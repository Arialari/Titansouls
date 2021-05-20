#include "stdafx.h"
#include "Hallway.h"
#include "TileMgr.h"
#include "ObjMgr.h"
#include "CGolLath.h"
#include "Player.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CHallway::CHallway()
{
}

CHallway::~CHallway()
{
	Release();
}

void CHallway::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp( L"../Image/Background.bmp", L"BackGround" );
	CBmpMgr::Get_Instance()->Insert_Bmp( L"../Image/w_Overworld.bmp", L"Tile" );
	m_iTileX = 80;
	m_iTileY = 200;
	m_pFileName = L"HallWay";
	CTileMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Set_TileLength( m_iTileX, m_iTileY );
	CTileMgr::Get_Instance()->Set_FileName( m_pFileName );
	CTileMgr::Get_Instance()->Create_Tile();
	CObjMgr::Get_Instance()->Add_Object( CAbstractFactory<CPlayer>::Create(), OBJID::PLAYER );
	CObjMgr::Get_Instance()->Add_Object( CAbstractFactory<CGolLath>::Create(), OBJID::TITAN );
}

void CHallway::Update()
{
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
}

void CHallway::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Late_Update();
}

void CHallway::Render( HDC _DC )
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp( L"BackGround" );

	BitBlt( _DC, 0, 0, WINCX, WINCY, hMemDC, -iScrollX, -iScrollY, SRCCOPY );

	//	CTileMgr::Get_Instance()->Render(_DC);
	CTileMgr::Get_Instance()->RenderPaintingLayerTile( _DC );
//	CTileMgr::Get_Instance()->RenderFoliage( _DC );
	CObjMgr::Get_Instance()->Render( _DC );
//	CTileMgr::Get_Instance()->RenderCelling( _DC );

}

void CHallway::Release()
{
}
