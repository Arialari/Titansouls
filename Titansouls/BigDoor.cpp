#include "stdafx.h"
#include "BigDoor.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Player.h"

CBigDoor::CBigDoor()
	:m_pPlayer(nullptr), m_iPatternFrame(0)
{
}

CBigDoor::~CBigDoor()
{
}

void CBigDoor::Initialize()
{
	m_tInfo.iCX = DEFAULTCX * 11;
	m_tInfo.iCY = DEFAULTCY * 14;

	m_eRenderID = RENDERID::DOOR;
	m_vecCollisionRect.reserve( 2 );
	m_vecCollisionRect.emplace_back( RECT() );
	m_vecCollisionRect.emplace_back( RECT() );
}

int CBigDoor::Update()
{
	Update_Rect();
	Update_ColisionRect();
	if ( m_pPlayer && (m_pPlayer->Get_Win_Count() == 2) )
	{
		if(m_pPlayer->Get_Info().fX <  m_tRect.right &&
			m_pPlayer->Get_Info().fX > m_tRect.left &&
			m_pPlayer->Get_Info().fY > m_tRect.bottom + (10 * DEFAULTCY))
			++m_iPatternFrame;
	}

	return 0;
}

void CBigDoor::Late_Update()
{
}

void CBigDoor::Render( HDC _DC )
{
    
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC  hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( L"Tile" );;
    
	GdiTransparentBlt( _DC
					   , m_tRect.left + iScrollX, m_tRect.top + iScrollY
					   , (m_tInfo.iCX >> 1), m_tInfo.iCY
					   , hMemDC
					   , (35 + (m_iPatternFrame * 0.1f)) * PIXELCX, 2 * PIXELCY
					   , PIXELCX * (5.5f - (m_iPatternFrame * 0.1f) ), PIXELCY * 14
					   , RGB( 255, 0, 255 ) );

	GdiTransparentBlt( _DC
					   , m_tRect.left + iScrollX + (m_tInfo.iCX >> 1), m_tRect.top + iScrollY
					   , ( m_tInfo.iCX >> 1 ), m_tInfo.iCY
					   , hMemDC
					   , 40.5f * PIXELCX, 2 * PIXELCY
					   , PIXELCX * (5.5f - (m_iPatternFrame * 0.1f)), PIXELCY * 14
					   , RGB( 255, 0, 255 ) );
	RenderCollision(_DC);
}

void CBigDoor::Release()
{
}

void CBigDoor::Update_ColisionRect()
{
	m_vecCollisionRect.front().left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1));
	m_vecCollisionRect.front().top = (LONG)(m_tInfo.fY + (m_tInfo.iCY >> 1) - DEFAULTCY);
	m_vecCollisionRect.front().right = (LONG)(m_tInfo.fX - (m_iPatternFrame * 0.1f) * DEFAULTCX);
	m_vecCollisionRect.front().bottom = (LONG)(m_tInfo.fY + (m_tInfo.iCY >> 1));

	m_vecCollisionRect.back().left = (LONG)(m_tInfo.fX + (m_iPatternFrame * 0.1f) * DEFAULTCX);
	m_vecCollisionRect.back().top = (LONG)(m_tInfo.fY + (m_tInfo.iCY >> 1) -DEFAULTCY);
	m_vecCollisionRect.back().right = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1));
	m_vecCollisionRect.back().bottom = (LONG)(m_tInfo.fY + (m_tInfo.iCY >> 1));
}
