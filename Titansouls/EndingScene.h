#pragma once
#include "Scene.h"
class CEndingScene :
    public CScene
{
public:
    CEndingScene();
    virtual ~CEndingScene();
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render( HDC _DC ) override;
	virtual void Release() override;
private:
	int			m_iPatternFrame;
};

