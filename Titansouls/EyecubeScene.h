#pragma once
#include "Scene.h"
class CEyecubeScene :
    public CScene
{
public:
	CEyecubeScene();
	virtual ~CEyecubeScene();
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render( HDC _DC ) override;
	virtual void Release() override;
private:
};

