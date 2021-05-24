#pragma once

#ifndef __CSlUDGEHEART_SHADOW_H__
#define __CSlUDGEHEART_SHADOW_H__

#include "Titan.h"
class CSlime;
class CSlimeShadow :
    public CTitan
{
public:
    CSlimeShadow();
    virtual ~CSlimeShadow();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render( HDC _DC ) override;
    virtual void Release() override;
private:
    virtual void Update_Dead() override;
    virtual void Update_Pattern() override;
private:
    static const int m_iSizeStartX[5];
    static const int m_iSizeStartY[5];
    static const int m_iSizeX[5];
    static const int m_iSizeY[5];
    int             m_iSizeLv;
    CSlime*         m_pSlime;
};

#endif // !__CSlUDGEHEART_SHADOW_H__