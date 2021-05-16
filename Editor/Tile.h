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
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
	inline void		Set_DrawYID( int _iYId ) { m_iDrawYID = m_iDrawYID; }
	inline const int& Get_DrawYID() const { return m_iDrawYID; }
private:
	virtual void Update_ColisionRect();
	int				m_iDrawYID;
};


#endif // !__TILE_H__

