#include "stdafx.h"
#include "TileMgr.h"
#include "Tile.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"

CTileMgr* CTileMgr::m_pInstance = nullptr;
CTileMgr::CTileMgr()
	:m_MemDc( nullptr ), m_tPaintPoint( {} ), m_tPaintEndX(0), m_iTileX(0), m_iTileY(0), m_pFileName(nullptr), m_ePaintLayer(TILE_LAYER::BACKGROUND), m_bPaintIsBlock(false)
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
	//if ( CKeyMgr::Get_Instance()->Key_Pressing( VK_CONTROL ) && CKeyMgr::Get_Instance()->Key_Pressing( 'S' ) )
	//	Save_Tile();
	Update_Animation_Frame();
}

void CTileMgr::RenderPaintingLayerTile(HDC _DC)
{
	if ( m_ePaintLayer == TILE_LAYER::TILE_LAYER_END )
	{
		RenderTile( _DC );
		return;
	}

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

			if ( 0 > iIdx || m_vecTile[m_ePaintLayer].size() <= (size_t)iIdx )
				continue;

			m_vecTile[m_ePaintLayer][iIdx]->Render( _DC );
		}
	}
}

void CTileMgr::RenderTile( HDC _DC )
{
	for ( int iTileLayer = 0; iTileLayer < TILE_LAYER::TILE_LAYER_END; ++iTileLayer )
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

				if ( 0 > iIdx || m_vecTile[iTileLayer].size() <= (size_t)iIdx )
					continue;

				m_vecTile[iTileLayer][iIdx]->Render( _DC );
			}
		}
	}

}

void CTileMgr::Release()
{
	for ( auto& vector : m_vecTile )
	{
		for_each( vector.begin(), vector.end(), Safe_Delete<CObj*> );
		vector.clear();
	}
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
	for ( auto& vector : m_vecTile )
	{
		vector.reserve( m_iTileX * m_iTileY );
	}

	if ( !Load_Tile() )
	{

		for ( int i = 0; i < m_iTileY; ++i )
		{
			for ( int j = 0; j < m_iTileX; ++j )
			{
				float	fX = (float)((DEFAULTCX >> 1) + (j * DEFAULTCX));
				float	fY = (float)((DEFAULTCY >> 1) + (i * DEFAULTCY));

				m_vecTile[TILE_LAYER::BACKGROUND].emplace_back( CAbstractFactory<CTile>::Create( fX, fY ) );
				m_vecTile[TILE_LAYER::FOLIAGE].emplace_back( CAbstractFactory<CTile>::Create( fX, fY, false ) );
				m_vecTile[TILE_LAYER::CELLING].emplace_back( CAbstractFactory<CTile>::Create( fX, fY, false ) );
			}
		}
	}
}

void CTileMgr::Picking_Tile( bool _bIsRender )
{
	if ( m_ePaintLayer == TILE_LAYER_END )
		return;
	POINT	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	int		x = pt.x / DEFAULTCX;
	int		y = pt.y / DEFAULTCY;

	int		iIdx = y * m_iTileX + x;

	if (0 > iIdx || m_vecTile[m_ePaintLayer].size() <= (size_t)iIdx)
		return;
	if ( _bIsRender )
	{
		static_cast<CTile*>(m_vecTile[m_ePaintLayer][iIdx])->Set_DrawID( m_tPaintPoint.x, m_tPaintPoint.y );
		static_cast<CTile*>(m_vecTile[m_ePaintLayer][iIdx])->Set_iFrameEndX( m_tPaintEndX );
		static_cast<CTile*>(m_vecTile[TILE_LAYER::BACKGROUND][iIdx])->Set_IsBlock( m_bPaintIsBlock );
	}		
	static_cast<CTile*>(m_vecTile[m_ePaintLayer][iIdx])->Set_IsRender( _bIsRender );

}

//void CTileMgr::Save_Tile()
//{
//	TCHAR szBuffBack[64] = L"../Data/";
//	TCHAR szEndBack[32] = L"BackTile.dat";
//	lstrcat( szBuffBack, m_pFileName );
//	lstrcat( szBuffBack, szEndBack );
//	HANDLE hFileBack = CreateFile( szBuffBack, GENERIC_WRITE
//		, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//
//	TCHAR szBuffFoliage[64] = L"../Data/";
//	TCHAR szEndFoliage[32] = L"Foliage.dat";
//	lstrcat( szBuffFoliage, m_pFileName );
//	lstrcat( szBuffFoliage, szEndFoliage );
//	HANDLE hFileFoliage = CreateFile( szBuffFoliage, GENERIC_WRITE
//							   , NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
//
//	TCHAR szBuffCelling[64] = L"../Data/";
//	TCHAR szEndCelling[32] = L"Celling.dat";
//	lstrcat( szBuffCelling, m_pFileName );
//	lstrcat( szBuffCelling, szEndCelling );
//	HANDLE hFileCelling = CreateFile( szBuffCelling, GENERIC_WRITE
//							   , NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
//
//
//	if (INVALID_HANDLE_VALUE == hFileBack || INVALID_HANDLE_VALUE == hFileFoliage || INVALID_HANDLE_VALUE  == hFileCelling )
//	{
//		MessageBox(g_hWnd, L"저장 실패!", L"실패", MB_OK);
//		return;
//	}
//
//	DWORD	dwByte = 0;
//
//	for (auto& pTileObj : m_vecTile[TILE_LAYER::BACKGROUND] )
//	{
//		CTile* pTile = static_cast<CTile*>(pTileObj);
//		WriteFile( hFileBack, &pTile->Get_Info(), sizeof(INFO), &dwByte, NULL);
//		WriteFile( hFileBack, &pTile->Get_DrawXID(), sizeof(int), &dwByte, NULL);
//		WriteFile( hFileBack, &pTile->Get_DrawYID(), sizeof(int), &dwByte, NULL);
//		WriteFile( hFileBack, &pTile->Get_iFrameEndX(), sizeof( int ), &dwByte, NULL );
//		WriteFile( hFileBack, &pTile->Get_IsRender(), sizeof( bool ), &dwByte, NULL );
//		WriteFile( hFileBack, &pTile->Get_IsBlock(), sizeof( bool ), &dwByte, NULL );
//	}
//	for ( auto& pTileObj : m_vecTile[TILE_LAYER::FOLIAGE] )
//	{
//		CTile* pTile = static_cast<CTile*>(pTileObj);
//		WriteFile( hFileFoliage, &pTile->Get_Info(), sizeof( INFO ), &dwByte, NULL );
//		WriteFile( hFileFoliage, &pTile->Get_DrawXID(), sizeof( int ), &dwByte, NULL );
//		WriteFile( hFileFoliage, &pTile->Get_DrawYID(), sizeof( int ), &dwByte, NULL );
//		WriteFile( hFileFoliage, &pTile->Get_iFrameEndX(), sizeof( int ), &dwByte, NULL );
//		WriteFile( hFileFoliage, &pTile->Get_IsRender(), sizeof( bool ), &dwByte, NULL );
//	}
//	for ( auto& pTileObj : m_vecTile[TILE_LAYER::CELLING] )
//	{
//		CTile* pTile = static_cast<CTile*>(pTileObj);
//		WriteFile( hFileCelling, &pTile->Get_Info(), sizeof( INFO ), &dwByte, NULL );
//		WriteFile( hFileCelling, &pTile->Get_DrawXID(), sizeof( int ), &dwByte, NULL );
//		WriteFile( hFileCelling, &pTile->Get_DrawYID(), sizeof( int ), &dwByte, NULL );
//		WriteFile( hFileCelling, &pTile->Get_iFrameEndX(), sizeof( int ), &dwByte, NULL );
//		WriteFile( hFileCelling, &pTile->Get_IsRender(), sizeof( bool ), &dwByte, NULL );
//	}
//
//	CloseHandle( hFileBack );
//	CloseHandle( hFileFoliage );
//	CloseHandle( hFileCelling );
//	MessageBox(g_hWnd, L"저장 성공!", L"성공", MB_OK);
//}

bool CTileMgr::Load_Tile()
{
	TCHAR szBuffBack[64] = L"../Data/";
	TCHAR szEndBack[32] = L"BackTile.dat";
	lstrcat( szBuffBack, m_pFileName );
	lstrcat( szBuffBack, szEndBack );
	HANDLE hFileBack = CreateFile( szBuffBack, GENERIC_READ
								   , NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

	TCHAR szBuffFoliage[64] = L"../Data/";
	TCHAR szEndFoliage[32] = L"Foliage.dat";
	lstrcat( szBuffFoliage, m_pFileName );
	lstrcat( szBuffFoliage, szEndFoliage );
	HANDLE hFileFoliage = CreateFile( szBuffFoliage, GENERIC_READ
									  , NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

	TCHAR szBuffCelling[64] = L"../Data/";
	TCHAR szEndCelling[32] = L"Celling.dat";
	lstrcat( szBuffCelling, m_pFileName );
	lstrcat( szBuffCelling, szEndCelling );
	HANDLE hFileCelling = CreateFile( szBuffCelling, GENERIC_READ
									  , NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

	if ( INVALID_HANDLE_VALUE == hFileBack || INVALID_HANDLE_VALUE == hFileFoliage || INVALID_HANDLE_VALUE == hFileCelling )
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

		m_vecTile[TILE_LAYER::BACKGROUND].emplace_back( pTile );
	}
	while ( true )
	{
		ReadFile( hFileFoliage, &tTemp, sizeof( INFO ), &dwByte, NULL );
		ReadFile( hFileFoliage, &iDrawXID, sizeof( int ), &dwByte, NULL );
		ReadFile( hFileFoliage, &iDrawYID, sizeof( int ), &dwByte, NULL );
		ReadFile( hFileFoliage, &iFrameEndX, sizeof( int ), &dwByte, NULL );
		ReadFile( hFileFoliage, &bIsRender, sizeof( bool ), &dwByte, NULL );

		if ( 0 == dwByte )
			break;

		CObj* pObj = CAbstractFactory<CTile>::Create( tTemp.fX, tTemp.fY );
		CTile* pTile = static_cast<CTile*>(pObj);
		pTile->Set_DrawXID( iDrawXID );
		pTile->Set_DrawYID( iDrawYID );
		pTile->Set_iFrameEndX( iFrameEndX );
		pTile->Set_IsRender( bIsRender );

		m_vecTile[TILE_LAYER::FOLIAGE].emplace_back( pTile );
	}
	while ( true )
	{
		ReadFile( hFileCelling, &tTemp, sizeof( INFO ), &dwByte, NULL );
		ReadFile( hFileCelling, &iDrawXID, sizeof( int ), &dwByte, NULL );
		ReadFile( hFileCelling, &iDrawYID, sizeof( int ), &dwByte, NULL );
		ReadFile( hFileCelling, &iFrameEndX, sizeof( int ), &dwByte, NULL );
		ReadFile( hFileCelling, &bIsRender, sizeof( bool ), &dwByte, NULL );


		if ( 0 == dwByte )
			break;

		CObj* pObj = CAbstractFactory<CTile>::Create( tTemp.fX, tTemp.fY );
		CTile* pTile = static_cast<CTile*>(pObj);
		pTile->Set_DrawXID( iDrawXID );
		pTile->Set_DrawYID( iDrawYID );
		pTile->Set_iFrameEndX( iFrameEndX );
		pTile->Set_IsRender( bIsRender );

		m_vecTile[TILE_LAYER::CELLING].emplace_back( pTile );
	}

	CloseHandle( hFileBack );
	CloseHandle( hFileFoliage );
	CloseHandle( hFileCelling );

	if ( m_vecTile[TILE_LAYER::BACKGROUND].size() == (m_iTileX * m_iTileY)
		 || m_vecTile[TILE_LAYER::FOLIAGE].size() == (m_iTileX * m_iTileY)
		 || m_vecTile[TILE_LAYER::CELLING].size() == (m_iTileX * m_iTileY) )
	{
		
		//MessageBox( g_hWnd, L"불러오기 성공!", L"성공", MB_OK );
		return true;
	}
	else
	{
		Release();
		MessageBox( g_hWnd, L"불러오기 정상적이지 않음!", L"비정상", MB_OK );
		return false;
	}
		
}
