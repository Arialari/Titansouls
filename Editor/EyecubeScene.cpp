#include "stdafx.h"
#include "EyecubeScene.h"
#include "ObjMgr.h"
#include "TileMgr.h"

CEyecubeScene::CEyecubeScene()
{
}

CEyecubeScene::~CEyecubeScene()
{
	Release();
}

void CEyecubeScene::Initialize()
{
	m_iTileX = 100;
	m_iTileY = 100;
	m_pFileName = L"EyeCube";
	CTileMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Set_TileLength( m_iTileX, m_iTileY );
	CTileMgr::Get_Instance()->Set_FileName( m_pFileName );
	CTileMgr::Get_Instance()->Create_Tile();
}

void CEyecubeScene::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CEyecubeScene::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CEyecubeScene::Render( HDC _DC )
{
	CTileMgr::Get_Instance()->RenderPaintingTile( _DC );
	//CTileMgr::Get_Instance()->RenderFoliage( _DC );
	CObjMgr::Get_Instance()->Render( _DC );
	//CTileMgr::Get_Instance()->RenderCelling( _DC );
}

void CEyecubeScene::Release()
{
}
