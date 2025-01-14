#include "stdafx.h"
#include "ScrollMgr.h"
#include "TileMgr.h"

CScrollMgr* CScrollMgr::m_pInstance = nullptr;
CScrollMgr::CScrollMgr()
	: m_fScrollX(0.f), m_fScrollY(0.f), m_fMoveTargetX(0.f), m_fMoveTargetY(0.f)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Late_Update()
{
	m_fScrollX = MyMath::FInterpTo( m_fScrollX, m_fMoveTargetX, DELTATIME_S, 8.f );
	m_fScrollY = MyMath::FInterpTo( m_fScrollY, m_fMoveTargetY, DELTATIME_S, 8.f );
	Scroll_Lock();
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

