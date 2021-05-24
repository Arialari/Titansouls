#include "stdafx.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "Obj.h"

CScrollMgr* CScrollMgr::m_pInstance = nullptr;
CScrollMgr::CScrollMgr()
	: m_fScrollX(0.f), m_fScrollY(0.f), m_fMoveTargetX(0.f), m_fMoveTargetY(0.f), m_pPlayer(nullptr), m_pTitan(nullptr)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Update()
{

	if ( m_pPlayer )
	{
		int iOffSetX = WINCX >> 1;
		int iOffSetY = WINCY >> 1;
		int iScrollX = (int)m_fMoveTargetX;
		int iScrollY = (int)m_fMoveTargetY;

		if ( iOffSetX < (int)(m_pPlayer->Get_Info().fX + iScrollX) )
			CScrollMgr::Get_Instance()->Add_ScrollX( iOffSetX - (m_pPlayer->Get_Info().fX + iScrollX) );

		if ( iOffSetX > ( int )(m_pPlayer->Get_Info().fX + iScrollX) )
			CScrollMgr::Get_Instance()->Add_ScrollX( iOffSetX - (m_pPlayer->Get_Info().fX + iScrollX) );

		if ( iOffSetY < (int)(m_pPlayer->Get_Info().fY + iScrollY) )
			CScrollMgr::Get_Instance()->Add_ScrollY( iOffSetY - (m_pPlayer->Get_Info().fY + iScrollY) );

		if ( iOffSetY > ( int )(m_pPlayer->Get_Info().fY + iScrollY) )
			CScrollMgr::Get_Instance()->Add_ScrollY( iOffSetY - (m_pPlayer->Get_Info().fY + iScrollY) );

	}
}

void CScrollMgr::Late_Update()
{
	m_fScrollX = MyMath::FInterpTo( m_fScrollX, m_fMoveTargetX, DELTATIME_S, 8.f );
	m_fScrollY = MyMath::FInterpTo( m_fScrollY, m_fMoveTargetY, DELTATIME_S, 8.f );
	Scroll_Lock();
}

void CScrollMgr::Force_Set_Scroll( float _x, float _y )
{
	m_fMoveTargetX = _x + (WINCX >> 1);
	m_fMoveTargetY = _y + (WINCY >> 1);
	m_fScrollX = _x + (WINCX >> 1);
	m_fScrollY = _y + (WINCY >> 1);
}

void CScrollMgr::Scroll_Lock()
{
	int iTileX = CTileMgr::Get_Instance()->Get_TileLengthX();
	int iTileY = CTileMgr::Get_Instance()->Get_TileLengthY();

	if ( 0 < m_fMoveTargetX )
		m_fMoveTargetX = 0.f;
	if ( 0 < m_fScrollX )
		m_fScrollX = 0.f;

	if((WINCX - (iTileX * DEFAULTCX)) > m_fMoveTargetX )
		m_fMoveTargetX = (float)(WINCX - (iTileX * DEFAULTCX));
	if ( (WINCX - (iTileX * DEFAULTCX)) > m_fScrollX )
		m_fScrollX = (float)(WINCX - (iTileX * DEFAULTCX));

	if ( 0 < m_fMoveTargetY )
		m_fMoveTargetY = 0.f;
	if ( 0 < m_fScrollY )
		m_fScrollY = 0.f;

	if ( (WINCY - (iTileY * DEFAULTCY)) > m_fMoveTargetY )
		m_fMoveTargetY = (float)(WINCY - (iTileY * DEFAULTCY));
	if ( (WINCY - (iTileY * DEFAULTCY)) > m_fScrollY )
		m_fScrollY = (float)(WINCY - (iTileY * DEFAULTCY));
}

