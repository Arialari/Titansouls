#pragma once
#include "Scene.h"
class CSludgeScene :
    public CScene
{
public:
	CSludgeScene();
	virtual ~CSludgeScene();
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render( HDC _DC ) override;
	virtual void Release() override;
private:

};

