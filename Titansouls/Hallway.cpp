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
	if ( !m_pPlayer )
	{
		m_pPlayer = static_cast<CPlayer*>(CAbstractFactory<CPlayer>::Create( m_fStartPointX, m_fStartPointY ));
		CObjMgr::Get_Instance()->Add_Object( m_pPlayer, OBJID::PLAYER );
	}
	else
	{
		//이전 위치에 따른 플레이어 이동
	}
	CObjMgr::Get_Instance()->Add_Object( CAbstractFactory<CGolLath>::Create(), OBJID::TITAN );
	CObj* pObj = CAbstractFactory<CSceneChanger>::Create(39.5f * DEFAULTCX, 98.5f * DEFAULTCY );
	static_cast<CSceneChanger*>(pObj)->Set_Scene( SCENEID::SLUDGE );
	CObjMgr::Get_Instance()->Add_Object( pObj, OBJID::COLLISION);
}

void CHallway::Update()
{
	CObjMgr::Get_Instance()->Update();
	CUiMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
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
}
