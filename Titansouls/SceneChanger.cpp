#include "stdafx.h"
#include "SceneChanger.h"
#include "UiMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

CSceneChanger::CSceneChanger()
    :m_bIsChange(false), m_pPlayer(nullptr), m_fTeleportX(0.f), m_fTeleportY(0.f)
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
    if ( m_bDestroyed )
        return OBJ_DESTROYED;

    return OBJ_NOEVENT;
    
}

void CSceneChanger::Late_Update()
{
    if ( m_bIsChange )
    {
        m_pPlayer->Set_Pos( m_fTeleportX,  m_fTeleportY );
        CSceneMgr::Get_Instance()->Scene_Change( m_eChangeScene );
        return;
    }
}

void CSceneChanger::Render( HDC _DC )
{

    RenderCollision( _DC );
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

}

void CSceneChanger::OnOverlaped( CObj* _pBlockedObj, DIRECTION _eDir )
{
    CSoundMgr::Get_Instance()->StopAll();
    m_bIsChange = true;
    m_pPlayer = _pBlockedObj;
    TCHAR szBuff[32] = L"Enter.mp3";
    CSoundMgr::Get_Instance()->PlaySound( szBuff, CSoundMgr::UI );

}
