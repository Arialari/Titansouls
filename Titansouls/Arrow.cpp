#include "stdafx.h"
#include "BmpMgr.h"
#include "Arrow.h"
#include "ScrollMgr.h"
#include "Tile.h"
#include "Player.h"

CArrow::CArrow()
    :m_fRadianAngle( 0.f ), m_hMemDc( nullptr ), m_fFullSpeed( 24.5f ), m_fSpeed(0.f), m_fReturnAccelator(1.f), m_bHolded(true), m_bIsReturning(false)
{
}

CArrow::~CArrow()
{
    Release();
}

void CArrow::Initialize()
{
    m_tInfo.iCX = DEFAULTCX;
    m_tInfo.iCY = DEFAULTCY;
    m_bIsRender = false;
    m_eRenderID = RENDERID::OBJECT;
    m_hMemDc = CBmpMgr::Get_Instance()->Find_Bmp( L"Player" );

    m_vecCollisionRect.reserve( 1 );
    m_vecCollisionRect.emplace_back( RECT() );
}

int CArrow::Update()
{
    if ( m_bDead )
        return OBJ_DEAD;

    if ( m_fSpeed >= 0.7 )
        m_fSpeed -= 0.7f;
    else
        m_fSpeed = 0;

    m_tInfo.fX += m_fSpeed * cosf( m_fRadianAngle );
    m_tInfo.fY -= m_fSpeed * sinf( m_fRadianAngle );

    Update_Rect();
    Update_ColisionRect();

    return OBJ_NOEVENT;
}

void CArrow::Late_Update()
{
    if ( m_fSpeed > 3.f )
        m_bIsBlock = true;
    else
        m_bIsBlock = false;
}

void CArrow::Render( HDC _DC )
{
    if ( m_bIsRender )
    {
        Update_Rect();
        int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
        int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

        bool b = GdiTransparentBlt( _DC
                           , m_tRect.left + iScrollX, m_tRect.top + iScrollY
                           , m_tInfo.iCX, m_tInfo.iCY
                           , m_hMemDc
                           , 31 * PIXELCX, 0
                           , PIXELCX, PIXELCY
                           , RGB( 255, 0, 255 ) );

    }
}

void CArrow::Release()
{
}

void CArrow::Update_ColisionRect()
{
    m_vecCollisionRect.front().left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1));
    m_vecCollisionRect.front().top = (LONG)(m_tInfo.fY - (m_tInfo.iCY >> 1));
    m_vecCollisionRect.front().right = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1));
    m_vecCollisionRect.front().bottom = (LONG)(m_tInfo.fY + (m_tInfo.iCY >> 1));
}

void CArrow::OnBlocked( CObj* _pBlockedObj,  DIRECTION _eDir )
{
    CObj* pObj;
    if ( pObj = dynamic_cast<CTile*>(_pBlockedObj) )
    {
        switch ( _eDir )
        {
        case E:
            if ( cos( m_fRadianAngle ) > 0 )
                m_fRadianAngle = PI - m_fRadianAngle;
            break;
        case W:
            if ( cos( m_fRadianAngle ) < 0 )
                m_fRadianAngle = PI - m_fRadianAngle;
            break;
        case N:
            if ( sin( m_fRadianAngle ) > 0 )
                m_fRadianAngle = -m_fRadianAngle;
            break;
        case S:
            if ( sin( m_fRadianAngle ) < 0 )
                m_fRadianAngle = -m_fRadianAngle;
            break;
        case SE:
        case SW:
        case NW:
        case NE:
            m_fRadianAngle += PI;
            break;
        case DIRECTION_END:
            break;
        default:
            break;
        }
    }
    else if ( pObj = dynamic_cast<CPlayer*>(_pBlockedObj) )
    {
        if ( !m_bHolded && ((m_fSpeed < 2.f) || m_bIsReturning) )
        {
            static_cast<CPlayer*>(pObj)->Pick_Arrow();
            m_bIsRender = false;
            m_bHolded = true;
        }
    }

}

void CArrow::Shoot( float _fAimGaze )
{
    m_fSpeed = m_fFullSpeed * _fAimGaze;
    m_bHolded = false;
}

void CArrow::Add_Speed()
{
    if ( m_fSpeed < m_fFullSpeed )
        m_fSpeed += m_fReturnAccelator;
    else
        m_fSpeed = m_fFullSpeed;
}
