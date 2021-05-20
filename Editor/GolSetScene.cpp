#include "stdafx.h"
#include "GolSetScene.h"
#include "TileMgr.h"
#include "ObjMgr.h"

CGolSetScene::CGolSetScene()
{
}

CGolSetScene::~CGolSetScene()
{
	Release();
}

void CGolSetScene::Initialize()
{
	m_iTileX = 100;
	m_iTileY = 100;
	m_pFileName = L"Gol_Lath";
	CTileMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Set_TileLength( m_iTileX, m_iTileY );
	CTileMgr::Get_Instance()->Set_FileName( m_pFileName );
	CTileMgr::Get_Instance()->Create_Tile();
}

void CGolSetScene::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CGolSetScene::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CGolSetScene::Render( HDC _DC )
{
	CTileMgr::Get_Instance()->RenderPaintingTile( _DC );
	//CTileMgr::Get_Instance()->RenderFoliage( _DC );
	CObjMgr::Get_Instance()->Render( _DC );
	//CTileMgr::Get_Instance()->RenderCelling( _DC );
}

void CGolSetScene::Release()
{
}
