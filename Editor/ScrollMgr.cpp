#include "stdafx.h"
#include "ScrollMgr.h"

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
	if (0 < m_fScrollX)
		m_fScrollX = 0.f;

	if((WINCX - (TILEX * DEFAULTCX)) > m_fScrollX)
		m_fScrollX = (float)(WINCX - (TILEX * DEFAULTCX));

	if ( 0 < m_fScrollY )
		m_fScrollY = 0.f;

	if ( (WINCY - (TILEY * DEFAULTCY)) > m_fScrollY )
		m_fScrollY = (float)(WINCY - (TILEY * DEFAULTCY));
}
