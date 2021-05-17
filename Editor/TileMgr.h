#pragma once

#ifndef __TILEMGR_H__
#define __TILEMGR_H__

#include "IAnimation.h"
class CTileMgr : public IAnimation
{
private:
	CTileMgr();
	~CTileMgr();

public:
	void Initialize();
	void Update();
	void RenderBackGround(HDC _DC);
	void RenderFoliage( HDC _DC );
	void RenderCelling( HDC _DC );
	void Release();

	virtual void Update_Animation_Frame() override;

public:
	void Create_Tile();
	void Picking_Tile();
	void Save_Tile();
	bool Load_Tile();
	const HDC& Get_DC() const { return m_MemDc; };
	inline void Set_PaintPoint( int _x, int _y ) { m_tPaintPoint.x = _x; m_tPaintPoint.y = _y; }
	inline void Set_PaintEndX( int _x ) { m_tPaintEndX = _x; }
	inline void Set_TileLength( int _x, int _y ) { m_iTileX = _x; m_iTileY = _y; }
public:
	static CTileMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CTileMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CTileMgr*	m_pInstance;
	int					m_iTileX;
	int					m_iTileY;

	vector<CObj*>		m_vecBackTile;
	vector<CObj*>		m_vecFoliageTile;
	vector<CObj*>		m_vecCellingTile;
	HDC					m_MemDc;
	POINT				m_tPaintPoint;
	int					m_tPaintEndX;
};


#endif // !__TILEMGR_H__
