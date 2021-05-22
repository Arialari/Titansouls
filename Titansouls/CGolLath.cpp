#include "stdafx.h"
#include "CGolLath.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CGolLath::CGolLath()
{
}

CGolLath::~CGolLath()
{
}

void CGolLath::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp( L"../Image/p_Gol-Lath.bmp", L"Gol_Lath" );

	m_tInfo.fX = 700.f;
	m_tInfo.fY = 100.f;
	m_tInfo.iCX = DEFAULTCX * 4;
	m_tInfo.iCY = DEFAULTCY * 5;
	Update_Rect();

	m_pImageKey = L"Gol_Lath";
	m_eRenderID = RENDERID::OBJECT;
	m_vecCollisionRect.reserve( 1 );
	m_vecCollisionRect.emplace_back( RECT() );
}

int CGolLath::Update()
{
	if ( m_bDestroyed )
		return OBJ_DEAD;

	Update_Animation_Frame();

	//Update_Rect(); Not Nessercery
	Update_ColisionRect();

	return OBJ_NOEVENT;
}

void CGolLath::Late_Update()
{
}

void CGolLath::Render( HDC _DC )
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( m_pImageKey );

	GdiTransparentBlt( _DC
					   , m_tRect.left + iScrollX, m_tRect.top + iScrollY
					   , m_tInfo.iCX, m_tInfo.iCY
					   , hMemDC
					   , m_tFrame.iFrameX * PIXELCX, m_tFrame.iModelY * PIXELCY
					   , PIXELCX * 4, PIXELCY * 5
					   , RGB( 255, 0, 255 ) );
}

void CGolLath::Release()
{
}

void CGolLath::Update_ColisionRect()
{
	m_vecCollisionRect.front().left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1));
	m_vecCollisionRect.front().top = (LONG)(m_tInfo.fY - (m_tInfo.iCY >> 1));
	m_vecCollisionRect.front().right = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1));
	m_vecCollisionRect.front().bottom = (LONG)(m_tInfo.fY + (m_tInfo.iCY >> 1));
}
