#include "stdafx.h"
#include "UiButton.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"

CUiButton::CUiButton()
	:m_eEventCode(EVENT_CODE::NO_EVENT)
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
	m_eUiType = UI_TYPE::BUTTON;
}

int CUiButton::Update()
{
	if ( m_bDead )
		return OBJ_DEAD;

	Update_Rect();
	Update_Hover();

	return OBJ_NOEVENT;
}

void CUiButton::Late_Update()
{
}

void CUiButton::Render( HDC _DC )
{
	if ( !m_bIsVisible )
		return;

	Update_Rect();

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( m_pImageKey );

	GdiTransparentBlt(_DC, m_tRect.left, m_tRect.top, m_tInfo.iCX, m_tInfo.iCY
					   , hMemDC, 
					   m_iDrawXID * PIXELCX*2, ((int)m_bIsHoverd)* PIXELCY*2, 
					   PIXELCX*2, PIXELCY*2, RGB(255,0,255) );
	 
}

void CUiButton::Release()
{

}

void CUiButton::Update_ColisionRect()
{
}

void CUiButton::Hit()
{
	if(m_pAttachingUI )
		m_pAttachingUI->OnEvent( m_eEventCode );
}

void CUiButton::OnEvent( EVENT_CODE _eEventCode )
{
}
