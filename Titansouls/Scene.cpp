#include "stdafx.h"
#include "Scene.h"

CPlayer* CScene::m_pPlayer = nullptr;
CScene::CScene()
	: m_iTileX( 0 ), m_iTileY( 0 ), m_pFileName( nullptr ), m_fStartPointX(0.f),m_fStartPointY(0.f)
{
}


CScene::~CScene()
{
}


