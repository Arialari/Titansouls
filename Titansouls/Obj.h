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
	inline void Set_Pos( float _x, float _y ) { m_tInfo.fX = _x; m_tInfo.fY = _y; }
	inline void Set_PosX( float _x ) { m_tInfo.fX = _x; }
	inline void Set_PosY( float _y ) { m_tInfo.fY = _y; }
	inline void Add_Pos( float _x, float _y ) { m_tInfo.fX += _x; m_tInfo.fY += _y; }
	inline void Add_PosX( float _x ) { m_tInfo.fX += _x; }
	inline void Add_PosY( float _y ) { m_tInfo.fY += _y; }
	inline void SetReserveCollisionRect( int _i ) { m_vecCollisionRect.reserve( _i ); }

	//Functions
	virtual void Hit() { m_bDead = true; }

	//Setter
	inline void Set_ImageKey( const TCHAR* _pImageKey ) { m_pImageKey = _pImageKey; }
	inline void Set_DrawXID( int _iDrawID ) { m_iDrawXID = _iDrawID; }

public:
	//Getter
	const INFO& Get_Info() const { return m_tInfo; }
	const RECT& Get_Rect() const { return m_tRect; }
	const int& Get_DrawXID() const { return m_iDrawXID; }
	const RENDERID::ID& Get_RenderID() const { return m_eRenderID; }
	const vector<RECT>& Get_CollisionRect() const { return m_vecCollisionRect; }

protected:
	void Update_Rect();
	virtual void Update_ColisionRect() = 0;

protected:
	INFO			m_tInfo;
	RECT			m_tRect;
	vector<RECT>	m_vecCollisionRect;
	bool			m_bDead;
	const TCHAR*	m_pImageKey;
	int				m_iDrawXID;
	RENDERID::ID	m_eRenderID;
};

#endif // !__OBJ_H__