#include "stdafx.h"
#include "UiMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "TileMgr.h"

CUiMgr* CUiMgr::m_pInstance = nullptr;
CUiMgr::CUiMgr()
	:m_bIsCollisionVisible(true)
{
}
CUiMgr::~CUiMgr()
{
	Release();
}

void CUiMgr::Initialize()
{

}

void CUiMgr::Release()
{
	for ( auto& vector : m_vecUi )
		vector.clear();
}

void CUiMgr::Update()
{
	KeyCheck();
}

void CUiMgr::KeyCheck()
{
	//if ( CKeyMgr::Get_Instance()->Key_Down( VK_LBUTTON ) )
	//{
	//	for ( auto& vector : m_vecUi )
	//	{
	//		for ( auto& pUi : vector )
	//		{
	//			if ( pUi->Get_IsHovered() && pUi->Get_IsVisible() )
	//			{
	//				pUi->Hit();
	//				break;
	//			}
	//		}
	//	}
	//}
	//if ( CKeyMgr::Get_Instance()->Key_Pressing( VK_LBUTTON ) )
	//{
	//	bool	bIsHitUi = false;
	//	for ( auto& vector : m_vecUi )
	//	{
	//		for ( auto& pUi : vector )
	//		{
	//			if ( pUi->Get_IsHovered() && pUi->Get_IsVisible() )
	//			{
	//				bIsHitUi = true;
	//				break;
	//			}
	//		}
	//		if ( bIsHitUi )
	//			break;
	//	}
	//	if ( !bIsHitUi )
	//		CTileMgr::Get_Instance()->Picking_Tile( true );
	//}
	//if ( CKeyMgr::Get_Instance()->Key_Pressing( VK_RBUTTON ) )
	//{
	//	CTileMgr::Get_Instance()->Picking_Tile( false );
	//}
	//if ( CKeyMgr::Get_Instance()->Key_Down( 'B' ) )
	//	CTileMgr::Get_Instance()->Toggle_PaintIsBlock();

	//if ( CKeyMgr::Get_Instance()->Key_Down( VK_SPACE ) )
	//{
	//	m_vecUi[UI_TYPE::LAYOUT].front()->Toggle_IsVisible();
	//}
	//if ( CKeyMgr::Get_Instance()->Key_Down( VK_UP ) )
	//{
	//	int iTileLayer = (CTileMgr::Get_Instance()->Get_TileLayer() + 1) % (CTileMgr::TILE_LAYER::TILE_LAYER_END + 1);
	//	CTileMgr::Get_Instance()->Set_TileLayer( (CTileMgr::TILE_LAYER)iTileLayer );
	//}
	//if ( CKeyMgr::Get_Instance()->Key_Down( VK_DOWN ) )
	//{
	//	int iTileLayer = (CTileMgr::Get_Instance()->Get_TileLayer() - 1);
	//	if ( iTileLayer < 0 )
	//		CTileMgr::Get_Instance()->Set_TileLayer( CTileMgr::TILE_LAYER::TILE_LAYER_END );
	//	else
	//		CTileMgr::Get_Instance()->Set_TileLayer( (CTileMgr::TILE_LAYER)iTileLayer );
	//}
	if ( CKeyMgr::Get_Instance()->Key_Down( VK_F1 ) )
		m_bIsCollisionVisible = !m_bIsCollisionVisible;
}
