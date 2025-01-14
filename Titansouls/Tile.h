#pragma once

#ifndef __TILE_H__
#define __TILE_H__

#include "Obj.h"
class CTile : public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	virtual void		Initialize() override;
	virtual int			Update() override;
	virtual void		Late_Update() override;
	virtual void		Render(HDC _DC) override;
	virtual void		Release() override;
	void				Setting_Done();
	inline void			Set_DrawYID( int _iYId ) { m_iDrawYID = _iYId; }
	inline void			Set_DrawID( int _iXId, int _iYId ) { m_iDrawXID = _iXId; m_iDrawYID = _iYId; }
	inline const int&	Get_DrawYID() const { return m_iDrawYID; }
	inline void			Set_iFrameEndX( int _x ) { m_iFrameEndX = _x; }
	inline const int&	Get_iFrameEndX() const { return m_iFrameEndX; }
	inline void			Set_IsBlock( bool _IsBlock ) { m_bIsCheckBlock = _IsBlock; }
	inline const bool&	Get_IsBlock() const { return m_bIsCheckBlock; }
	static void			Set_iFrameIdx( int _iFrameIdx ) { m_iFrameIdx = _iFrameIdx; }
	inline void			Set_eRenderId( RENDERID::ID _eId ) { m_eRenderID = _eId; }
	
protected:

	virtual void		Update_ColisionRect();
private:
	int					m_iDrawYID;
	static int			m_iFrameIdx;
	int					m_iFrameEndX;
	bool				m_bIsAlphaRender;
};


#endif // !__TILE_H__

