#pragma once

#ifndef __OBJ_H__
#define __OBJ_H__


class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render( HDC _DC ) = 0;
	virtual void Release() = 0;

public:
	//Init SET
	void Set_Pos( float _x, float _y ) { m_tInfo.fX = _x; m_tInfo.fY = _y; }
	void SetReserveCollisionRect( int _i ) { m_tCollisionRect.reserve( _i ); }

	//Functions
	virtual void Hit() { m_bDead = true; }

	//Setter
	void Set_ImageKey( const TCHAR* _pImageKey ) { m_pImageKey = _pImageKey; }
	void Set_DrawID( int _iDrawID ) { m_iDrawID = _iDrawID; }

public:
	//Getter
	const INFO& Get_Info() const { return m_tInfo; }
	const RECT& Get_Rect() const { return m_tRect; }
	const int& Get_DrawID() const { return m_iDrawID; }
	const vector<RECT>& Get_CollisionRect() const { return m_tCollisionRect; }

protected:
	void Update_Rect();

protected:
	INFO			m_tInfo;
	RECT			m_tRect;
	vector<RECT>	m_tCollisionRect;
	bool			m_bDead;
	const TCHAR*	m_pImageKey;
	int				m_iDrawID;
	RENDERID::ID	m_eRenderID;
};


#endif // !__OBJ_H__
