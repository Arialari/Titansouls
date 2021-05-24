#pragma once
#include "Scene.h"
class CMenu :
    public CScene
{
public:
    CMenu();
    virtual ~CMenu();
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render( HDC _DC ) override;
	virtual void Release() override;
private:
	int		m_iSelect;
};

