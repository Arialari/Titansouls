#include "stdafx.h"
#include "SludgeHeart.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Slime.h"

CSludgeHeart::CSludgeHeart()
	:m_pShadow(nullptr)
{
	ZeroMemory( m_pSlime, sizeof( m_pSlime ) );
}

CSludgeHeart::~CSludgeHeart()
{
	Release();
}

void CSludgeHeart::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp( L"../Image/p_Sludge Heart.bmp", L"Sludge" );
	m_tInfo.fX = 45.5f * DEFAULTCX;
	m_tInfo.fY = 42.5f * DEFAULTCY;
	m_tInfo.iCX = 2 * DEFAULTCX;
	m_tInfo.iCY = 2 * DEFAULTCY;
	Update_Rect();
	m_pImageKey = L"Sludge";
	m_eRenderID = RENDERID::OBJECT;
	m_vecCollisionRect.reserve( 1 );
	m_vecCollisionRect.emplace_back( RECT() );
	m_fPosZ = 30.f;
	
	m_pSlime[0] = static_cast<CSlime*>(CAbstractFactory<CSlime>::Create(m_tInfo.fX,m_tInfo.fY));
	m_pSlime[0]->Set_SludgeHeart( this );
}

int CSludgeHeart::Update()
{
	return 0;
}

void CSludgeHeart::Late_Update()
{
}

void CSludgeHeart::Render( HDC _DC )
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( m_pImageKey );

	GdiTransparentBlt( _DC
					   , m_tRect.left + iScrollX, (int)(m_tRect.top + iScrollY)
					   , m_tInfo.iCX, m_tInfo.iCY
					   , hMemDC
					   , 24 * PIXELCX, m_iFrameidx * 2 * PIXELCY
					   , PIXELCX * 2, PIXELCY * 2
					   , RGB( 255, 0, 255 ) );
}

void CSludgeHeart::Release()
{
}

void CSludgeHeart::Update_Dead()
{
}

void CSludgeHeart::Update_Pattern()
{
}
