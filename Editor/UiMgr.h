#pragma once

#ifndef __UIMGR_H__
#define __UIMGR_H__


class CUiMgr
{
private:
	CUiMgr();
	~CUiMgr();
public:
	void Initialize();
	void Update();
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
};

#endif // !__UIMGR_H__