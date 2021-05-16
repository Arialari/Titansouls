#include "stdafx.h"
#include "TileMgr.h"
#include "Tile.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"

CTileMgr* CTileMgr::m_pInstance = nullptr;
CTileMgr::CTileMgr()
	:m_MemDc(nullptr)
{
	m_vecBackTile.reserve(TILEX * TILEY);
	m_vecFoliageTile.reserve( TILEX * TILEY );
	m_vecCellingTile.reserve( TILEX * TILEY );
	
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp( L"../Image/w_Overworld.bmp", L"Tile" );
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float	fX = (float)((DEFAULTCX >> 1) + (j * DEFAULTCX));
			float	fY = (float)((DEFAULTCY >> 1) + (i * DEFAULTCY));

			m_vecBackTile.emplace_back(CAbstractFactory<CTile>::Create(fX, fY));
			m_vecFoliageTile.emplace_back( CAbstractFactory<CTile>::Create( fX, fY ) );
			m_vecCellingTile.emplace_back( CAbstractFactory<CTile>::Create( fX, fY ) );
		}
	}
	m_MemDc = CBmpMgr::Get_Instance()->Find_Bmp( L"Tile" );
}

void CTileMgr::RenderBackGround(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	int	iCullX = abs( iScrollX / DEFAULTCX );
	int	iCullY = abs( iScrollY / DEFAULTCY );

	int iCullEndX = iCullX + (WINCX / DEFAULTCX) + 2;
	int iCullEndY = iCullY + (WINCY / DEFAULTCY) + 2;


	for ( int i = iCullY; i < iCullEndY; ++i )
	{
		for ( int j = iCullX; j < iCullEndX; ++j )
		{
			int iIdx = i * TILEX + j;

			if ( 0 > iIdx || m_vecBackTile.size() <= (size_t)iIdx )
				continue;

			m_vecBackTile[iIdx]->Render( _DC );
		}
	}
}

void CTileMgr::RenderFoliage( HDC _DC )
{
	for ( auto& pTile : m_vecFoliageTile )
		pTile->Render( _DC );
}

void CTileMgr::RenderCelling( HDC _DC )
{
	for ( auto& pTile : m_vecCellingTile )
		pTile->Render( _DC );
}

void CTileMgr::Release()
{
	for_each( m_vecBackTile.begin(), m_vecBackTile.end(), Safe_Delete<CObj*>);
	m_vecBackTile.clear();
	for_each( m_vecFoliageTile.begin(), m_vecFoliageTile.end(), Safe_Delete<CObj*> );
	m_vecFoliageTile.clear();
	for_each( m_vecCellingTile.begin(), m_vecCellingTile.end(), Safe_Delete<CObj*> );
	m_vecCellingTile.clear();
}

void CTileMgr::Picking_Tile(int _iDrawID)
{
	POINT	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	int		x = pt.x / PIXELCX;
	int		y = pt.y / PIXELCY;

	int		iIdx = y * TILEX + x;

	if (0 > iIdx || m_vecBackTile.size() <= (size_t)iIdx)
		return;

	m_vecBackTile[iIdx]->Set_DrawXID(_iDrawID);
}

void CTileMgr::Save_Tile()
{
	HANDLE hFile = CreateFile(L"../Data/Tile.dat", GENERIC_WRITE
		, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"저장 실패!", L"실패", MB_OK);
		return;
	}

	DWORD	dwByte = 0;

	for (auto& pTile : m_vecBackTile )
	{
		WriteFile(hFile, &pTile->Get_Info(), sizeof(INFO), &dwByte, NULL);
		WriteFile(hFile, &pTile->Get_DrawXID(), sizeof(int), &dwByte, NULL);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"저장 성공!", L"성공", MB_OK);
}

void CTileMgr::Load_Tile()
{
	HANDLE hFile = CreateFile(L"../Data/Tile.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"불러오기 실패!", L"실패", MB_OK);
		return;
	}

	Release();

	DWORD	dwByte = 0;
	INFO	tTemp = {};
	int		iDrawID = 0;

	while (true)
	{
		ReadFile(hFile, &tTemp, sizeof(INFO), &dwByte, NULL);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);

		if (0 == dwByte)
			break;

		CObj* pObj = CAbstractFactory<CTile>::Create(tTemp.fX, tTemp.fY);
		pObj->Set_DrawXID(iDrawID);

		m_vecBackTile.emplace_back(pObj);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"불러오기 성공!", L"성공", MB_OK);
}
