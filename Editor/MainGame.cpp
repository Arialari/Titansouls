#include "stdafx.h"
#include "MainGame.h"
#include "CollisionMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "TileMgr.h"


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
	CTileMgr::Get_Instance()->Initialize();
}

void CMainGame::Update()
{
	//CTileMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	//CTileMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	HDC hBackBuffer = CBmpMgr::Get_Instance()->Find_Bmp( L"BackBuffer" );
	HDC hBack = CBmpMgr::Get_Instance()->Find_Bmp( L"Back" );

	BitBlt( hBack, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY );

	CTileMgr::Get_Instance()->Render( hBack );

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
	CScrollMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	CTileMgr::Destroy_Instance();
	ReleaseDC( g_hWnd, m_hDC );
}
