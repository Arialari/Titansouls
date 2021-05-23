#include "stdafx.h"
#include "Tile.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "UiMgr.h"

int CTile::m_iFrameIdx = 0;
CTile::CTile()
	: m_iDrawYID(0), m_iFrameEndX(0), m_bIsAlphaRender(false), m_bIsCheckBlock(false)
{
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_tInfo.iCX = DEFAULTCX;
	m_tInfo.iCY = DEFAULTCY;
	m_eRenderID = RENDERID::BACKGROUND;
}

int CTile::Update()
{
	if (m_bDestroyed)
		return OBJ_DESTROYED;

	return OBJ_NOEVENT;
}

void CTile::Late_Update()
{
}

void CTile::Render(HDC _DC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	if ( m_bIsRender )
	{
		Update_Rect();



		int iFrameX = 0;
		if ( m_iFrameEndX )
			iFrameX = m_iFrameIdx % m_iFrameEndX;

		HDC hMemDC = CTileMgr::Get_Instance()->Get_DC();

		//if ( m_bIsAlphaRender )
		//{
		//	BLENDFUNCTION tBlendFunction;
		//	tBlendFunction.AlphaFormat = 0;
		//	tBlendFunction.BlendFlags = 0;
		//	tBlendFunction.BlendOp = 0;
		//	tBlendFunction.SourceConstantAlpha = 0;
		//	AlphaBlend(_DC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tInfo.iCX, m_tInfo.iCY
		//				, hMemDC, (m_iDrawXID + iFrameX) * PIXELCX, m_iDrawYID * PIXELCY
		//				, PIXELCX, PIXELCY, tBlendFunction);
		//	GdiTransparentBlt( _DC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tInfo.iCX, m_tInfo.iCY
		//					   , hMemDC, (m_iDrawXID + iFrameX) * PIXELCX, m_iDrawYID * PIXELCY
		//					   , PIXELCX, PIXELCY, RGB( 255, 255, 255 ) );
		//}
		//else
		//{
			//BitBlt(_DC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tInfo.iCX, m_tInfo.iCY
			//	, hMemDC, m_iDrawXID * PIXELCX, m_iDrawYID * PIXELCY, SRCCOPY);
			GdiTransparentBlt( _DC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tInfo.iCX, m_tInfo.iCY
							   , hMemDC, (m_iDrawXID + iFrameX) * PIXELCX, m_iDrawYID * PIXELCY
							   , PIXELCX, PIXELCY, RGB( 255, 255, 255 ) );
		//}


	}
	if ( CUiMgr::Get_Instance()->Get_IsCollisionVisible() )
	{
		if ( m_bIsCheckBlock )
		{
			HPEN r_brush = CreatePen( PS_SOLID, 1, RGB( 255, 0, 0 ) );
			HGDIOBJ hOldBrush = SelectObject( _DC, r_brush );

			MoveToEx( _DC, m_tRect.left + iScrollX + 1, m_tRect.top + iScrollY + 1, NULL );
			LineTo( _DC, m_tRect.right + iScrollX - 1, m_tRect.top + iScrollY + 1 );
			LineTo( _DC, m_tRect.right + iScrollX - 1, m_tRect.bottom + iScrollY - 1 );
			LineTo( _DC, m_tRect.left + iScrollX + 1, m_tRect.bottom + iScrollY - 1 );
			LineTo( _DC, m_tRect.left + iScrollX + 1, m_tRect.top + iScrollY + 1 );

			SelectObject( _DC, hOldBrush );
			DeleteObject( r_brush );
		}
	}

}

void CTile::Release()
{
}

void CTile::Update_ColisionRect()
{
}
