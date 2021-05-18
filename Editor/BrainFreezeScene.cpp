#include "stdafx.h"
#include "BrainFreezeScene.h"
#include "TileMgr.h"
#include "ObjMgr.h"

CBrainFreezeScene::CBrainFreezeScene()
{
}

CBrainFreezeScene::~CBrainFreezeScene()
{
	Release();
}

void CBrainFreezeScene::Initialize()
{
	m_iTileX = 100;
	m_iTileY = 100;
	m_pFileName = L"BrainFreeze";
	CTileMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Set_TileLength( m_iTileX, m_iTileY );
	CTileMgr::Get_Instance()->Set_FileName( m_pFileName );
	CTileMgr::Get_Instance()->Create_Tile();
}

void CBrainFreezeScene::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CBrainFreezeScene::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CBrainFreezeScene::Render( HDC _DC )
{
	CTileMgr::Get_Instance()->RenderBackGround( _DC );
	//CTileMgr::Get_Instance()->RenderFoliage( _DC );
	CObjMgr::Get_Instance()->Render( _DC );
	//CTileMgr::Get_Instance()->RenderCelling( _DC );
}

void CBrainFreezeScene::Release()
{
}
