#pragma once

#ifndef __SCENE_H__
#define __SCENE_H__

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(HDC _DC) = 0;
	virtual void Release() = 0;
	const int&		Get_TileX() const { return m_iTileX; }
	const int&		Get_TileY() const { return m_iTileY; }
protected:
	int					m_iTileX;
	int					m_iTileY;
	const TCHAR*		m_pFileName;
};

#endif // !__SCENE_H__
