#pragma once

#ifndef __PAWN_H__
#define __PAWN_H__

#include "Obj.h"
#include "IAnimation.h"
class CPawn :
    public CObj, public IAnimation
{
public:
    CPawn();
    virtual ~CPawn();
protected:
    float			m_fSpeed;
    float           m_fVelocityX;
    float           m_fVelocityY;
};

#endif // !__PAWN_H__