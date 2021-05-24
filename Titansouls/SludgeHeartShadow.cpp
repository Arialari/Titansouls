#include "stdafx.h"
#include "SludgeHeartShadow.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CSludgeHeartShadow::CSludgeHeartShadow()
    : m_pSludgeHeart(nullptr)
{
}

CSludgeHeartShadow::~CSludgeHeartShadow()
{
	Release();
}

void CSludgeHeartShadow::Initialize()
{
	m_tInfo.iCX = DEFAULTCX;
	m_tInfo.iCY = DEFAULTCY * 2;

	m_eRenderID = RENDERID::SHADOW;
}

int CSludgeHeartShadow::Update()
{
    return 0;
}

void CSludgeHeartShadow::Late_Update()
{
}

void CSludgeHeartShadow::Render( HDC _DC )
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( m_pImageKey );

	GdiTransparentBlt( _DC
					   , m_tRect.left + iScrollX, (int)(m_tRect.top + iScrollY)
					   , m_tInfo.iCX, m_tInfo.iCY
					   , hMemDC
					   , 18 * PIXELCX, 3 * PIXELCY
					   , PIXELCX * 2, PIXELCY * 1
					   , RGB( 255, 0, 255 ) );
}

void CSludgeHeartShadow::Release()
{
}

void CSludgeHeartShadow::Update_Dead()
{
}

void CSludgeHeartShadow::Update_Pattern()
{
}
