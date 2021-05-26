#include "stdafx.h"
#include "TitanKillBox.h"
#include "Titan.h"
#include "Arrow.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"

CTitanKillBox::CTitanKillBox()
	: m_bIsKillBoxAcive( false ), m_pTitan( nullptr ), m_bOverlapeOnce( true), m_pArrow(nullptr)
{
}

CTitanKillBox::~CTitanKillBox()
{
}

void CTitanKillBox::Initialize()
{
	m_bIsCheckOverlape = true;
	m_eRenderID = RENDERID::UI;
	m_bIsRender = false;

	m_vecCollisionRect.reserve( 1 );
	m_vecCollisionRect.emplace_back( RECT() );
}

int CTitanKillBox::Update()
{
	if ( m_bDestroyed )
		return OBJ_DESTROYED;
	if ( m_pArrow && m_pArrow->Get_IsDamage() )
	{
		m_bIsRender = false;
		m_pArrow->Set_IsRender( true );
	}
		
	Update_ColisionRect();
	return OBJ_NOEVENT;
}

void CTitanKillBox::Late_Update()
{
}

void CTitanKillBox::Render( HDC _DC )
{
	if ( m_bIsRender )
	{
		m_hMemDc = CBmpMgr::Get_Instance()->Find_Bmp( L"Player" );

		Update_RenderPoint();
		Update_Rect();
		int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
		HDC hPlgDC = CBmpMgr::Get_Instance()->Find_Bmp( L"Plg" );
		HDC hResetDC = CBmpMgr::Get_Instance()->Find_Bmp( L"Reset" );

		PlgBlt( hPlgDC, m_tRenderPoint
				, m_hMemDc
				, 30 * PIXELCX, PIXELCY
				, PIXELCX, PIXELCY
				, NULL, NULL, NULL );

		GdiTransparentBlt( _DC
						   , m_tRect.left + iScrollX, m_tRect.top + iScrollY
						   , m_tInfo.iCX, m_tInfo.iCY
						   , hPlgDC
						   , 0, 0
						   , PIXELCX, PIXELCY
						   , RGB( 255, 0, 255 ) );
		BitBlt( hPlgDC, 0, 0, PIXELCX, PIXELCY, hResetDC, 0, 0, SRCCOPY );
	}
	RenderCollision(_DC, RGB(168,33,168));
}

void CTitanKillBox::Release()
{
}

void CTitanKillBox::Update_ColisionRect()
{
	m_vecCollisionRect.front().left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1));
	m_vecCollisionRect.front().top = (LONG)(m_tInfo.fY - (m_tInfo.iCY >> 1));
	m_vecCollisionRect.front().right = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1));
	m_vecCollisionRect.front().bottom = (LONG)(m_tInfo.fY + (m_tInfo.iCY >> 1));

}
void CTitanKillBox::Update_RenderPoint()
{
	float	fX = (float)(PIXELCX >> 1);
	float	fY = (float)(PIXELCY >> 1);

	float	fCX = (float)(PIXELCX >> 1);
	float	fCY = (float)(PIXELCY >> 1);
	float	fDia = sqrtf( fCX * fCX + fCY * fCY );

	m_tRenderPoint[0].x = (LONG)(fX + (cosf( PI * 5 / 4 + m_fArrowAngle ) * fDia));
	m_tRenderPoint[0].y = (LONG)(fY - (sinf( PI * 5 / 4 + m_fArrowAngle ) * fDia));

	m_tRenderPoint[1].x = (LONG)(fX + (cosf( PI * 3 / 4 + m_fArrowAngle ) * fDia));
	m_tRenderPoint[1].y = (LONG)(fY - (sinf( PI * 3 / 4 + m_fArrowAngle ) * fDia));

	m_tRenderPoint[2].x = (LONG)(fX + (cosf( PI * 7 / 4 + m_fArrowAngle ) * fDia));
	m_tRenderPoint[2].y = (LONG)(fY - (sinf( PI * 7 / 4 + m_fArrowAngle ) * fDia));
}

void CTitanKillBox::OnOverlaped( CObj* _pBlockedObj, DIRECTION _eDir )
{
	if ( m_bIsKillBoxAcive && m_bOverlapeOnce )
	{
		m_pTitan->Set_Dead( true );
		m_pArrow = static_cast<CArrow*>(_pBlockedObj);
		m_pArrow->Set_IsRender( false );
		m_fArrowAngle = m_pArrow->Get_Angle();
		m_pArrow->Set_Pos( m_tInfo.fX, m_tInfo.fY );
		m_pArrow->Stop_Moving();
		m_bIsRender = true;
		m_bOverlapeOnce = false;

		CSoundMgr::Get_Instance()->StopAll();
		TCHAR szBuff[32] = L"Impact.mp3";
		CSoundMgr::Get_Instance()->PlaySound( szBuff, CSoundMgr::TITAN );
	}
}
