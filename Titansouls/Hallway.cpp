#include "stdafx.h"
#include "Hallway.h"
#include "TileMgr.h"
#include "ObjMgr.h"
#include "CGolLath.h"
#include "Player.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "UiMgr.h"
#include "SceneChanger.h"
#include "SoundMgr.h"
#include "BigDoor.h"

CHallway::CHallway()
{
}

CHallway::~CHallway()
{
	Release();
}

void CHallway::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp( L"../Image/Background.bmp", L"BackGround" );
	CBmpMgr::Get_Instance()->Insert_Bmp( L"../Image/w_Overworld.bmp", L"Tile" );
	m_iTileX = 80;
	m_iTileY = 200;
	m_pFileName = L"HallWay";
	CTileMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Set_TileLength( m_iTileX, m_iTileY );
	CTileMgr::Get_Instance()->Set_FileName( m_pFileName );
	CTileMgr::Get_Instance()->Create_Tile();
	m_fStartPointX = 39.5f * DEFAULTCX;
	m_fStartPointY = 184.5f * DEFAULTCY;
	// ---------------------------------------- Create -------------------------
	if ( !m_pPlayer )
	{
		m_pPlayer = static_cast<CPlayer*>(CAbstractFactory<CPlayer>::Create( m_fStartPointX, m_fStartPointY ));
		CObjMgr::Get_Instance()->Add_Object( m_pPlayer, OBJID::PLAYER );
		CScrollMgr::Get_Instance()->Set_Player( m_pPlayer );

	}

	CObj* pObj = CAbstractFactory<CGolLath>::Create();
	static_cast<CTitan*>(pObj)->Set_Player( m_pPlayer );
	CObjMgr::Get_Instance()->Add_Object( pObj, OBJID::TITAN );
	CScrollMgr::Get_Instance()->Set_Titan( pObj );

	pObj = CAbstractFactory<CSceneChanger>::Create(39.5f * DEFAULTCX, 98.5f * DEFAULTCY );
	static_cast<CSceneChanger*>(pObj)->Set_Scene( SCENEID::SLUDGE );
	static_cast<CSceneChanger*>(pObj)->Set_TeleportPos ( 45.5f * DEFAULTCX, 81.5f * DEFAULTCY );
	CObjMgr::Get_Instance()->Add_Object( pObj, OBJID::COLLISION);

	pObj = CAbstractFactory<CSceneChanger>::Create( 40.5f * DEFAULTCX, 15.5f * DEFAULTCY );
	static_cast<CSceneChanger*>(pObj)->Set_Scene( SCENEID::ENDING );
	static_cast<CSceneChanger*>(pObj)->Set_TeleportPos ( 0, 0 );
	static_cast<CSceneChanger*>(pObj)->Set_SizeX( DEFAULTCX * 11.f );
	static_cast<CSceneChanger*>(pObj)->Update_ColisionRect();
	CObjMgr::Get_Instance()->Add_Object( pObj, OBJID::COLLISION );

	pObj = CAbstractFactory<CBigDoor>::Create( 40.5f * DEFAULTCX, 21.f * DEFAULTCY );
	static_cast<CBigDoor*>(pObj)->Set_Player( m_pPlayer );
	CObjMgr::Get_Instance()->Add_Object( pObj, OBJID::DOOR );
	
	TCHAR bgmName[32] = L"Hallway.mp3";
	CSoundMgr::Get_Instance()->PlayBGM( bgmName );
}

void CHallway::Update()
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

void CHallway::Late_Update()
{
	// 스크롤 먼저 업데이트 안해주면 타일 컬링에 문제생깁니다.
	CScrollMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
}

void CHallway::Render( HDC _DC )
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( L"BackGround" );

	BitBlt( _DC, 0, 0, WINCX, WINCY, hMemDC, -iScrollX, -iScrollY, SRCCOPY );

	CObjMgr::Get_Instance()->Render( _DC );

}

void CHallway::Release()
{
	for ( int i = 0; i < OBJID::END; ++i )
	{
		if( i != OBJID::PLAYER  && i != OBJID::ARROW)
			CObjMgr::Get_Instance()->Delete_ObjID( (OBJID::ID)i );
	}
	CTileMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->ReleaseRenderList();
	CScrollMgr::Get_Instance()->Set_Titan( nullptr );

}
