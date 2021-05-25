#include "stdafx.h"
#include "SludgeScene.h"
#include "TileMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "BmpMgr.h"
#include "UiMgr.h"
#include "ScrollMgr.h"
#include "SceneChanger.h"
#include "CGolLath.h"
#include "SoundMgr.h"
#include "SludgeHeart.h"

CSludgeScene::CSludgeScene()
{
}

CSludgeScene::~CSludgeScene()
{
	Release();
}

void CSludgeScene::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp( L"../Image/Background.bmp", L"BackGround" );
	CBmpMgr::Get_Instance()->Insert_Bmp( L"../Image/w_Overworld.bmp", L"Tile" );

	m_iTileX = 100;
	m_iTileY = 100;
	m_pFileName = L"Sludge";
	CTileMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Set_TileLength( m_iTileX, m_iTileY );
	CTileMgr::Get_Instance()->Set_FileName( m_pFileName );
	CTileMgr::Get_Instance()->Create_Tile();
	m_fStartPointX = 39.5f * DEFAULTCX;
	m_fStartPointY = 84.5f * DEFAULTCY;
	if ( !m_pPlayer )
	{
		m_pPlayer = static_cast<CPlayer*>(CAbstractFactory<CPlayer>::Create( m_fStartPointX, m_fStartPointY ));
		CObjMgr::Get_Instance()->Add_Object( m_pPlayer, OBJID::PLAYER );
	}
	CObj* pObj = CAbstractFactory<CSludgeHeart>::Create();
	static_cast<CTitan*>(pObj)->Set_Player( m_pPlayer );
	CObjMgr::Get_Instance()->Add_Object( pObj, OBJID::TITANKILLBOX );

	pObj = CAbstractFactory<CSceneChanger>::Create( 45.5f * DEFAULTCX, 82.5f * DEFAULTCY );
	static_cast<CSceneChanger*>(pObj)->Set_Scene( SCENEID::HALLWAY_UNDER );
	static_cast<CSceneChanger*>(pObj)->Set_TeleportPos( 39.5f * DEFAULTCX, 99.5f * DEFAULTCY );
	CObjMgr::Get_Instance()->Add_Object( pObj, OBJID::COLLISION );
}

void CSludgeScene::Update()
{
	CObjMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Update();
	CUiMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	if ( m_pPlayer->Get_IsDead() )
	{
		CSoundMgr::Get_Instance()->StopSound( CSoundMgr::BGM );
		CSoundMgr::Get_Instance()->StopSound( CSoundMgr::TITANBGM );
	}
}
void CSludgeScene::Late_Update()
{
	// 스크롤 먼저 업데이트 안해주면 타일 컬링에 문제생깁니다.
	CScrollMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
}

void CSludgeScene::Render( HDC _DC )
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( L"BackGround" );

	BitBlt( _DC, 0, 0, WINCX, WINCY, hMemDC, -iScrollX, -iScrollY, SRCCOPY );

	CObjMgr::Get_Instance()->Render( _DC );
}

void CSludgeScene::Release()
{
	for ( int i = 0; i < OBJID::END; ++i )
	{
		if ( i != OBJID::PLAYER && i != OBJID::ARROW )
			CObjMgr::Get_Instance()->Delete_ObjID( (OBJID::ID)i );
	}
	CTileMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->ReleaseRenderList();
	}
