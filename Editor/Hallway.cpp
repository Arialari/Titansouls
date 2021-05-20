#include "stdafx.h"
#include "Hallway.h"
#include "TileMgr.h"
#include "ObjMgr.h"

CHallway::CHallway()
{
}

CHallway::~CHallway()
{
	Release();
}

void CHallway::Initialize()
{
	m_iTileX = 80;
	m_iTileY = 200;
	m_pFileName = L"HallWay";
	CTileMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Set_TileLength( m_iTileX, m_iTileY );
	CTileMgr::Get_Instance()->Set_FileName( m_pFileName );
	CTileMgr::Get_Instance()->Create_Tile();
}

void CHallway::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CHallway::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CHallway::Render( HDC _DC )
{
	CTileMgr::Get_Instance()->RenderTile( _DC );
//	CTileMgr::Get_Instance()->RenderFoliage( _DC );
	CObjMgr::Get_Instance()->Render( _DC );
//	CTileMgr::Get_Instance()->RenderCelling( _DC );
}

void CHallway::Release()
{
}
