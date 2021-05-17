#include "stdafx.h"
#include "UiMgr.h"
#include "UiButton.h"
#include "UiLayout.h"
#include "UiImage.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"

CUiMgr* CUiMgr::m_pInstance = nullptr;
CUiMgr::CUiMgr()
{
}
CUiMgr::~CUiMgr()
{
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

	pObj = CAbstractFactory<CUiButton>::Create();
	pObj->Set_DrawXID( 1 );
	static_cast<CUiButton*>(pObj)->Set_EventCode( CUi::EVENT_CODE::MOVE_UP );
	static_cast<CUiLayout*>(pLayout)->AttachUi( static_cast<CUi*>(pObj), 0.f, -300.0f );
	CObjMgr::Get_Instance()->Add_Object( pObj, OBJID::UI );

	pObj = CAbstractFactory<CUiButton>::Create();
	pObj->Set_DrawXID( 2 );
	static_cast<CUiButton*>(pObj)->Set_EventCode( CUi::EVENT_CODE::MOVE_RIGHT );
	static_cast<CUiLayout*>(pLayout)->AttachUi( static_cast<CUi*>(pObj), 300.0f, 0.f );
	CObjMgr::Get_Instance()->Add_Object( pObj, OBJID::UI );

	pObj = CAbstractFactory<CUiButton>::Create();
	pObj->Set_DrawXID( 3 );
	static_cast<CUiButton*>(pObj)->Set_EventCode( CUi::EVENT_CODE::MOVE_DOWN );
	static_cast<CUiLayout*>(pLayout)->AttachUi( static_cast<CUi*>(pObj), 0.f, 300.0f );
	CObjMgr::Get_Instance()->Add_Object( pObj, OBJID::UI );

	pObj = CAbstractFactory<CUiImage>::Create();
	pObj->Set_ImageKey( L"Tile" );
	static_cast<CUiImage*>(pObj)->Set_ImageSize( 500, 500 );
	static_cast<CUiLayout*>(pLayout)->AttachUi( static_cast<CUi*>(pObj), 0.f, 0.0f );
	CObjMgr::Get_Instance()->Add_Object( pObj, OBJID::UI );

	CObjMgr::Get_Instance()->Add_Object( pLayout, OBJID::UI );
}

void CUiMgr::Update()
{
	if ( CKeyMgr::Get_Instance()->Key_Down( VK_LBUTTON ) )
	{
		const list<CObj*> listUi = CObjMgr::Get_Instance()->Get_ListUi();
		for ( auto& pUi : listUi )
		{
			if ( static_cast<CUi*>(pUi)->Get_IsHovered() )
			{
				pUi->Hit();
				break;
			}
		}
	}
}
