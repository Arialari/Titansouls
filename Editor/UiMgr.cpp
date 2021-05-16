#include "stdafx.h"
#include "UiMgr.h"
#include "UiButton.h"
#include "BmpMgr.h"
#include "ObjMgr.h"

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
	CObj* pObj = CAbstractFactory<CUiButton>::Create();
	pObj->Set_DrawXID( 0 );
	CObjMgr::Get_Instance()->Add_Object( pObj, OBJID::UI );
	pObj = CAbstractFactory<CUiButton>::Create();
	pObj->Set_DrawXID( 1 );
	CObjMgr::Get_Instance()->Add_Object( pObj, OBJID::UI );
	pObj = CAbstractFactory<CUiButton>::Create();
	pObj->Set_DrawXID( 2 );
	CObjMgr::Get_Instance()->Add_Object( pObj, OBJID::UI );
	pObj = CAbstractFactory<CUiButton>::Create();
	pObj->Set_DrawXID( 3 );
	CObjMgr::Get_Instance()->Add_Object( pObj, OBJID::UI );

}
