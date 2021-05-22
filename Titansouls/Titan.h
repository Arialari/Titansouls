#pragma once

#ifndef __TITAN_H__
#define __TITAN_H__

#include "Pawn.h"
class CTitan :
    public CPawn
{
public:
    CTitan();
    virtual ~CTitan();

    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render( HDC _DC ) override;
    virtual void Release() override;
    virtual void Update_ColisionRect() override;

private:


};

#endif // !__TITAN_H__