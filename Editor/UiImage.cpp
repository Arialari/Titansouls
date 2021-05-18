#include "stdafx.h"
#include "UiImage.h"
#include "BmpMgr.h"
#include "TileMgr.h"
#include "KeyMgr.h"

CUiImage::CUiImage()
	: m_tModelInfo( {} ), m_iModelEndX(0), m_iModelIntervalX(8)
{
}

CUiImage::~CUiImage()
{
}

void CUiImage::Initialize()
{
	m_eRenderID = RENDERID::UI;
	m_tModelInfo.iCX = 16;
	m_tModelInfo.iCY = 16;
	m_eUiType = UI_TYPE::IMAGE;
}

int CUiImage::Update()
{
	if ( m_bDead )
		return OBJ_DEAD;
	if ( CKeyMgr::Get_Instance()->Key_Down( '0' ) )
		m_iModelEndX = 0;
	else if ( CKeyMgr::Get_Instance()->Key_Down( VK_ADD ) )
		m_iModelEndX++;
	else if ( CKeyMgr::Get_Instance()->Key_Down( VK_SUBTRACT ) )
	{
		if( m_iModelEndX > 0 )
			m_iModelEndX--;
	}
		

	Update_Rect();
	Update_Hover();
	return OBJ_NOEVENT;
}

void CUiImage::Late_Update()
{
}

void CUiImage::Render( HDC _DC )
{
	if ( !m_bIsVisible )
		return;

	Update_Rect();
	HDC hMemDc = CBmpMgr::Get_Instance()->Find_Bmp( m_pImageKey );
	Rectangle( _DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom );
	GdiTransparentBlt( _DC, m_tRect.left, m_tRect.top, m_tInfo.iCX, m_tInfo.iCY
					   , hMemDc, (int)(m_tModelInfo.fX * m_iModelIntervalX * PIXELCX), (int)(m_tModelInfo.fY * m_iModelIntervalX * PIXELCY),
					   PIXELCX * m_tModelInfo.iCX, PIXELCY * m_tModelInfo.iCY, RGB( 255, 255, 255 ) );


	TCHAR szBuff[32];
	swprintf_s( szBuff, L"iEndX : %d", m_iModelEndX);
	TextOut( _DC, m_tRect.bottom, m_tRect.right - 30, szBuff, lstrlen( szBuff ) );
}

void CUiImage::Release()
{
}

void CUiImage::Update_ColisionRect()
{
}

void CUiImage::OnEvent( EVENT_CODE _eEventCode )
{
	switch ( _eEventCode )
	{
	case CUi::MOVE_LEFT:
		if( m_tModelInfo.fX > 0.f )
			m_tModelInfo.fX -= 1.f;
		break;
	case CUi::MOVE_UP:
		if ( m_tModelInfo.fY > 0.f )
			m_tModelInfo.fY -= 1.f;
		break;
	case CUi::MOVE_RIGHT:
		if ( m_tModelInfo.fX < 30.f )
			m_tModelInfo.fX += 1.f;
		break;
	case CUi::MOVE_DOWN:
		if ( m_tModelInfo.fY < 6.f )
			m_tModelInfo.fY += 1.f;
		break;
	case CUi::NO_EVENT:
	default:
		return;
	}
}

void CUiImage::Hit()
{
	POINT	pt = {};
	GetCursorPos( &pt );
	ScreenToClient( g_hWnd, &pt );

	int iModelX = (int)(((pt.x - m_tRect.left)/ (m_tInfo.iCX / m_tModelInfo.iCX)) + m_tModelInfo.fX* m_iModelIntervalX);
	int iModelY = (int)(((pt.y - m_tRect.top) / (m_tInfo.iCY / m_tModelInfo.iCY)) + m_tModelInfo.fY* m_iModelIntervalX);

	CTileMgr::Get_Instance()->Set_PaintPoint( iModelX, iModelY );
	CTileMgr::Get_Instance()->Set_PaintEndX( m_iModelEndX );
}
