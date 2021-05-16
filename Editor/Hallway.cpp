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
	CTileMgr::Get_Instance()->Initialize();
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
	CTileMgr::Get_Instance()->RenderBackGround( _DC );
	//CTileMgr::Get_Instance()->RenderFoliage( _DC );
	CObjMgr::Get_Instance()->Render( _DC );
	//CTileMgr::Get_Instance()->RenderCelling( _DC );
}

void CHallway::Release()
{
}
