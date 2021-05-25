#include "stdafx.h"
#include "SlimeShadow.h"
#include "SludgeHeart.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Player.h"
#include "Arrow.h"
#include "Slime.h"

const int CSlimeShadow::m_iSizeStartX[5] = { 0, 10, 15, 18, 20 };
const int CSlimeShadow::m_iSizeStartY[5] = { 10, 6, 4, 3, 1 };
const int CSlimeShadow::m_iSizeX[5] = { 8, 5, 3, 2, 1 };
const int CSlimeShadow::m_iSizeY[5] = { 5, 3, 2, 1, 1 };
CSlimeShadow::CSlimeShadow()
	:m_iSizeLv(0), m_pSlime(nullptr), m_iMaxCX(0), m_fMozziX(1.f), m_iMaxCY(0), m_fMozziY( 1.f )
{
}

CSlimeShadow::~CSlimeShadow()
{
	Release();
}

void CSlimeShadow::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp( L"../Image/p_Sludge Heart.bmp", L"Sludge" );
	m_iMaxCX = m_iSizeX[m_iSizeLv] * DEFAULTCX;
	m_iMaxCY = m_iSizeY[m_iSizeLv] * DEFAULTCY;
	m_tInfo.iCX = m_iMaxCX;
	m_tInfo.iCY = m_iMaxCY;
	Update_Rect();
	m_pImageKey = L"Sludge";
	
	m_bIsCheckOverlape = false;
	m_eRenderID = RENDERID::SHADOW;
	m_vecCollisionRect.reserve( 1 );
	m_vecCollisionRect.emplace_back( RECT() );
}

int CSlimeShadow::Update()
{
	if ( m_bDestroyed || m_bDead)
		return OBJ_DESTROYED;
	Reset_Size();
	Update_Mozzi();
	Update_Rect();
	Update_ColisionRect();

	return OBJ_NOEVENT;
}

void CSlimeShadow::Late_Update()
{
}

void CSlimeShadow::Render( HDC _DC )
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( m_pImageKey );

	Update_Rect();

	GdiTransparentBlt( _DC
					   , m_tRect.left + iScrollX, (int)(m_tRect.top + iScrollY - (m_tInfo.iCY >> 1) )
					   , m_tInfo.iCX, m_tInfo.iCY
					   , hMemDC
					   , m_iSizeStartX[m_iSizeLv] * PIXELCX, m_iSizeStartY[m_iSizeLv] * PIXELCY
					   , PIXELCX * m_iSizeX[m_iSizeLv], PIXELCY * m_iSizeY[m_iSizeLv]
					   , RGB( 255, 0, 255 ) );
	RenderCollision(_DC);
}

void CSlimeShadow::Release()
{
}

void CSlimeShadow::Update_ColisionRect()
{
	if ( m_bIsCheckOverlape )
	{
		m_vecCollisionRect.front().left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1));
		m_vecCollisionRect.front().top = (LONG)(m_tInfo.fY - m_tInfo.iCY);
		m_vecCollisionRect.front().right = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1));
		m_vecCollisionRect.front().bottom = (LONG)(m_tInfo.fY);
	}
	else
	{
		m_vecCollisionRect.front().left = (LONG)0;
		m_vecCollisionRect.front().top = (LONG)0;
		m_vecCollisionRect.front().right = (LONG)0;
		m_vecCollisionRect.front().bottom = (LONG)0;
	}
}

void CSlimeShadow::OnOverlaped( CObj* _pBlockedObj, DIRECTION _eDir )
{
	if ( dynamic_cast<CPlayer*>(_pBlockedObj) )
	{
		if ( !m_bDead )
		{
			_pBlockedObj->Set_Dead( true );
			_pBlockedObj->Update_ColisionRect();
		}
	}
	else if ( dynamic_cast<CArrow*>(_pBlockedObj) )
	{
		if ( !(static_cast<CArrow*>(_pBlockedObj)->Get_IsDamage()) )
			return;
		if ( !m_bDead )
		{
			m_pSludgeHeart->Set_Active();
			if ( m_iSizeLv < 4 )
			{
				if ( m_pSlime->Get_bHaveHeart() && m_iSizeLv == 3 )
				{
					m_bDestroyed = true;
					m_pSlime->Set_Dead(true);
					m_pSludgeHeart->Set_Alone();
				}
				else
				{
					m_bDestroyed = true;
					m_pSlime->Set_Dead( true );
					m_pSludgeHeart->Create_Slime( m_tInfo.fX, m_tInfo.fY + (rand() % 3 - 1)* 2 * DEFAULTCY, ++m_iSizeLv, m_pSlime->Get_bHaveHeart() );
					m_pSlime->Set_iSizeLv( m_iSizeLv );
					m_pSlime->Reset_Size();
					m_pSludgeHeart->Create_Slime( m_tInfo.fX + (rand() % 3 - 1)* 2 * DEFAULTCX, m_tInfo.fY, m_iSizeLv, false );
					m_pSlime->Set_iSizeLv( m_iSizeLv );
					m_pSlime->Reset_Size();
				}
			}
				
		}
	}
	
}

void CSlimeShadow::Reset_Size()
{
	m_iMaxCX = m_iSizeX[m_iSizeLv] * DEFAULTCX;
	m_iMaxCY = m_iSizeY[m_iSizeLv] * DEFAULTCY;
	m_tInfo.iCX = m_iMaxCX;
	m_tInfo.iCY = m_iMaxCY;
	//m_tInfo.iCY = m_iSizeY[m_iSizeLv] * DEFAULTCY - (DEFAULTCY * m_iSizeY[m_iSizeLv] / 8);
	Update_Rect();
}

void CSlimeShadow::Update_Mozzi()
{
	m_tInfo.iCX = m_iMaxCX * m_fMozziX - (DEFAULTCX * m_iSizeX[m_iSizeLv] / 8);
	m_tInfo.iCY = m_iMaxCY * m_fMozziY - (DEFAULTCX * m_iSizeY[m_iSizeLv] / 8);
}

void CSlimeShadow::Update_Dead()
{
}

void CSlimeShadow::Update_Pattern()
{
}
