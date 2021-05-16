#pragma once
#include "Titan.h"
class CGolLath :
    public CTitan
{
public:
    CGolLath();
    virtual ~CGolLath();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render( HDC _DC ) override;
    virtual void Release() override;
private:
    virtual void Update_ColisionRect() override;

};

