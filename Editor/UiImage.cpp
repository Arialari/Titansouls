#include "stdafx.h"
#include "UiImage.h"
#include "BmpMgr.h"

CUiImage::CUiImage()
	: m_tModelInfo( {} )
{
}

CUiImage::~CUiImage()
{
}

void CUiImage::Initialize()
{
	m_eRenderID = RENDERID::UI;
	m_tModelInfo.iCX = 10;
	m_tModelInfo.iCY = 10;
}

int CUiImage::Update()
{
	if ( m_bDead )
		return OBJ_DEAD;
	return OBJ_NOEVENT;
}

void CUiImage::Late_Update()
{
}

void CUiImage::Render( HDC _DC )
{
	Update_Rect();
	HDC hMemDc = CBmpMgr::Get_Instance()->Find_Bmp( m_pImageKey );
	Rectangle( _DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom );
	GdiTransparentBlt( _DC, m_tRect.left, m_tRect.top, m_tInfo.iCX, m_tInfo.iCY
					   , hMemDc, (int)(m_tModelInfo.fX * m_tModelInfo.iCX * PIXELCX), (int)(m_tModelInfo.fY * m_tModelInfo.iCY * PIXELCY),
					   PIXELCX * m_tModelInfo.iCX, PIXELCY * m_tModelInfo.iCY, RGB( 255, 255, 255 ) );
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
		m_tModelInfo.fX += 1.f;
		break;
	case CUi::MOVE_DOWN:
		m_tModelInfo.fY += 1.f;
		break;
	case CUi::NO_EVENT:
	default:
		return;
	}
}
