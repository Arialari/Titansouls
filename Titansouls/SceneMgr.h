#pragma once

#ifndef __SCENEMGR_H__
#define __SCENEMGR_H__

class CScene;
class CSceneMgr
{
public:

private:
	CSceneMgr();
	~CSceneMgr();

public:
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();

public:
	void Scene_Change( SCENEID::ID _eID);

public:
	static CSceneMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CSceneMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CSceneMgr* m_pInstance;

	CScene*		m_pScene;

	SCENEID::ID		m_ePreScene;
	SCENEID::ID		m_eCurScene;
};


#endif // !__SCENEMGR_H__
