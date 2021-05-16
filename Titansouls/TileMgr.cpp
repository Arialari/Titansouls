#include "stdafx.h"
#include "TileMgr.h"
#include "Tile.h"
#include "ScrollMgr.h"

CTileMgr* CTileMgr::m_pInstance = nullptr;
CTileMgr::CTileMgr()
{
	m_vecTile.reserve(TILEX * TILEY);
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float	fX = (float)((PIXELCX >> 1) + (j * PIXELCX));
			float	fY = (float)((PIXELCY >> 1) + (i * PIXELCY));

			m_vecTile.emplace_back(CAbstractFactory<CTile>::Create(fX, fY));
		}
	}
}

void CTileMgr::Render(HDC _DC)
{
	for (auto& pTile : m_vecTile)
		pTile->Render(_DC);
}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObj*>);
	m_vecTile.clear();
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

	if (0 > iIdx || m_vecTile.size() <= (size_t)iIdx)
		return;

	m_vecTile[iIdx]->Set_DrawXID(_iDrawID);
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

	for (auto& pTile : m_vecTile)
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

		m_vecTile.emplace_back(pObj);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"불러오기 성공!", L"성공", MB_OK);
}
