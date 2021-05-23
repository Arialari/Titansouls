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

	m_eRenderID = RENDERID::UI;
	m_eUiType = UI_TYPE::LAYOUT;
}

int CUiLayout::Update()
{
	if ( m_bDestroyed )
		return OBJ_DESTROYED;

	return OBJ_NOEVENT;
}

void CUiLayout::Late_Update()
{
}

void CUiLayout::Render( HDC _DC )
{
	Update_Rect();
	Update_Hover();

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

