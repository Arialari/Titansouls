#pragma once

#ifndef __UIMGR_H__
#define __UIMGR_H__

class CUi;
class CUiMgr
{
private:
	CUiMgr();
	~CUiMgr();
public:
	void Initialize();
	void Release();
	void Update();
	void KeyCheck();
	const bool& Get_IsCollisionVisible() const { return m_bIsCollisionVisible; }
	static CUiMgr* Get_Instance()
	{
		if ( !m_pInstance )
			m_pInstance = new CUiMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE( m_pInstance );
	}
private:
	static CUiMgr* m_pInstance;
	vector<CUi*> m_vecUi[UI_TYPE::UI_TYPE_END];
	bool		m_bIsCollisionVisible;
};

#endif // !__UIMGR_H__