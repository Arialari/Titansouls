#include "stdafx.h"
#include "Tile.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CTile::CTile()
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

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Tile");

	GdiTransparentBlt(_DC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC, m_iDrawID * PIXELCX, 0, PIXELCX,PIXELCY,RGB(255,0,255));
}

void CTile::Release()
{
}

void CTile::Update_ColisionRect()
{
}
