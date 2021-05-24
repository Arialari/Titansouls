#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Hallway.h"
#include "SludgeScene.h"
#include "BrainFreezeScene.h"
#include "EyecubeScene.h"
#include "GolSetScene.h"
#include "TileMgr.h"
#include "Menu.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;
CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_ePreScene( SCENEID::ID::SCENDID_END), m_eCurScene( SCENEID::ID::SCENDID_END )
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC _DC)
{
	m_pScene->Render(_DC);
}

void CSceneMgr::Release()
{
	SAFE_DELETE(m_pScene);
}

void CSceneMgr::Scene_Change( SCENEID::ID _eID)
{
	m_eCurScene = _eID;

	if (m_ePreScene != m_eCurScene)
	{
		Release();
		CTileMgr::Get_Instance()->Release();

		switch (m_eCurScene)
		{
		case SCENEID::ID::MENU:
			m_pScene = new CMenu;
			break;
		case SCENEID::ID::HALLWAY_UNDER:
			m_pScene = new CHallway;
			break;
		case SCENEID::ID::SLUDGE:
			m_pScene = new CSludgeScene;
			break;
		case SCENEID::ID::BARIN_FREEZE:
			m_pScene = new CBrainFreezeScene;
			break;
		case SCENEID::ID::EYE_CUBE:
			m_pScene = new CEyecubeScene;
			break;
		case SCENEID::ID::GOL_SET:
			m_pScene = new CGolSetScene;
			break;
		default:
			break;
		}
		m_pScene->Initialize();
		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Scene_ChangeToNext()
{
	m_eCurScene = (SCENEID::ID)((m_eCurScene + 1) % SCENEID::SCENDID_END);
	Scene_Change( m_eCurScene );
}

void CSceneMgr::Scene_ChangeToPrev()
{
	if( m_eCurScene == 0)
		m_eCurScene = (SCENEID::ID)(SCENEID::SCENDID_END-1);
	else
		m_eCurScene = (SCENEID::ID)(m_eCurScene - 1);
	Scene_Change( m_eCurScene );
}
