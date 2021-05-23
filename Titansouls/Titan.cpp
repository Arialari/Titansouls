#include "stdafx.h"
#include "Titan.h"
#include "Arrow.h"

CTitan::CTitan()
	:m_bActive(false), m_fPosZ(0.f)
{
}

CTitan::~CTitan()
{
}

void CTitan::Initialize()
{
}

int CTitan::Update()
{
	return 0;
}

void CTitan::Late_Update()
{
}

void CTitan::Render( HDC _DC )
{
}

void CTitan::Release()
{
}

void CTitan::Update_ColisionRect()
{
}

void CTitan::OnBlocked( CObj* _pBlockedObj, DIRECTION _eDir)
{
	if ( dynamic_cast<CArrow*>(_pBlockedObj) )
		if ( !m_bDead && static_cast<CArrow*>(_pBlockedObj)->Get_IsDamage() )
			m_bActive = true;
}

void CTitan::OnOverlaped( CObj* _pBlockedObj, DIRECTION _eDir )
{
	
}

void CTitan::Update_DamageCollision()
{
	if ( m_fPosZ == 0 )
	{
		if ( !m_bIsCheckBlock )
			m_bIsCheckOverlape = true;
		m_bIsCheckBlock = true;
	}
	else
	{
		m_bIsCheckBlock = false;
		m_bIsCheckOverlape = false;
	}
}
