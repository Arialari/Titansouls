#include "stdafx.h"
#include "Menu.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CMenu::CMenu()
	:m_iSelect(0)
{
}

CMenu::~CMenu()
{
	Release();
}

void CMenu::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp( L"../Image/Menu1.bmp", L"Menu1" );
	CBmpMgr::Get_Instance()->Insert_Bmp( L"../Image/Menu2.bmp", L"Menu2" );
	TCHAR szBuff[32] = L"Souls.mp3";
	CSoundMgr::Get_Instance()->PlayBGM( szBuff );
}

void CMenu::Update()
{
	if ( CKeyMgr::Get_Instance()->Key_Down( VK_DOWN )
		 || CKeyMgr::Get_Instance()->Key_Down(VK_UP))
	{
		m_iSelect = !m_iSelect;
	}
	if ( CKeyMgr::Get_Instance()->Key_Down( 'X' )
		 || CKeyMgr::Get_Instance()->Key_Down( VK_RETURN ) )
	{
		CSoundMgr::Get_Instance()->StopAll();
		TCHAR szBuff[32] = L"Enter.mp3";
		CSoundMgr::Get_Instance()->PlaySound( szBuff, CSoundMgr::UI );

		if ( m_iSelect == 0 )
			CSceneMgr::Get_Instance()->Scene_Change( SCENEID::HALLWAY_UNDER );
		else
			DestroyWindow( g_hWnd );
	}
}

void CMenu::Late_Update()
{
}

void CMenu::Render( HDC _DC )
{
	HDC hMemDC = nullptr;
	if(m_iSelect == 0 )
		hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( L"Menu1" );
	else if (m_iSelect == 1 )
		hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( L"Menu2" );

	BitBlt( _DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY );
}

void CMenu::Release()
{

}
