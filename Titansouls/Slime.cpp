#include "stdafx.h"
#include "Slime.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SlimeShadow.h"
#include "SludgeHeart.h"
#include "ObjMgr.h"
#include "Player.h"
#include "SoundMgr.h"

int CSlime::m_iSoundNumber = 0;
const int CSlime::m_iSizeStartX[5] = { 0, 10, 15, 18, 20 };
const int CSlime::m_iSize[5] = { 8, 5, 3, 2, 1 };
const float CSlime::m_fMozziMinX = 0.6f;
const float CSlime::m_fMozziMinY = 0.5f;
CSlime::CSlime()
	:m_pShadow(nullptr), m_iSizeLv(0), m_bHaveHeart(false), m_fMozziY(false), m_fMozziX(false)
	, m_fTargetX(0), m_fTargetY(0), m_bIsHomingPlayer(true), m_iShakeStartFrame(0)
{
}

CSlime::~CSlime()
{
	Release();
}

void CSlime::Initialize()
{
	m_iMaxCX = m_iSize[m_iSizeLv] * DEFAULTCX;
	m_iMaxCY = m_iSize[m_iSizeLv] * DEFAULTCY;
	m_tInfo.iCX = m_iMaxCX;
	m_tInfo.iCY = m_iMaxCY;
	Update_Rect();
	m_pImageKey = L"Sludge";
	m_eRenderID = RENDERID::OBJECT;
	m_fPosZ = 30.f;
	m_iPatternFrame = 10 + rand() % 20;

	m_pShadow = static_cast<CSlimeShadow*>(CAbstractFactory<CSlimeShadow>::Create( m_tInfo.fX, m_tInfo.fY ));
	m_pShadow->Set_Slime( this );
	CObjMgr::Get_Instance()->Add_Object( m_pShadow, OBJID::SHADOW );
}

int CSlime::Update()
{
	
	if ( m_bDestroyed || m_bDead )
	{
		m_pSludeHeart->EraseSlime( m_iterThis );
		return OBJ_DESTROYED;
	}
		

	m_pShadow->Set_SludgeHeart( m_pSludeHeart );
	++m_iPatternFrame;

	//점프 점프
	
	int iCurPatternFrame = m_iPatternFrame % 100;
	if ( iCurPatternFrame < 50 )
		m_fPosZ = DEFAULTCY * 3 * sin( iCurPatternFrame * PI / 50 );
	else
		m_fPosZ = 0.f;

	if ( m_bHaveHeart )
		m_pSludeHeart->Set_PosZ( m_fPosZ );

	if(m_bHaveHeart )
		Update_Heart();
	Update_Shadow();
	Update_Mozzi();

	if ( !m_bDead )
	{
		Update_Pattern();
		Update_DamageCollision();
	}
	else
	{
		Update_Dead();
	}
	Update_Rect();


	return OBJ_NOEVENT;
}

void CSlime::Late_Update()
{
	if (!m_bDead && m_iSizeLv < 2 )
	{
		int iCurPatternFrame = m_iPatternFrame % 100;
		if ( iCurPatternFrame == 50 )
		{
			m_iShakeStartFrame = m_iPatternFrame;

		}
		if ( m_iPatternFrame > m_iShakeStartFrame && m_iPatternFrame < m_iShakeStartFrame + 10 )
		{
			int iDeltaFrame = m_iPatternFrame - m_iShakeStartFrame;
			int sign = ((iDeltaFrame) % 3 - 1);
			CScrollMgr::Get_Instance()->Force_Add_Scroll( ( (20.f - iDeltaFrame) * sign) / (m_iSizeLv + 1), 0.f );
		}
	}
	if ( !m_bDead )
	{
		int iCurPatternFrame = m_iPatternFrame % 100;
		if ( iCurPatternFrame == 50 )
		{
			CSoundMgr::Get_Instance()->StopSound( CSoundMgr::CHANNELID( m_iSoundNumber + 5 ) );
			TCHAR szBuff[32];
			if ( m_iSizeLv == 0 )
				lstrcpy( szBuff, L"Biggest1.mp3" );
			else if ( m_iSizeLv == 1 )
				lstrcpy( szBuff, L"Big1.mp3" );
			else if ( m_iSizeLv == 2 )
				lstrcpy( szBuff, L"Medium1.mp3" );
			else if ( m_iSizeLv == 3 )
				lstrcpy( szBuff, L"Small1.mp3" );
			else if ( m_iSizeLv == 4 )
				lstrcpy( szBuff, L"Smallest1.mp3" );

			CSoundMgr::Get_Instance()->PlaySound( szBuff, CSoundMgr::CHANNELID( m_iSoundNumber + 5 ) );
			m_iSoundNumber = ((m_iSoundNumber + 1) % 16);
		}
	}
}

void CSlime::Render( HDC _DC )
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( m_pImageKey );


	Update_Rect();

	GdiTransparentBlt( _DC
				   , m_tRect.left + iScrollX, (int)(m_tRect.top + iScrollY - (m_tInfo.iCY >> 1) - m_fPosZ)
				   , m_tInfo.iCX, m_tInfo.iCY
				   , hMemDC
				   , m_iSizeStartX[m_iSizeLv] * PIXELCX, 0
				   , PIXELCX* m_iSize[m_iSizeLv], PIXELCY* m_iSize[m_iSizeLv]
				   , RGB( 255, 0, 255 ) );
	RenderCollision( _DC );
}

void CSlime::Release()
{
}

void CSlime::Set_ThisIter( list<CSlime*>::iterator _iter )
{
	m_iterThis = _iter; m_pShadow->Set_Slimeiter( _iter );
}

void CSlime::Set_iSizeLv( int _iSizeLv )
{
	m_iSizeLv = _iSizeLv;
	m_pShadow->Set_iSizeLv( m_iSizeLv );
}

void CSlime::Set_Active()
{
	m_bActive = true;
	m_pShadow->Set_Active();
}

void CSlime::Reset_Size()
{
	m_iMaxCX = m_iSize[m_iSizeLv] * DEFAULTCX;
	m_iMaxCY = m_iSize[m_iSizeLv] * DEFAULTCY;
	m_tInfo.iCX = m_iMaxCX;
	m_tInfo.iCY = m_iMaxCY;
	Update_Rect();
	m_pShadow->Reset_Size();
}

void CSlime::Set_Dead( bool _bDead )
{
	m_bDead = true;
	m_pShadow->Set_Dead( true );
}

void CSlime::Update_DamageCollision()
{
	if ( m_fPosZ <= 2.f && m_fPosZ >= -2.f )
	{
		m_bIsCheckOverlape = true;
		m_pShadow->Set_IsCheckOverlap( true );
	}
	else
	{
		m_bIsCheckOverlape = false;
		m_pShadow->Set_IsCheckOverlap( false );
	}
}

void CSlime::Update_Dead()
{
	m_pShadow->Set_Dead( true );
	m_bDestroyed = true;
}

void CSlime::Update_Pattern()
{
	int iCurPatternFrame = m_iPatternFrame % 100;
	if ( iCurPatternFrame == 0 )
	{
		m_fTargetX = m_pPlayer->Get_Info().fX;
		m_fTargetY = m_pPlayer->Get_Info().fY + DEFAULTCY;
	}
	if ( !m_fTargetX && !m_fTargetY )
	{
		m_fTargetX = m_tInfo.fX + rand() % DEFAULTCX - (DEFAULTCX >> 1);
		m_fTargetY = m_tInfo.fY + rand() % DEFAULTCY - (DEFAULTCY >> 1);
	}

	if ( iCurPatternFrame < 50 )
	{
		if ( m_bActive )
		{
			float fDiffX = m_fTargetX - m_tInfo.fX;
			float fDiffY = m_fTargetY - m_tInfo.fY;
			float fDeltaX = 0.f;
			float fDeltaY = 0.f;
			if ( sqrtf( fDiffX * fDiffX + fDiffY * fDiffY ) < sqrtf( 25 * DEFAULTCX * DEFAULTCX + 25 * DEFAULTCY * DEFAULTCY ) )
			{

				fDeltaX = MyMath::Clamp<float>( m_fTargetX - m_tInfo.fX, -0.7f * (m_iSizeLv + 1) - 2.f, 0.7f * (m_iSizeLv + 1) + 2.f );
				fDeltaY = MyMath::Clamp<float>( m_fTargetY - m_tInfo.fY, -0.7f * (m_iSizeLv + 1) - 2.f, 0.7f * (m_iSizeLv + 1) + 2.f );
				m_tInfo.fX += fDeltaX;
				m_tInfo.fY += fDeltaY;
			}
			else
			{
				if ( !m_bHaveHeart )
				{
					if ( m_bIsHomingPlayer )
					{
						m_fTargetX = m_tInfo.fX + (rand() % 3 - 1) * 5 * DEFAULTCX;
						m_fTargetY = m_tInfo.fY + (rand() % 3 - 1) * 5 * DEFAULTCY;
						m_bIsHomingPlayer = false;
					}

					fDeltaX = MyMath::Clamp<float>( m_fTargetX - m_tInfo.fX, -0.7f * (m_iSizeLv + 1) - 2.f, 0.7f * (m_iSizeLv + 1) + 2.f );
					fDeltaY = MyMath::Clamp<float>( m_fTargetY - m_tInfo.fY, -0.7f * (m_iSizeLv + 1) - 2.f, 0.7f * (m_iSizeLv + 1) + 2.f );
					m_tInfo.fX += fDeltaX;
					m_tInfo.fY += fDeltaY;

					if ( sqrtf( fDeltaX * fDeltaX + fDeltaY * fDeltaY ) < DEFAULTCX * 1.414f )
						m_bIsHomingPlayer = true;
				}
				else
				{
					fDeltaX = -MyMath::Clamp<float>( m_fTargetX - m_tInfo.fX, -1.f, 1.f );
					fDeltaY = -MyMath::Clamp<float>( m_fTargetY - m_tInfo.fY, -1.f, 1.f );
					m_tInfo.fX += fDeltaX;
					m_tInfo.fY += fDeltaY;
				}

			}
			if ( m_tInfo.fX < 32 * DEFAULTCY )
			{
				m_tInfo.fX = 32 * DEFAULTCY;
				m_bIsHomingPlayer = true;
			}
			if ( m_tInfo.fX > 59 * DEFAULTCY )
			{
				m_tInfo.fX = 59 * DEFAULTCY;
				m_bIsHomingPlayer = true;
			}
			if ( m_tInfo.fY < 40 * DEFAULTCY )
			{
				m_tInfo.fY = 40 * DEFAULTCY;
				m_bIsHomingPlayer = true;
			}
			if ( m_tInfo.fY > 59 * DEFAULTCY )
			{
				m_tInfo.fY = 59 * DEFAULTCY;
				m_bIsHomingPlayer = true;
			}
				

			if ( m_bHaveHeart )
				m_pSludeHeart->Set_Pos( m_tInfo.fX, m_tInfo.fY );
		}
	}
}

void CSlime::Update_Shadow()
{
	m_pShadow->Set_Pos( m_tInfo.fX, m_tInfo.fY );
	m_pShadow->Set_iSizeLv( m_iSizeLv );
}

void CSlime::Update_Heart()
{
	m_pSludeHeart->Set_Pos( m_tInfo.fX, m_tInfo.fY + 1 );
	m_pSludeHeart->Set_PosZ( m_fPosZ + (m_tInfo.iCY >> 2) );
}

void CSlime::Update_Mozzi()
{
	int iCurPatternFrame = m_iPatternFrame % 100;

	if ( iCurPatternFrame < 30 )
	{
		m_fMozziX = MyMath::FInterpTo( m_fMozziX, m_fMozziMinX, DELTATIME_S, (iCurPatternFrame + 40) / 8.f);
		m_fMozziY = MyMath::FInterpTo( m_fMozziY, 1.f, DELTATIME_S, (iCurPatternFrame+40) / 8.f );
		m_tInfo.iCX = m_iMaxCX * m_fMozziX;
		m_pShadow->Set_MozziX( m_fMozziX );
		m_tInfo.iCY = m_iMaxCY * m_fMozziY;
		m_pShadow->Set_MozziY( m_fMozziY );
	}
	else if ( iCurPatternFrame < 60 )
	{
		m_fMozziX = MyMath::FInterpTo( m_fMozziX, 1.f, DELTATIME_S, (iCurPatternFrame + 10) / 8.f );
		m_fMozziY = MyMath::FInterpTo( m_fMozziY, m_fMozziMinY, DELTATIME_S, (iCurPatternFrame + 10) / 8.f );
		m_tInfo.iCX = m_iMaxCX * m_fMozziX;
		m_pShadow->Set_MozziX( m_fMozziX );
		m_tInfo.iCY = m_iMaxCY * m_fMozziY;
		m_pShadow->Set_MozziY( m_fMozziY );
	}
	else if (iCurPatternFrame < 70 )
	{
		m_fMozziX = MyMath::FInterpTo( m_fMozziX, 0.9f, DELTATIME_S, iCurPatternFrame / 8.f );
		m_fMozziY = MyMath::FInterpTo( m_fMozziY, 0.9f, DELTATIME_S, iCurPatternFrame / 8.f );
		m_tInfo.iCX = m_iMaxCX * m_fMozziX;
		m_pShadow->Set_MozziX( m_fMozziX );
		m_tInfo.iCY = m_iMaxCY * m_fMozziY;
		m_pShadow->Set_MozziY( m_fMozziY );
	}
	else if ( iCurPatternFrame > 85 )
	{
		m_fMozziX = MyMath::FInterpTo( m_fMozziX, 1.f, DELTATIME_S, iCurPatternFrame / 8.f );
		m_fMozziY = MyMath::FInterpTo( m_fMozziY, m_fMozziMinY, DELTATIME_S, iCurPatternFrame / 8.f );
		m_tInfo.iCX = m_iMaxCX * m_fMozziX;
		m_pShadow->Set_MozziX( m_fMozziX );
		m_tInfo.iCY = m_iMaxCY * m_fMozziY;
		m_pShadow->Set_MozziY( m_fMozziY );
	}
}
