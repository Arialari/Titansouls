#include "stdafx.h"
#include "MainGame.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "TileMgr.h"
#include "UiMgr.h"


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
	CBmpMgr::Get_Instance()->Insert_Bmp( L"../Image/w_Overworld.bmp", L"Tile" );

	CSceneMgr::Get_Instance()->Scene_Change( SCENEID::HALLWAY_UNDER );
	CUiMgr::Get_Instance()->Initialize();
}

void CMainGame::Update()
{
	
	if ( CKeyMgr::Get_Instance()->Key_Pressing( 'D' ) )
		CScrollMgr::Get_Instance()->Add_ScrollX( -20.f );
	if ( CKeyMgr::Get_Instance()->Key_Pressing( 'A' ) )
		CScrollMgr::Get_Instance()->Add_ScrollX( 20.f );
	if ( CKeyMgr::Get_Instance()->Key_Pressing( 'W' ) )
		CScrollMgr::Get_Instance()->Add_ScrollY( 20.f );
	if ( CKeyMgr::Get_Instance()->Key_Pressing( 'S' ) )
		CScrollMgr::Get_Instance()->Add_ScrollY( -20.f );
	if ( CKeyMgr::Get_Instance()->Key_Pressing( VK_RIGHT ) )
	{
		CTileMgr::Get_Instance()->Save_Tile();
		CSceneMgr::Get_Instance()->Scene_ChangeToNext();
		return;
	}
	if ( CKeyMgr::Get_Instance()->Key_Pressing( VK_LEFT ) )
	{
		CTileMgr::Get_Instance()->Save_Tile();
		CSceneMgr::Get_Instance()->Scene_ChangeToPrev();
		return;
	}

	CSceneMgr::Get_Instance()->Update();
	CUiMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Late_Update();
	
	//CTileMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	HDC hBackBuffer = CBmpMgr::Get_Instance()->Find_Bmp( L"BackBuffer" );
	HDC hBack = CBmpMgr::Get_Instance()->Find_Bmp( L"Back" );

	BitBlt( hBack, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY );

	CSceneMgr::Get_Instance()->Render( hBack );

	BitBlt( m_hDC, 0, 0, WINCX, WINCY, hBack, 0, 0, SRCCOPY );
	//-------------------DEBUG--------------------------------


	++m_iFPS;
	static int iPrevFPS = 0;
	if ( m_dwFPSTime + 20 < GetTickCount() )
	{
		if ( m_dwFPSTime + 1000 < GetTickCount() )
		{
			iPrevFPS = m_iFPS;
			m_iFPS = 0;
			m_dwFPSTime = GetTickCount();
		}

		POINT	pt = {};
		GetCursorPos( &pt );
		ScreenToClient( g_hWnd, &pt );

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		int		x = pt.x / DEFAULTCX;
		int		y = pt.y / DEFAULTCY;

		bool bIsBlock = CTileMgr::Get_Instance()->Get_PaintIsBlock();

		TCHAR		szFPS[128] = L"";
		swprintf_s( szFPS, L"FPS: %d // Scene : ", iPrevFPS );
		lstrcat( szFPS, CTileMgr::Get_Instance()->Get_FileName() );
		TCHAR		szLayerName[64] = L"";
		swprintf_s( szLayerName, L" // Layer : %d ", CTileMgr::Get_Instance()->Get_TileLayer() );
		TCHAR		szMouseXY[64] = L"";
		swprintf_s( szMouseXY, L" // X : %d, Y : %d ", x, y );
		TCHAR		szIsBlock[32] = L"";
		if( bIsBlock )
			swprintf_s( szIsBlock, L" // IsBlock : True" );
		else
			swprintf_s( szIsBlock, L" // IsBlock : False" );

		lstrcat( szFPS, szLayerName );
		lstrcat( szFPS, szMouseXY );
		lstrcat( szFPS, szIsBlock );
		SetWindowText( g_hWnd, szFPS );
	}

}

void CMainGame::Release()
{
	CKeyMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	CTileMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CUiMgr::Destroy_Instance();
	ReleaseDC( g_hWnd, m_hDC );
}
