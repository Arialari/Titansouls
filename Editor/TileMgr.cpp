#include "stdafx.h"
#include "TileMgr.h"
#include "Tile.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"

CTileMgr* CTileMgr::m_pInstance = nullptr;
CTileMgr::CTileMgr()
	:m_MemDc( nullptr ), m_tPaintPoint( {} ), m_tPaintEndX(0), m_ePaintRenderID(RENDERID::BACKGROUND)
	, m_iTileX(0), m_iTileY(0), m_pFileName(nullptr), m_bPaintIsBlock(false), m_bGonnaPick(false)
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

void CTileMgr::RenderTile( HDC _DC )
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

			if ( 0 > iIdx || m_vecTile.size() <= (size_t)iIdx )
				continue;

			m_vecTile[iIdx]->Render( _DC );
		}
	}
}

void CTileMgr::Release()
{
	for_each( m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObj*> );
	m_vecTile.clear();
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
	m_vecTile.reserve( m_iTileX * m_iTileY );


	if ( !Load_Tile() )
	{

		for ( int i = 0; i < m_iTileY; ++i )
		{
			for ( int j = 0; j < m_iTileX; ++j )
			{
				float	fX = (float)((DEFAULTCX >> 1) + (j * DEFAULTCX));
				float	fY = (float)((DEFAULTCY >> 1) + (i * DEFAULTCY));

				m_vecTile.emplace_back( CAbstractFactory<CTile>::Create( fX, fY ) );
			}
		}
	}
}

void CTileMgr::Picking_Tile( bool _bIsRender )
{
	if ( !m_bGonnaPick )
		return;
	POINT	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	int		x = pt.x / DEFAULTCX;
	int		y = pt.y / DEFAULTCY;

	int		iIdx = y * m_iTileX + x;

	if (0 > iIdx || m_vecTile.size() <= (size_t)iIdx)
		return;

	static_cast<CTile*>(m_vecTile[iIdx])->Set_DrawID( m_tPaintPoint.x, m_tPaintPoint.y );
	static_cast<CTile*>(m_vecTile[iIdx])->Set_iFrameEndX( m_tPaintEndX );
	static_cast<CTile*>(m_vecTile[iIdx])->Set_IsBlock( m_bPaintIsBlock );
	static_cast<CTile*>(m_vecTile[iIdx])->Set_eRenderId( m_ePaintRenderID );

}

void CTileMgr::Save_Tile()
{
	TCHAR szBuffBack[64] = L"../Data/";
	TCHAR szEndBack[32] = L"BackTile.dat";
	lstrcat( szBuffBack, m_pFileName );
	lstrcat( szBuffBack, szEndBack );
	HANDLE hFileBack = CreateFile( szBuffBack, GENERIC_WRITE
		, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);


	if (INVALID_HANDLE_VALUE == hFileBack )
	{
		MessageBox(g_hWnd, L"저장 실패!", L"실패", MB_OK);
		return;
	}

	DWORD	dwByte = 0;

	for (auto& pTileObj : m_vecTile )
	{
		CTile* pTile = static_cast<CTile*>(pTileObj);
		WriteFile( hFileBack, &pTile->Get_Info(), sizeof(INFO), &dwByte, NULL);
		WriteFile( hFileBack, &pTile->Get_DrawXID(), sizeof(int), &dwByte, NULL);
		WriteFile( hFileBack, &pTile->Get_DrawYID(), sizeof(int), &dwByte, NULL);
		WriteFile( hFileBack, &pTile->Get_iFrameEndX(), sizeof( int ), &dwByte, NULL );
		WriteFile( hFileBack, &pTile->Get_IsRender(), sizeof( bool ), &dwByte, NULL );
		WriteFile( hFileBack, &pTile->Get_IsBlock(), sizeof( bool ), &dwByte, NULL );
	}


	CloseHandle( hFileBack );
	MessageBox(g_hWnd, L"저장 성공!", L"성공", MB_OK);
}

bool CTileMgr::Load_Tile()
{
	TCHAR szBuffBack[64] = L"../Data/";
	TCHAR szEndBack[32] = L"BackTile.dat";
	lstrcat( szBuffBack, m_pFileName );
	lstrcat( szBuffBack, szEndBack );
	HANDLE hFileBack = CreateFile( szBuffBack, GENERIC_READ
								   , NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

	if ( INVALID_HANDLE_VALUE == hFileBack )
	{
		MessageBox(g_hWnd, L"불러오기 실패!", L"실패", MB_OK);
		return false;
	}

	Release();

	DWORD	dwByte = 0;
	INFO	tTemp = {};
	int		iDrawXID = 0;
	int		iDrawYID = 0;
	int		iFrameEndX = 0;
	bool	bIsRender = false;
	bool	bIsBlock = false;

	while (true)
	{
		ReadFile( hFileBack, &tTemp, sizeof(INFO), &dwByte, NULL);
		ReadFile( hFileBack, &iDrawXID, sizeof(int), &dwByte, NULL);
		ReadFile( hFileBack, &iDrawYID, sizeof( int ), &dwByte, NULL );
		ReadFile( hFileBack, &iFrameEndX, sizeof( int ), &dwByte, NULL );
		ReadFile( hFileBack, &bIsRender, sizeof( bool ), &dwByte, NULL );
		ReadFile( hFileBack, &bIsBlock, sizeof( bool ), &dwByte, NULL );


		if (0 == dwByte)
			break;

		CObj* pObj = CAbstractFactory<CTile>::Create(tTemp.fX, tTemp.fY);
		CTile* pTile = static_cast<CTile*>(pObj);
		pTile->Set_DrawXID( iDrawXID );
		pTile->Set_DrawYID( iDrawYID );
		pTile->Set_iFrameEndX( iFrameEndX );
		pTile->Set_IsRender( bIsRender );
		pTile->Set_IsBlock( bIsBlock );

		m_vecTile.emplace_back( pTile );
	}


	CloseHandle( hFileBack );

	if ( m_vecTile.size() == (m_iTileX * m_iTileY))
	{
		
		MessageBox( g_hWnd, L"불러오기 성공!", L"성공", MB_OK );
		return true;
	}
	else
	{
		Release();
		MessageBox( g_hWnd, L"불러오기 정상적이지 않음!", L"비정상", MB_OK );
		return false;
	}
		
}
