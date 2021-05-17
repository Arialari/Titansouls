#include "stdafx.h"
#include "UiMgr.h"
#include "UiButton.h"
#include "UiLayout.h"
#include "UiImage.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "TileMgr.h"

CUiMgr* CUiMgr::m_pInstance = nullptr;
CUiMgr::CUiMgr()
{
}
CUiMgr::~CUiMgr()
{
	Release();
}

void CUiMgr::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp( L"../Image/p_MyUIButton.bmp", L"UIButton" );

	CObj* pLayout = CAbstractFactory<CUiLayout>::Create(400.f, 300.f);
	static_cast<CUiLayout*>(pLayout)->ReserveAttachSize( 5 );

	CObj* pObj = CAbstractFactory<CUiButton>::Create();
	pObj->Set_DrawXID( 0 );
	static_cast<CUiButton*>(pObj)->Set_EventCode( CUi::EVENT_CODE::MOVE_LEFT );
	static_cast<CUiLayout*>(pLayout)->AttachUi( static_cast<CUi*>(pObj), -300.0f, 0.f );
	CObjMgr::Get_Instance()->Add_Object( pObj, OBJID::UI );
	m_vecUi[UI_TYPE::BUTTON].emplace_back( static_cast<CUiButton*>(pObj) );

	pObj = CAbstractFactory<CUiButton>::Create();
	pObj->Set_DrawXID( 1 );
	static_cast<CUiButton*>(pObj)->Set_EventCode( CUi::EVENT_CODE::MOVE_UP );
	static_cast<CUiLayout*>(pLayout)->AttachUi( static_cast<CUi*>(pObj), 0.f, -300.0f );
	CObjMgr::Get_Instance()->Add_Object( pObj, OBJID::UI );
	m_vecUi[UI_TYPE::BUTTON].emplace_back( static_cast<CUiButton*>(pObj) );

	pObj = CAbstractFactory<CUiButton>::Create();
	pObj->Set_DrawXID( 2 );
	static_cast<CUiButton*>(pObj)->Set_EventCode( CUi::EVENT_CODE::MOVE_RIGHT );
	static_cast<CUiLayout*>(pLayout)->AttachUi( static_cast<CUi*>(pObj), 300.0f, 0.f );
	CObjMgr::Get_Instance()->Add_Object( pObj, OBJID::UI );
	m_vecUi[UI_TYPE::BUTTON].emplace_back( static_cast<CUiButton*>(pObj) );

	pObj = CAbstractFactory<CUiButton>::Create();
	pObj->Set_DrawXID( 3 );
	static_cast<CUiButton*>(pObj)->Set_EventCode( CUi::EVENT_CODE::MOVE_DOWN );
	static_cast<CUiLayout*>(pLayout)->AttachUi( static_cast<CUi*>(pObj), 0.f, 300.0f );
	CObjMgr::Get_Instance()->Add_Object( pObj, OBJID::UI );
	m_vecUi[UI_TYPE::BUTTON].emplace_back( static_cast<CUiButton*>(pObj) );

	pObj = CAbstractFactory<CUiImage>::Create();
	pObj->Set_ImageKey( L"Tile" );
	static_cast<CUiImage*>(pObj)->Set_ImageSize( 500, 500 );
	static_cast<CUiLayout*>(pLayout)->AttachUi( static_cast<CUi*>(pObj), 0.f, 0.0f );
	CObjMgr::Get_Instance()->Add_Object( pObj, OBJID::UI );
	m_vecUi[UI_TYPE::IMAGE].emplace_back( static_cast<CUiImage*>(pObj) );

	CObjMgr::Get_Instance()->Add_Object( pLayout, OBJID::UI );
	m_vecUi[UI_TYPE::LAYOUT].emplace_back( static_cast<CUiLayout*>(pLayout) );
}

void CUiMgr::Release()
{
	for ( auto& vector : m_vecUi )
		vector.clear();
}

void CUiMgr::Update()
{

	if ( CKeyMgr::Get_Instance()->Key_Down( VK_LBUTTON ) )
	{
		for ( auto& vector : m_vecUi )
		{
			for ( auto& pUi : vector )
			{
				if ( pUi->Get_IsHovered() && pUi->Get_IsVisible() )
				{
					pUi->Hit();
					break;
				}
			}
		}
	}
	if ( CKeyMgr::Get_Instance()->Key_Pressing( VK_LBUTTON ) )
	{
		bool	bIsHitUi = false;
		for ( auto& vector : m_vecUi )
		{
			for ( auto& pUi : vector )
			{
				if ( pUi->Get_IsHovered() && pUi->Get_IsVisible() )
				{
					bIsHitUi = true;
					break;
				}
			}
			if ( bIsHitUi )
				break;
		}
		if ( !bIsHitUi )
			CTileMgr::Get_Instance()->Picking_Tile();
	}


	if ( CKeyMgr::Get_Instance()->Key_Down( VK_SPACE ) )
	{
		m_vecUi[UI_TYPE::LAYOUT].front()->Toggle_IsVisible();
	}
}
