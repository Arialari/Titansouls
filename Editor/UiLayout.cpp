#include "stdafx.h"
#include "UiLayout.h"

CUiLayout::CUiLayout()
{
}

CUiLayout::~CUiLayout()
{
}

void CUiLayout::Initialize()
{
	m_tInfo.iCX = 100;
	m_tInfo.iCY = 100;

	m_eRenderID = RENDERID::UI;
}

int CUiLayout::Update()
{
	if ( m_bDead )
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CUiLayout::Late_Update()
{
}

void CUiLayout::Render( HDC _DC )
{
	Update_Rect();
//	Rectangle( _DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom );
}

void CUiLayout::Release()
{
}

void CUiLayout::Update_ColisionRect()
{
}

void CUiLayout::OnEvent( EVENT_CODE _eEventCode )
{
	m_vecAttachedUI.back()->OnEvent( _eEventCode );
}

