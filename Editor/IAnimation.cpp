#include "stdafx.h"
#include "IAnimation.h"

IAnimation::IAnimation()
	: m_iFrameidx( 0 ), m_tFrame( {} )
{
}

IAnimation::~IAnimation()
{
}

void IAnimation::Update_Animation_Frame()
{
	if ( m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount() )
	{
		++m_tFrame.iFrameX;

		if ( m_tFrame.iStartX >= m_tFrame.iEndX )
			m_tFrame.iStartX = m_tFrame.iFrameX;

		m_tFrame.dwTime = GetTickCount();
	}
}