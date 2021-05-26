#include "stdafx.h"
#include "SludgeHeart.h"
#include "SludgeHeartShadow.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Slime.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Arrow.h"
#include "SoundMgr.h"

CSludgeHeart::CSludgeHeart()
	:m_pShadow( nullptr ), m_bAlone( false ), m_fArrowAngle( 0.f ), m_pArrow(nullptr)
{
	ZeroMemory( m_tRenderPoint, sizeof( m_tRenderPoint ) );
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
	m_bIsCheckBlock = false;
	m_bIsRender = false;
	
	m_pSlime.emplace_back(static_cast<CSlime*>(CAbstractFactory<CSlime>::Create(m_tInfo.fX,m_tInfo.fY)));
	m_pSlime.back()->Set_SludgeHeart( this );
	m_pSlime.back()->Set_HaveHeart();
	m_pSlime.back()->Set_ThisIter(m_pSlime.begin() );
	CObjMgr::Get_Instance()->Add_Object( m_pSlime.back(), OBJID::TITAN );

	m_pShadow =  static_cast<CSludgeHeartShadow*>(CAbstractFactory<CSludgeHeartShadow>::Create( m_tInfo.fX, m_tInfo.fY ) );
	CObjMgr::Get_Instance()->Add_Object( m_pShadow, OBJID::SHADOW );
}

int CSludgeHeart::Update()
{
	if ( m_bDestroyed )
		return OBJ_DESTROYED;

	++m_iPatternFrame;
	if ( m_iPatternFrame == 1 )
		m_pSlime.back()->Set_Player( m_pPlayer );

	if ( !m_bDead )
	{
		Update_Pattern();
		Update_DamageCollision();
		Update_ColisionRect();
	}
	else
	{
		Update_Dead();
	}

	return OBJ_NOEVENT;
}

void CSludgeHeart::Late_Update()
{
}

void CSludgeHeart::Render( HDC _DC )
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( m_pImageKey );
	Update_Rect();

	GdiTransparentBlt( _DC
					   , m_tRect.left + iScrollX, (int)(m_tRect.top + iScrollY - DEFAULTCY - m_fPosZ)
					   , m_tInfo.iCX, m_tInfo.iCY
					   , hMemDC
					   , 24 * PIXELCX, m_iFrameidx * 2 * PIXELCY
					   , PIXELCX * 2, PIXELCY * 2
					   , RGB( 255, 0, 255 ) );

	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( L"Player" );

	if ( m_bIsRender )
	{
		Update_RenderPoint();

		int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
		HDC hPlgDC = CBmpMgr::Get_Instance()->Find_Bmp( L"Plg" );
		HDC hResetDC = CBmpMgr::Get_Instance()->Find_Bmp( L"Reset" );

		PlgBlt( hPlgDC, m_tRenderPoint
				, hMemDC
				, 30 * PIXELCX, PIXELCY
				, PIXELCX, PIXELCY
				, NULL, NULL, NULL );

		GdiTransparentBlt( _DC
						   , m_tRect.left + iScrollX, m_tRect.top + iScrollY - DEFAULTCY
						   , DEFAULTCX, DEFAULTCY
						   , hPlgDC
						   , 0, 0
						   , PIXELCX, PIXELCY
						   , RGB( 255, 0, 255 ) );
		BitBlt( hPlgDC, 0, 0, PIXELCX, PIXELCY, hResetDC, 0, 0, SRCCOPY );
	}


	RenderCollision(_DC);
}

void CSludgeHeart::Release()
{
}

void CSludgeHeart::Set_Active()
{
	if ( !m_bActive )
	{
		m_bActive = true;
		m_pShadow->Set_Active();

		auto iter = m_pSlime.begin();
		while ( iter != m_pSlime.end() && iter._Ptr != nullptr )
		{
			(*iter)->Set_Active();
			++iter;
		}
		CSoundMgr::Get_Instance()->StopSound( CSoundMgr::TITANBGM );
		CSoundMgr::Get_Instance()->StopSound( CSoundMgr::BGM );
		TCHAR szBuff[32] = L"Sludgeheart.mp3";
		CSoundMgr::Get_Instance()->PlayBGM( szBuff );
	}

}

void CSludgeHeart::Update_ColisionRect()
{
	if ( !m_bDead && m_bIsCheckOverlape && m_bAlone )
	{
		m_vecCollisionRect.front().left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1));
		m_vecCollisionRect.front().top = (LONG)(m_tInfo.fY - m_tInfo.iCY);
		m_vecCollisionRect.front().right = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1));
		m_vecCollisionRect.front().bottom = (LONG)(m_tInfo.fY);
	}
	else
	{
		m_vecCollisionRect.front().left = (LONG)0;
		m_vecCollisionRect.front().top = (LONG)0;
		m_vecCollisionRect.front().right = (LONG)0;
		m_vecCollisionRect.front().bottom = (LONG)0;
	}
}

void CSludgeHeart::Set_Alone()
{
	m_bAlone = true;
	m_pShadow->Set_Alone();
	m_iPatternFrame = 15;
	m_bIsCheckOverlape = false;
}

void CSludgeHeart::Update_DamageCollision()
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

void CSludgeHeart::OnOverlaped( CObj* _pBlockedObj, DIRECTION _eDir )
{
	if ( !m_bDead )
	{
		if ( dynamic_cast<CPlayer*>(_pBlockedObj) )
		{
			_pBlockedObj->Set_Dead( true );
		}
		else if ( dynamic_cast<CArrow*>(_pBlockedObj) )
		{

			m_pArrow = static_cast<CArrow*>(_pBlockedObj);

			if ( m_pArrow->Get_IsDamage() )
				m_bDead = true;
			CSoundMgr::Get_Instance()->StopAll();
			TCHAR szBuff[32] = L"Impact.mp3";
			CSoundMgr::Get_Instance()->PlaySound( szBuff, CSoundMgr::TITAN );

	
			m_pArrow->Set_IsRender( false );
			m_fArrowAngle = m_pArrow->Get_Angle();
			m_pArrow->Set_Pos( m_tInfo.fX, m_tInfo.fY );
			m_pArrow->Stop_Moving();
			m_bIsRender = true;
		}
	}

}

void CSludgeHeart::Create_Slime( float _x, float _y, int _iSizeLv, bool _bHaveHeart )
{
	CSlime* pSlime = static_cast<CSlime*>(CAbstractFactory<CSlime>::Create(_x,_y));
	if ( _bHaveHeart )
	{
		pSlime->Set_HaveHeart();
	}
		
	pSlime->Set_SludgeHeart( this );
	pSlime->Set_Player( m_pPlayer );
	pSlime->Set_Active();
	pSlime->Set_iSizeLv( _iSizeLv );
	m_pSlime.emplace_back( pSlime );
	pSlime->Set_ThisIter( --m_pSlime.end() );
	CObjMgr::Get_Instance()->Add_Object( pSlime , OBJID::TITAN);
	pSlime->Reset_Size();
}

void CSludgeHeart::Update_Dead()
{
	auto iter = m_pSlime.begin();
	while(iter != m_pSlime.end() && iter._Ptr != nullptr )
	{
		(*iter)->Set_Dead(true);
		++iter;
	}
	if ( m_pArrow && m_pArrow->Get_IsDamage() )
	{
		m_bIsRender = false;
		m_pArrow->Set_IsRender( true );
	}
}

void CSludgeHeart::Update_Pattern()
{
	if ( m_bAlone )
	{
		int iCurPatternFrame = m_iPatternFrame % 50;
		if ( iCurPatternFrame < 30 )
		{
			m_fPosZ = DEFAULTCY * 1 * sin( iCurPatternFrame * PI / 30 );
			if( m_fPosZ > (DEFAULTCY>>1) )
				m_iFrameidx = 4;
			else
				m_iFrameidx = 3;
		}
		else
		{
			m_fPosZ = 0.f;
			m_iFrameidx = 2;
		}
	}
}

void CSludgeHeart::Update_RenderPoint()
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

