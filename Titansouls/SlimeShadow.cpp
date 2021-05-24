#include "stdafx.h"
#include "SlimeShadow.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

const int CSlimeShadow::m_iSizeStartX[5] = { 0, 10, 15, 18, 20 };
const int CSlimeShadow::m_iSizeStartY[5] = { 10, 6, 4, 3, 1 };
const int CSlimeShadow::m_iSizeX[5] = { 8, 5, 3, 2, 1 };
const int CSlimeShadow::m_iSizeY[5] = { 5, 3, 2, 1, 1 };
CSlimeShadow::CSlimeShadow()
	:m_iSizeLv(0), m_pSlime(nullptr)
{
}

CSlimeShadow::~CSlimeShadow()
{
	Release();
}

void CSlimeShadow::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp( L"../Image/p_Sludge Heart.bmp", L"Sludge" );

	m_tInfo.iCX = DEFAULTCX * 7;
	m_tInfo.iCY = DEFAULTCY * 5;
	Update_Rect();
	m_pImageKey = L"Sludge";
	
	m_eRenderID = RENDERID::SHADOW;
}

int CSlimeShadow::Update()
{
	if ( m_bDestroyed )
		return OBJ_DESTROYED;

	return OBJ_NOEVENT;
}

void CSlimeShadow::Late_Update()
{
}

void CSlimeShadow::Render( HDC _DC )
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( m_pImageKey );

	GdiTransparentBlt( _DC
					   , m_tRect.left + iScrollX, (int)(m_tRect.top + iScrollY )
					   , m_tInfo.iCX, m_tInfo.iCY
					   , hMemDC
					   , m_iSizeStartX[m_iSizeLv] * PIXELCX, m_iSizeStartY[m_iSizeLv] * PIXELCY
					   , PIXELCX * m_iSizeX[m_iSizeLv], PIXELCY * m_iSizeY[m_iSizeLv]
					   , RGB( 255, 0, 255 ) );
}

void CSlimeShadow::Release()
{
}

void CSlimeShadow::Update_Dead()
{
}

void CSlimeShadow::Update_Pattern()
{
}
