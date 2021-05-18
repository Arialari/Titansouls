#pragma once

#ifndef __TILEMGR_H__
#define __TILEMGR_H__

#include "IAnimation.h"
class CTileMgr : public IAnimation
{
public :
	enum TILE_LAYER {BACKGROUND, FOLIAGE, CELLING, TILE_LAYER_END };
private:
	CTileMgr();
	~CTileMgr();

public:
	void Initialize();
	void Update();
	void RenderPaintingLayerTile( HDC _DC );
	void RenderTile( HDC _DC );
	void Release();

	virtual void Update_Animation_Frame() override;

public:
	void Create_Tile();
	void Picking_Tile(bool _bIsRender);
	void Set_FileName( const TCHAR* _pName ) { m_pFileName = _pName; }
	void Save_Tile();
	bool Load_Tile();
	const HDC& Get_DC() const { return m_MemDc; };
	inline void Set_PaintPoint( int _x, int _y ) { m_tPaintPoint.x = _x; m_tPaintPoint.y = _y; }
	inline void Set_PaintEndX( int _x ) { m_tPaintEndX = _x; }
	inline void Set_TileLength( int _x, int _y ) { m_iTileX = _x; m_iTileY = _y; }
	inline const int& Get_TileLengthX() const { return m_iTileX; }
	inline const int& Get_TileLengthY() const { return m_iTileY; }
	inline const TCHAR* Get_FileName() const { return m_pFileName; }
	inline void Set_TileLayer( TILE_LAYER _eTile ) { m_ePaintLayer = _eTile;  }
	inline const TILE_LAYER& Get_TileLayer() { return m_ePaintLayer; }
	inline void Toggle_PaintIsBlock() { m_bPaintIsBlock = !m_bPaintIsBlock; }
	inline const bool& Get_PaintIsBlock() { return m_bPaintIsBlock; }
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

	vector<CObj*>		m_vecTile[TILE_LAYER_END];
	HDC					m_MemDc;
	POINT				m_tPaintPoint;
	int					m_tPaintEndX;
	const TCHAR*		m_pFileName;
	TILE_LAYER			m_ePaintLayer;
	bool				m_bPaintIsBlock;
};


#endif // !__TILEMGR_H__
