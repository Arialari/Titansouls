#include "stdafx.h"
#include "SludgeScene.h"
#include "TileMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "UiMgr.h"
#include "ScrollMgr.h"

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
}

void CSludgeScene::Update()
{
	CObjMgr::Get_Instance()->Update();
	CUiMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
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
}
