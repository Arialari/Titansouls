#include "stdafx.h"
#include "Ui.h"
#include "KeyMgr.h"

CUi::CUi()
	:m_bIsVisible(false), m_bIsHoverd(false),m_fRelatedX(0.f), m_fRelatedY(0.f), m_pAttachingUI(nullptr), m_eUiType(UI_TYPE::UI_TYPE_END)
{
}

CUi::~CUi()
{
	
}
void CUi::Set_Pos( float _x, float _y )
{
	m_tInfo.fX = _x + m_fRelatedX;
	m_tInfo.fY = _y + m_fRelatedY;
	for ( auto& pUi : m_vecAttachedUI )
		pUi->Set_Pos( _x, _y );
}

void CUi::Set_PosX( float _x )
{
	m_tInfo.fX = _x + m_fRelatedX;
	for ( auto& pUi : m_vecAttachedUI )
		pUi->Set_PosX( _x );
}

void CUi::Set_PosY( float _y )
{
	m_tInfo.fY = _y + m_fRelatedY;
	for ( auto& pUi : m_vecAttachedUI )
		pUi->Set_PosY( _y );
}

void CUi::Add_Pos( float _x, float _y )
{
	m_tInfo.fX += _x;
	m_tInfo.fY += _y;
	for ( auto& pUi : m_vecAttachedUI )
		pUi->Add_Pos( _x, _y );
}

void CUi::Add_PosX( float _x )
{
	m_tInfo.fX += _x;
	for ( auto& pUi : m_vecAttachedUI )
		pUi->Add_PosX( _x );
}

void CUi::Add_PosY( float _y )
{
	m_tInfo.fY += _y;
	for ( auto& pUi : m_vecAttachedUI )
		pUi->Add_PosY( _y );
}

void CUi::Set_IsVisible( bool _bIsVisible )
{
	m_bIsVisible = _bIsVisible;
	for ( auto& pUi : m_vecAttachedUI )
		pUi->Set_IsVisible( _bIsVisible );
}

void CUi::AttachUi( CUi* _pAttachedUi, float _fRelatedX, float _fRelatedY )
{
	m_vecAttachedUI.emplace_back( _pAttachedUi );
	_pAttachedUi->SetAttachingUi( this );
	_pAttachedUi->Set_RelatedX( _fRelatedX );
	_pAttachedUi->Set_RelatedY( _fRelatedY );
	_pAttachedUi->Set_Pos( m_tInfo.fX, m_tInfo.fY );
}

void CUi::Update_Hover()
{
	POINT	pt = {};
	GetCursorPos( &pt );
	ScreenToClient( g_hWnd, &pt );
	if ( PtInRect( &m_tRect, pt ) )
		m_bIsHoverd = true;
	else
		m_bIsHoverd = false;
}
