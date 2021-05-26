#include "stdafx.h"
#include "EndingScene.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CEndingScene::CEndingScene()
	:m_iPatternFrame(0)
{
}

CEndingScene::~CEndingScene()
{
}

void CEndingScene::Initialize()
{
	CObjMgr::Get_Instance()->Release();
	CBmpMgr::Get_Instance()->Insert_Bmp( L"../Image/Ending.bmp", L"Ending" );
	CSoundMgr::Get_Instance()->StopSound( CSoundMgr::BGM );
	TCHAR szBuff[32] = L"Credits.mp3";
	CSoundMgr::Get_Instance()->PlaySound( szBuff, CSoundMgr::BGM );

	m_iPatternFrame = -100;
}

void CEndingScene::Update()
{
	++m_iPatternFrame;
	if ( CKeyMgr::Get_Instance()->Key_Down( VK_RETURN ) || CKeyMgr::Get_Instance()->Key_Down( VK_SPACE ) || CKeyMgr::Get_Instance()->Key_Down( 'X' ) || CKeyMgr::Get_Instance()->Key_Down( 'C' ) )
	{
		CSoundMgr::Get_Instance()->StopAll();
		CSceneMgr::Get_Instance()->Scene_Change( SCENEID::MENU );
		return;
	}
		
}

void CEndingScene::Late_Update()
{
}

void CEndingScene::Render( HDC _DC )
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( L"Ending" );
	int iY = WINCY - m_iPatternFrame;
	if ( iY < 0 )
		iY = 0;

	BitBlt( _DC, 0, iY, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY );
}

void CEndingScene::Release()
{
}
