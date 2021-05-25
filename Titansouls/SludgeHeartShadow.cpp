#include "stdafx.h"
#include "SludgeHeartShadow.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CSludgeHeartShadow::CSludgeHeartShadow()
    : m_pSludgeHeart(nullptr), m_bIsAlone(false)
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
	m_vecCollisionRect.reserve( 1 );
	m_vecCollisionRect.emplace_back( RECT() );
}

int CSludgeHeartShadow::Update()
{
	if ( m_bDestroyed )
		return OBJ_DESTROYED;

	return OBJ_NOEVENT;
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
					   , m_tRect.left + iScrollX, (int)(m_tRect.top + iScrollY /*- (m_tInfo.iCY)>>1*/)
					   , m_tInfo.iCX, m_tInfo.iCY
					   , hMemDC
					   , 18 * PIXELCX, 3 * PIXELCY
					   , PIXELCX * 2, PIXELCY * 1
					   , RGB( 255, 0, 255 ) );
}

void CSludgeHeartShadow::Release()
{
}

void CSludgeHeartShadow::Update_ColisionRect()
{

}

void CSludgeHeartShadow::Update_Dead()
{
}

void CSludgeHeartShadow::Update_Pattern()
{
}
