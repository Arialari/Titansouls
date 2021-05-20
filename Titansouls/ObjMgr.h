#pragma once

#ifndef __OBJMGR_H__
#define __OBJMGR_H__

class CObj;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	void Update();
	void Late_Update();
	void Render( HDC _DC );
	void Release();
	void Add_Object( CObj* _pObj, OBJID::ID _eID ) { m_listObj[_eID].emplace_back( _pObj ); }

public:
	CObj* Get_Player() const { return m_listObj[OBJID::PLAYER].front(); }
	CObj* Get_Target( CObj* _pObj, OBJID::ID _eID ) const;

public:
	void Delete_ObjID( OBJID::ID _eID );

private:
	void Late_Update_BackGround();

public:
	static CObjMgr* Get_Instance()
	{
		if ( !m_pInstance )
			m_pInstance = new CObjMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE( m_pInstance );
	}

private:
	static CObjMgr* m_pInstance;
	list<CObj*>		m_listObj[OBJID::END];
	list<CObj*>		m_listRender[RENDERID::END];
};

#endif // !__OBJMGR_H__