#include "stdafx.h"
#include "SceneChanger.h"
#include "UiMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"

CSceneChanger::CSceneChanger()
{
}

CSceneChanger::~CSceneChanger()
{
}

void CSceneChanger::Initialize()
{
    m_tInfo.iCX = DEFAULTCX*3;
    m_tInfo.iCY = DEFAULTCY;
    m_eRenderID = RENDERID::UI;
    m_vecCollisionRect.reserve( 1 );
    m_vecCollisionRect.emplace_back( RECT() );
}

int CSceneChanger::Update()
{
    if ( m_bDead )
        return OBJ_DEAD;
    return OBJ_NOEVENT;
}

void CSceneChanger::Late_Update()
{
}

void CSceneChanger::Render( HDC _DC )
{
    if ( CUiMgr::Get_Instance()->Get_IsCollisionVisible() )
    {
        int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
        int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
        HBRUSH r_brush = CreateSolidBrush( RGB( 255, 0, 0 ) );
        HGDIOBJ hOldBrush = SelectObject( _DC, r_brush );
        Rectangle( _DC, m_tRect.left + iScrollX + 2, m_tRect.top + iScrollY + 2, m_tRect.right + iScrollX - 2, m_tRect.bottom + iScrollY - 2 );
        SelectObject( _DC, hOldBrush );
        DeleteObject( r_brush );
    }
}

void CSceneChanger::Release()
{
}

void CSceneChanger::Update_ColisionRect()
{
    m_vecCollisionRect.front().left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1));
    m_vecCollisionRect.front().top = (LONG)(m_tInfo.fY - (m_tInfo.iCY >> 1));
    m_vecCollisionRect.front().right = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1));
    m_vecCollisionRect.front().bottom = (LONG)(m_tInfo.fY + (m_tInfo.iCY >> 1));
}

void CSceneChanger::OnBlocked( CObj* _pBlockedObj, DIRECTION _eDir )
{
    CSceneMgr::Get_Instance()->Scene_Change( m_eChangeScene );
}
