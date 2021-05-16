#pragma once
#include "Scene.h"

#ifndef __HALLWAY_H__
#define __HALLWAY_H__

class CHallway :
    public CScene
{
public:
    CHallway();
    ~CHallway();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render( HDC _DC ) override;
	virtual void Release() override;
private:

};


#endif // !__HALLWAY_H__