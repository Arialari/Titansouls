#include "stdafx.h"
#include "SludgeHeart.h"
#include "SludgeHeartShadow.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Slime.h"
#include "ObjMgr.h"

CSludgeHeart::CSludgeHeart()
	:m_pShadow(nullptr), m_bAlone(false)
{
	
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
	
	m_pSlime.reserve( 16 );
	m_pSlime.emplace_back(static_cast<CSlime*>(CAbstractFactory<CSlime>::Create(m_tInfo.fX,m_tInfo.fY)));
	m_pSlime[0]->Set_SludgeHeart( this );
	m_pSlime[0]->Set_HaveHeart();
	CObjMgr::Get_Instance()->Add_Object( m_pSlime[0], OBJID::TITAN );

	m_pShadow =  static_cast<CSludgeHeartShadow*>(CAbstractFactory<CSludgeHeartShadow>::Create( m_tInfo.fX, m_tInfo.fY ) );
	CObjMgr::Get_Instance()->Add_Object( m_pShadow, OBJID::SHADOW );
}

int CSludgeHeart::Update()
{
	if ( m_bDestroyed )
		return OBJ_DESTROYED;

	++m_iPatternFrame;
	if ( m_iPatternFrame == 1 )
		m_pSlime[0]->Set_Player( m_pPlayer );

	if ( !m_bDead )
	{
		Update_Pattern();
		Update_DamageCollision();
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
}

void CSludgeHeart::Release()
{
}

void CSludgeHeart::Set_Active()
{
	m_bActive = true;
	m_pShadow->Set_Active();
	for ( auto& pSlime : m_pSlime )
		pSlime->Set_Active();
}

void CSludgeHeart::Create_Slime(float _x, float _y, int _iSizeLv )
{
	CSlime* pSlime = static_cast<CSlime*>(CAbstractFactory<CSlime>::Create(_x,_y));
	pSlime->Set_SludgeHeart( this );
	pSlime->Set_Player( m_pPlayer );
	pSlime->Set_iSizeLv( _iSizeLv );
	m_pSlime.emplace_back( pSlime );
	CObjMgr::Get_Instance()->Add_Object( pSlime , OBJID::TITAN);
	pSlime->Reset_Size();
}

void CSludgeHeart::Update_Dead()
{
	for ( auto& pSlime : m_pSlime )
	{
		pSlime->Set_Dead(true);
	}
}

void CSludgeHeart::Update_Pattern()
{
}
