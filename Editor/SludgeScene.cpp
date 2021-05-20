#include "stdafx.h"
#include "SludgeScene.h"
#include "TileMgr.h"
#include "ObjMgr.h"

CSludgeScene::CSludgeScene()
{
}

CSludgeScene::~CSludgeScene()
{
	Release();
}

void CSludgeScene::Initialize()
{
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
}
void CSludgeScene::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CSludgeScene::Render( HDC _DC )
{
	CTileMgr::Get_Instance()->RenderPaintingTile( _DC );
	//CTileMgr::Get_Instance()->RenderFoliage( _DC );
	CObjMgr::Get_Instance()->Render( _DC );
	//CTileMgr::Get_Instance()->RenderCelling( _DC );
}

void CSludgeScene::Release()
{
}
