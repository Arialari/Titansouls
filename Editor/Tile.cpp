#include "stdafx.h"
#include "Tile.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"

int CTile::m_iFrameIdx = 0;
CTile::CTile()
	: m_iDrawYID(0), m_iFrameEndX(0)
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
}

int CTile::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CTile::Late_Update()
{
}

void CTile::Render(HDC _DC)
{
	Update_Rect();

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	int iFrameX = 0;
	if( m_iFrameEndX )
		iFrameX = m_iFrameIdx % m_iFrameEndX;

	HDC hMemDC = CTileMgr::Get_Instance()->Get_DC();

	//BitBlt(_DC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tInfo.iCX, m_tInfo.iCY
	//	, hMemDC, m_iDrawXID * PIXELCX, m_iDrawYID * PIXELCY, SRCCOPY);

	GdiTransparentBlt(_DC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tInfo.iCX, m_tInfo.iCY
						, hMemDC, (m_iDrawXID+ iFrameX) * PIXELCX, m_iDrawYID * PIXELCY
					   , PIXELCX,PIXELCY,RGB(255,255,255));
}

void CTile::Release()
{
}

void CTile::Update_ColisionRect()
{
}
