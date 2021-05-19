#include "stdafx.h"
#include "Stage.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "CGolLath.h"


CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Background.bmp", L"BackGround");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/w_Overworld.bmp", L"Tile");
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CPlayer>::Create(), OBJID::PLAYER);
	CObjMgr::Get_Instance()->Add_Object( CAbstractFactory<CGolLath>::Create(), OBJID::TITAN );

//	CTileMgr::Get_Instance()->Load_Tile();
}

void CStage::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CStage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Late_Update();
}

void CStage::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(L"BackGround");

	BitBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, -iScrollX, -iScrollY, SRCCOPY);

//	CTileMgr::Get_Instance()->Render(_DC);
	CObjMgr::Get_Instance()->Render(_DC);
}

void CStage::Release()
{
}
