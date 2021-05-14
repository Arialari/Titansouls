#pragma once
#ifndef __IANIMATION_H__
#define __IANIMATION_H__

#include "Implement.h"
class IAnimation :
    public CImplement
{
public:
    IAnimation();
    virtual ~IAnimation();
protected:
    virtual void    Update_Animation_Frame();
protected:
    unsigned int m_iFrameidx;
    FRAME        m_tFrame;
};

#endif // !__IANIMATION_H__