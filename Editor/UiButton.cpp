#include "stdafx.h"
#include "UiButton.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CUiButton::CUiButton()
{
}

CUiButton::~CUiButton()
{
}

void CUiButton::Initialize()
{
	m_tInfo.iCX = PIXELCX*4;
	m_tInfo.iCY = PIXELCY*4;

	m_pImageKey = L"UIButton";
	m_eRenderID = RENDERID::UI;
}

int CUiButton::Update()
{
	if ( m_bDead )
		return OBJ_DEAD;


	return OBJ_NOEVENT;
}

void CUiButton::Late_Update()
{
}

void CUiButton::Render( HDC _DC )
{
	/*if ( !m_bIsVisible )
		return;*/

	Update_Rect();

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( m_pImageKey );

	GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC, m_iDrawXID * m_tInfo.iCX, ((int)m_bIsHoverd)* m_tInfo.iCY, m_tInfo.iCX, m_tInfo.iCY,RGB(255,0,255) );
	 
}

void CUiButton::Release()
{

}

void CUiButton::Update_ColisionRect()
{
}
