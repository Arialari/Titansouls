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
	CObjMgr::Get_Instance()->Add_Object( CAbstractFactory<CGolLath>::Create(), OBJID::TITAN );
	CObj* pObj = CAbstractFactory<CSceneChanger>::Create( 39.5f * DEFAULTCX, 81.5f * DEFAULTCY );
	static_cast<CSceneChanger*>(pObj)->Set_Scene( SCENEID::HALLWAY_UNDER );
	static_cast<CSceneChanger*>(pObj)->Set_TeleportPos( 39.5f * DEFAULTCX, 99.5f * DEFAULTCY );
	CObjMgr::Get_Instance()->Add_Object( pObj, OBJID::COLLISION );
}

void CSludgeScene::Update()
{
	CObjMgr::Get_Instance()->Update();
	CUiMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
}
void CSludgeScene::Late_Update()
{
	// ��ũ�� ���� ������Ʈ �����ָ� Ÿ�� �ø��� ��������ϴ�.
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
