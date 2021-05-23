#include "stdafx.h"
#include "GolLathArm.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CGolLathArm::CGolLathArm()
	:m_bIsFliped(false), m_pGolLath(nullptr)
{
}

CGolLathArm::~CGolLathArm()
{
}

void CGolLathArm::Initialize()
{
	m_tInfo.fX = 42.5f * DEFAULTCX;
	m_tInfo.fY = 60.5f * DEFAULTCY;
	m_tInfo.iCX = DEFAULTCX * 4;
	m_tInfo.iCY = DEFAULTCY * 2;
	Update_Rect();
	m_pImageKey = L"Gol_Lath";
	m_eRenderID = RENDERID::OBJECT;
	m_vecCollisionRect.reserve( 1 );
	m_vecCollisionRect.emplace_back( RECT() );
}

int CGolLathArm::Update()
{
	if ( m_bDestroyed )
		return OBJ_DESTROYED;

	if ( m_bIsCheckBlock )
		m_bIsCheckOverlape = false;
	Update_Pattern();
	Update_DamageCollision();
	Update_ColisionRect();

	return OBJ_NOEVENT;
}

void CGolLathArm::Late_Update()
{
}

void CGolLathArm::Render( HDC _DC )
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( m_pImageKey );

	//그림자
	GdiTransparentBlt( _DC
					   , m_tRect.left + iScrollX, m_tRect.top + iScrollY
					   , m_tInfo.iCX, m_tInfo.iCY
					   , hMemDC
					   , (m_tFrame.iFrameX + 16) * PIXELCX, (20 + (6 * m_bIsFliped) )* PIXELCY
					   , 4 * PIXELCX, 2 * PIXELCY
					   , RGB( 255, 0, 255 ) );
	//손
	GdiTransparentBlt( _DC
					   , m_tRect.left + iScrollX, m_tRect.top + iScrollY - (DEFAULTCY) - m_fPosZ
					   , m_tInfo.iCX, 4 * DEFAULTCY
					   , hMemDC
					   , (m_tFrame.iFrameX + 16) * PIXELCX, (16 + (6 * m_bIsFliped)) * PIXELCY
					   , 4 * PIXELCX, 4 * PIXELCY
					   , RGB( 255, 0, 255 ) );
	RenderCollision(_DC);
}

void CGolLathArm::Release()
{
}

void CGolLathArm::Update_ColisionRect()
{
	if ( m_bIsCheckBlock )
	{
		m_vecCollisionRect.front().left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1) + (m_bIsFliped * DEFAULTCX));
		m_vecCollisionRect.front().top = (LONG)(m_tInfo.fY - (m_tInfo.iCY >> 1) - (DEFAULTCY >> 1));
		m_vecCollisionRect.front().right = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1) - (!m_bIsFliped * DEFAULTCX));
		m_vecCollisionRect.front().bottom = (LONG)(m_tInfo.fY + (m_tInfo.iCY >> 1) + (DEFAULTCY >> 1));
	}
	else
	{
		m_vecCollisionRect.front().left = (LONG)0;
		m_vecCollisionRect.front().top = (LONG)0;
		m_vecCollisionRect.front().right = (LONG)0;
		m_vecCollisionRect.front().bottom = (LONG)0;
	}
	
}

void CGolLathArm::OnOverlaped( CObj* _pBlockedObj, DIRECTION _eDir )
{
	_pBlockedObj->Set_Dead( true );
}

void CGolLathArm::Update_Pattern()
{
	if ( m_bActive )
		++m_iPatternFrame;
	
}
