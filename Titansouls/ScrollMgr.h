#pragma once

#ifndef __SCROLLMGR_H__
#define __SCROLLMGR_H__


class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();
public:
	void	Update();
	void	Late_Update();

public:
	void Add_ScrollX(float _x) { m_fMoveTargetX += _x; }
	void Add_ScrollY( float _y ) { m_fMoveTargetY += _y; }
	void Set_ScrollX( float _x ) { m_fMoveTargetX = _x + (WINCX >> 1); }
	void Set_ScrollY( float _y ) { m_fMoveTargetY = _y + (WINCY >> 1);	}
	void Force_Set_Scroll( float _x, float _y );
	void Set_Titan( CObj* _pTitan ) { m_pTitan = _pTitan; }
	void Set_Player( CObj* _pPlayer ) { m_pPlayer = _pPlayer; }

public:
	float Get_ScrollX() const { return m_fScrollX; }
	float Get_ScrollY() const { return m_fScrollY; }
	
	float Get_TargetScrollX() const { return m_fMoveTargetX; }
	float Get_TargetScrollY() const { return m_fMoveTargetY; }

private:
	void Scroll_Lock();

public:
	static CScrollMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CScrollMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CScrollMgr* m_pInstance;

	float	m_fScrollX;
	float	m_fScrollY;
	float	m_fMoveTargetX;
	float	m_fMoveTargetY;
	CObj*	m_pPlayer;
	CObj*	m_pTitan;
};


#endif // !__SCROLLMGR_H__
