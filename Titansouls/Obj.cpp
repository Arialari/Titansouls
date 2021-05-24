#include "stdafx.h"
#include "Obj.h"
#include "UiMgr.h"
#include "ScrollMgr.h"


CObj::CObj()
	: m_bDestroyed( false ), m_pImageKey( nullptr ), m_iDrawXID( 0 ), m_eRenderID(RENDERID::END), m_bIsRender( true ), m_bIsCheckBlock(true), m_bIsCheckOverlape(true) ,m_bDead(false)
{
	ZeroMemory( &m_tInfo, sizeof( m_tInfo ) );
	ZeroMemory( &m_tRect, sizeof( m_tRect ) );
}


CObj::~CObj()
{
}

void CObj::RenderCollision(HDC _DC, COLORREF _color )
{
	if ( CUiMgr::Get_Instance()->Get_IsCollisionVisible() )
	{
		for ( auto& rc : m_vecCollisionRect )
		{
			int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
			int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
			HBRUSH r_brush = CreateSolidBrush( _color );
			HGDIOBJ hOldBrush = SelectObject( _DC, r_brush );
			Rectangle( _DC, rc.left + iScrollX + 2, rc.top + iScrollY + 2, rc.right + iScrollX - 2, rc.bottom + iScrollY - 2 );
			SelectObject( _DC, hOldBrush );
			DeleteObject( r_brush );
		}
	}
}

void CObj::Update_Rect()
{
	m_tRect.left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1));
	m_tRect.top = (LONG)(m_tInfo.fY - (m_tInfo.iCY >> 1));
	m_tRect.right = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1));
	m_tRect.bottom = (LONG)(m_tInfo.fY + (m_tInfo.iCY >> 1));
}

