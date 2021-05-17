#include "stdafx.h"
#include "UiLayout.h"

void CUiLayout::Initialize()
{
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
}

void CUiLayout::Release()
{
}

void CUiLayout::Update_ColisionRect()
{
}

void CUiLayout::Set_Pos( float _x, float _y )
{
	m_tInfo.fX = _x;
	m_tInfo.fY = _y;
	for ( auto& pUi : m_vecHavingUI )
		pUi->Set_Pos( _x, _y );
}

void CUiLayout::Set_PosX( float _x )
{
	m_tInfo.fX = _x;
	for ( auto& pUi : m_vecHavingUI )
		pUi->Set_PosX( _x );
}

void CUiLayout::Set_PosY( float _y )
{
	m_tInfo.fY = _y;
	for ( auto& pUi : m_vecHavingUI )
		pUi->Set_PosY( _y );
}

void CUiLayout::Add_Pos( float _x, float _y )
{
	m_tInfo.fX += _x;
	m_tInfo.fY += _y;
	for ( auto& pUi : m_vecHavingUI )
		pUi->Add_Pos( _x, _y );
}

void CUiLayout::Add_PosX( float _x )
{
	m_tInfo.fX += _x;
	for ( auto& pUi : m_vecHavingUI )
		pUi->Add_PosX( _x );
}

void CUiLayout::Add_PosY( float _y )
{
	m_tInfo.fY += _y;
	for ( auto& pUi : m_vecHavingUI )
		pUi->Add_PosY( _y );
}

void CUiLayout::AttachUi( CUi* pCUi )
{
	m_vecHavingUI.emplace_back( pCUi );
}
