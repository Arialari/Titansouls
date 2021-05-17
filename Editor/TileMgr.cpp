#include "stdafx.h"
#include "TileMgr.h"
#include "Tile.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"

CTileMgr* CTileMgr::m_pInstance = nullptr;
CTileMgr::CTileMgr()
	:m_MemDc( nullptr ), m_tPaintPoint( {} ), m_tPaintEndX(0), m_iTileX(0), m_iTileY(0), m_pFileName(nullptr)
{

	
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	
	m_MemDc = CBmpMgr::Get_Instance()->Find_Bmp( L"Tile" );

	m_tFrame.iFrameX = m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 3628800-1;
	m_tFrame.dwDelay = (DWORD)200.f;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.ePlayType = FRAME::LOOP;
}

void CTileMgr::Update()
{
	if ( CKeyMgr::Get_Instance()->Key_Pressing( VK_CONTROL ) && CKeyMgr::Get_Instance()->Key_Pressing( 'S' ) )
		Save_Tile();
	Update_Animation_Frame();
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
			int iIdx = i * m_iTileX + j;

			if ( 0 > iIdx || m_vecBackTile.size() <= (size_t)iIdx )
				continue;

			m_vecBackTile[iIdx]->Render( _DC );
		}
	}
}

void CTileMgr::RenderFoliage( HDC _DC )
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
			int iIdx = i * m_iTileX + j;

			if ( 0 > iIdx || m_vecFoliageTile.size() <= (size_t)iIdx )
				continue;

			m_vecFoliageTile[iIdx]->Render( _DC );
		}
	}
}

void CTileMgr::RenderCelling( HDC _DC )
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
			int iIdx = i * m_iTileX + j;

			if ( 0 > iIdx || m_vecCellingTile.size() <= (size_t)iIdx )
				continue;

			m_vecCellingTile[iIdx]->Render( _DC );
		}
	}
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

void CTileMgr::Update_Animation_Frame()
{
	if ( m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount() )
	{
		++m_tFrame.iFrameX;
		CTile::Set_iFrameIdx( m_tFrame.iFrameX );

		if ( m_tFrame.iStartX >= m_tFrame.iEndX )
			m_tFrame.iStartX = m_tFrame.iFrameX;

		m_tFrame.dwTime = GetTickCount();
	}

}

void CTileMgr::Create_Tile()
{
	m_vecBackTile.reserve( m_iTileX * m_iTileY );
	m_vecFoliageTile.reserve( m_iTileX * m_iTileY );
	m_vecCellingTile.reserve( m_iTileX * m_iTileY );

	if ( !Load_Tile() )
	{

		for ( int i = 0; i < m_iTileY; ++i )
		{
			for ( int j = 0; j < m_iTileX; ++j )
			{
				float	fX = (float)((DEFAULTCX >> 1) + (j * DEFAULTCX));
				float	fY = (float)((DEFAULTCY >> 1) + (i * DEFAULTCY));

				m_vecBackTile.emplace_back( CAbstractFactory<CTile>::Create( fX, fY ) );
				m_vecFoliageTile.emplace_back( CAbstractFactory<CTile>::Create( fX, fY ) );
				m_vecCellingTile.emplace_back( CAbstractFactory<CTile>::Create( fX, fY ) );
			}
		}
	}
}

void CTileMgr::Picking_Tile()
{
	POINT	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	int		x = pt.x / DEFAULTCX;
	int		y = pt.y / DEFAULTCY;

	int		iIdx = y * m_iTileX + x;

	if (0 > iIdx || m_vecBackTile.size() <= (size_t)iIdx)
		return;

	static_cast<CTile*>(m_vecBackTile[iIdx])->Set_DrawID(m_tPaintPoint.x, m_tPaintPoint.y);
	static_cast<CTile*>(m_vecBackTile[iIdx])->Set_iFrameEndX( m_tPaintEndX );
}

void CTileMgr::Save_Tile()
{
	TCHAR szBuff[32] = L"../Data/";
	TCHAR szEnd[8] = L".dat";
	lstrcat( szBuff, m_pFileName );
	lstrcat( szBuff, szEnd );
	HANDLE hFile = CreateFile( szBuff, GENERIC_WRITE
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
		WriteFile(hFile, &pTile->Get_DrawXID(), sizeof(int), &dwByte, NULL);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"저장 성공!", L"성공", MB_OK);
}

bool CTileMgr::Load_Tile()
{
	TCHAR szBuff[32] = L"../Data/";
	TCHAR szEnd[8] = L".dat";
	lstrcat( szBuff, m_pFileName );
	lstrcat( szBuff, szEnd );
	HANDLE hFile = CreateFile( szBuff, GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"불러오기 실패!", L"실패", MB_OK);
		return false;
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
	return true;
}
