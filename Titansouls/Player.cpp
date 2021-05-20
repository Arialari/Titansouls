#include "stdafx.h"
#include "Player.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"


CPlayer::CPlayer()
	: m_ePreState( STATE_END ), m_eCurState( STATE_END ), m_eCurDirection(DIRECTION::DIRECTION_END)
	, m_fRunSpeed(3.f), m_fWalkSpeed(15.5f), m_fRollSpeed(4.5f)
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/p_Protagonist.bmp", L"Player");
	CBmpMgr::Get_Instance()->Insert_Bmp( L"../Image/p_Bow.bmp", L"Bow" );
	CBmpMgr::Get_Instance()->Insert_Bmp( L"../Image/p_Arrow.bmp", L"Arrow" );

	m_tInfo.fX = 38.f* DEFAULTCX;
	m_tInfo.fY = 184.f * DEFAULTCY;
	m_tInfo.iCX = DEFAULTCX;
	m_tInfo.iCY = DEFAULTCY;

	m_fSpeed = m_fWalkSpeed;

	m_eCurState = IDLE;
	m_pImageKey = L"Player";
	m_eCurDirection = DIRECTION::N;
	m_eRenderID = RENDERID::OBJECT;
	m_vecCollisionRect.reserve( 1 );
	m_vecCollisionRect.emplace_back( RECT() );
}

int CPlayer::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	Key_Check();
	OffSet();
	State_Change();
	Update_Animation_Frame();

	Update_Rect();
	Update_ColisionRect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
}

void CPlayer::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( m_pImageKey );

	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_tFrame.iFrameX * PIXELCX, m_tFrame.iModelY * PIXELCY
		, PIXELCX, PIXELCY
		, RGB(255, 0, 255));

	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( L"Bow" );

	GdiTransparentBlt( _DC
					   , m_tRect.left + iScrollX, m_tRect.top + iScrollY
					   , m_tInfo.iCX, m_tInfo.iCY
					   , hMemDC
					   , m_tFrame.iFrameX * PIXELCX, m_tFrame.iModelY * PIXELCY
					   , PIXELCX, PIXELCY
					   , RGB( 255, 0, 255 ) );

	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( L"Arrow" );

	GdiTransparentBlt( _DC
					   , m_tRect.left + iScrollX, m_tRect.top + iScrollY
					   , m_tInfo.iCX, m_tInfo.iCY
					   , hMemDC
					   , m_tFrame.iFrameX * PIXELCX, m_tFrame.iModelY * PIXELCY
					   , PIXELCX, PIXELCY
					   , RGB( 255, 0, 255 ) );

	//TCHAR		szBuff[16] = L"";
	//swprintf_s( szBuff, L"Frame X : %d", m_tFrame.iFrameX );
	//TextOut( _DC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, szBuff, lstrlen( szBuff) );

}

void CPlayer::Release()
{
}

void CPlayer::Hit()
{

}

void CPlayer::Key_Check()
{

	if ( m_eCurState != STATE::ROLL )
	{
		if ( CKeyMgr::Get_Instance()->Key_Down( 'X' ) )
		{
			m_fSpeed = m_fRollSpeed;
			m_eCurState = STATE::ROLL;
		}
		else if ( CKeyMgr::Get_Instance()->Key_Pressing( 'X' ) )
		{
			m_fSpeed = m_fRunSpeed;
			m_eCurState = STATE::RUN;
		}
		else
		{
			m_fSpeed = m_fWalkSpeed;
			m_eCurState = STATE::WALK;
		}


		m_fVelocityX = 0.f;
		m_fVelocityY = 0.f;
		if ( CKeyMgr::Get_Instance()->Key_Pressing( VK_LEFT ) )
		{
			if ( CKeyMgr::Get_Instance()->Key_Pressing( VK_UP ) )
			{
				m_fVelocityX = (float)(-m_fSpeed * cosf( PI / 4 ));
				m_fVelocityY = (float)(-m_fSpeed * sinf( PI / 4 ));
				m_eCurDirection = DIRECTION::NW;
			}
			else if ( CKeyMgr::Get_Instance()->Key_Pressing( VK_DOWN ) )
			{
				m_fVelocityX = (float)(-m_fSpeed * cosf( PI / 4 ));
				m_fVelocityY = (float)(m_fSpeed * sinf( PI / 4 ));
				m_eCurDirection = DIRECTION::SW;
			}
			else
			{
				m_fVelocityX = -m_fSpeed;
				m_eCurDirection = DIRECTION::W;
			}
		}
		else if ( CKeyMgr::Get_Instance()->Key_Pressing( VK_RIGHT ) )
		{
			if ( CKeyMgr::Get_Instance()->Key_Pressing( VK_UP ) )
			{
				m_fVelocityX = (float)(m_fSpeed * cosf( PI / 4 ));
				m_fVelocityY = (float)(-m_fSpeed * sinf( PI / 4 ));
				m_eCurDirection = DIRECTION::NE;
			}
			else if ( CKeyMgr::Get_Instance()->Key_Pressing( VK_DOWN ) )
			{
				m_fVelocityX = (float)(m_fSpeed * cosf( PI / 4 ));
				m_fVelocityY = (float)(m_fSpeed * sinf( PI / 4 ));
				m_eCurDirection = DIRECTION::SE;
			}
			else
			{
				m_fVelocityX = m_fSpeed;
				m_eCurDirection = DIRECTION::E;
			}
		}
		else if ( CKeyMgr::Get_Instance()->Key_Pressing( VK_UP ) )
		{
			m_fVelocityY = -m_fSpeed;
			m_eCurDirection = DIRECTION::N;
		}
		else if ( CKeyMgr::Get_Instance()->Key_Pressing( VK_DOWN ) )
		{
			m_fVelocityY = m_fSpeed;
			m_eCurDirection = DIRECTION::S;
		}

	}

	if ( m_fVelocityX == 0.f && m_fVelocityY == 0.f )
	{
		m_eCurState = STATE::IDLE;
	}
		
	m_tInfo.fX += m_fVelocityX;
	m_tInfo.fY += m_fVelocityY;
}

void CPlayer::State_Change()
{
	if (m_ePreState != m_eCurState || m_ePreDirection != m_eCurDirection)
	{
		switch (m_eCurState)
		{
		case STATE::IDLE:
			m_tFrame.iFrameX = m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 1;
			m_tFrame.iModelY = m_eCurDirection;
			m_tFrame.dwDelay = MAXDWORD;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.ePlayType = FRAME::PLAYTYPE::NO_LOOP;
			break;
		case STATE::WALK:
			if ( m_tFrame.iFrameX > 6 )
				m_tFrame.iFrameX = 0;
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 6;
			m_tFrame.iModelY = m_eCurDirection;
			m_tFrame.dwDelay = 100;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.ePlayType = FRAME::PLAYTYPE::LOOP;
			break;
		case STATE::ROLL:
			m_tFrame.iFrameX = m_tFrame.iStartX = 6;
			m_tFrame.iEndX = 11;
			m_tFrame.iModelY = m_eCurDirection;
			m_tFrame.dwDelay = 50;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.ePlayType = FRAME::PLAYTYPE::NO_LOOP;
			break;
		case STATE::RUN:			
			if ( m_tFrame.iFrameX > 6 )
				m_tFrame.iFrameX = 0;
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 6;
			m_tFrame.iModelY = m_eCurDirection;
			m_tFrame.dwDelay = 80;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.ePlayType = FRAME::PLAYTYPE::LOOP;
			break;
		case STATE::AIM:
			break;
		case STATE::DEAD:
			break;
		}
		m_ePreState = m_eCurState;
		m_ePreDirection = m_eCurDirection;
	}
}

void CPlayer::OffSet()
{
	int iOffSetX = WINCX >> 1;
	int iOffSetY = WINCY >> 1;
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_TargetScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_TargetScrollY();

	if ( iOffSetX < (int)(m_tInfo.fX + iScrollX))
		CScrollMgr::Get_Instance()->Add_ScrollX( iOffSetX - (m_tInfo.fX + iScrollX));

	if ( iOffSetX > ( int )(m_tInfo.fX + iScrollX))
		CScrollMgr::Get_Instance()->Add_ScrollX( iOffSetX - (m_tInfo.fX + iScrollX));

	if ( iOffSetY < (int)(m_tInfo.fY + iScrollY) )
		CScrollMgr::Get_Instance()->Add_ScrollY( iOffSetY - (m_tInfo.fY + iScrollY) );

	if ( iOffSetY > ( int )( m_tInfo.fY + iScrollY ) )
		CScrollMgr::Get_Instance()->Add_ScrollY( iOffSetY - (m_tInfo.fY + iScrollY) );
}

void CPlayer::Update_Animation_Frame()
{
	if ( m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount() )
	{
		++m_tFrame.iFrameX;
		switch ( m_tFrame.ePlayType )
		{
		case FRAME::PLAYTYPE::LOOP :
			if ( m_tFrame.iFrameX >= m_tFrame.iEndX )
				m_tFrame.iFrameX = m_tFrame.iStartX;
			break;
		case FRAME::PLAYTYPE::NO_LOOP:
			if ( m_tFrame.iFrameX >= m_tFrame.iEndX )
			{
				if ( m_eCurState == STATE::ROLL )
				{
					m_eCurState = STATE::WALK;
					return;
				}
				m_tFrame.iFrameX = m_tFrame.iEndX - 1;
			}
			break;
		case FRAME::PLAYTYPE::REVERSE_NO_LOOP:
			break;
		default:
			break;
		}

		m_tFrame.dwTime = GetTickCount();
	}
}

void CPlayer::Update_ColisionRect()
{
	m_vecCollisionRect.front().left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1));
	m_vecCollisionRect.front().top = (LONG)(m_tInfo.fY - (m_tInfo.iCY >> 1));
	m_vecCollisionRect.front().right = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1));
	m_vecCollisionRect.front().bottom = (LONG)(m_tInfo.fY + (m_tInfo.iCY >> 1));
}

