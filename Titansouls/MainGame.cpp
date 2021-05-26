#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "CollisionMgr.h"
//#include "Mouse.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "TileMgr.h"
#include "UiMgr.h"
#include "SoundMgr.h"


CMainGame::CMainGame()
	: m_hDC(NULL), m_iFPS( 0 ), m_dwFPSTime( GetTickCount() )
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC( g_hWnd );
	CBmpMgr::Get_Instance()->Insert_Bmp( L"../Image/BackBuffer.bmp", L"BackBuffer" );
	CBmpMgr::Get_Instance()->Insert_Bmp( L"../Image/Back.bmp", L"Back" );
	CSoundMgr::Get_Instance()->Initialize();
	CSceneMgr::Get_Instance()->Scene_Change( SCENEID::ID::MENU );
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	HDC hBackBuffer = CBmpMgr::Get_Instance()->Find_Bmp( L"BackBuffer" );
	HDC hBack = CBmpMgr::Get_Instance()->Find_Bmp( L"Back" );

	BitBlt( hBack, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY );

	CSceneMgr::Get_Instance()->Render( hBack );

	BitBlt( m_hDC, 0, 0, WINCX, WINCY, hBack, 0, 0, SRCCOPY );

	++m_iFPS;
	if ( m_dwFPSTime + 1000 < GetTickCount() )
	{
		TCHAR		szFPS[16] = L"";
		swprintf_s( szFPS, L"FPS: %d", m_iFPS );
		SetWindowText( g_hWnd, szFPS );

		m_iFPS = 0;
		m_dwFPSTime = GetTickCount();
	}
}

void CMainGame::Release()
{
	CKeyMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CTileMgr::Destroy_Instance();
	CUiMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CSoundMgr::Destroy_Instance();
	ReleaseDC( g_hWnd, m_hDC );
}
