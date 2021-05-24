#pragma once

#ifndef __SLIME_H__
#define __SLIME_H__

#include "Titan.h"
class CSlimeShadow;
class CSludgeHeart;
class CSlime :
    public CTitan
{
public:
    CSlime();
    virtual ~CSlime();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render( HDC _DC ) override;
    virtual void Release() override;
public:
    void        Set_SludgeHeart( CSludgeHeart* _pSludge ) { m_pSludeHeart = _pSludge; }
private:
    virtual void Update_DamageCollision() override;
    virtual void Update_Dead() override;
    virtual void Update_Pattern() override;
private:
    CSlimeShadow*         m_pShadow;
    CSludgeHeart*       m_pSludeHeart;
    static const int    m_iSizeStartX[5];
    static const int    m_iSize[5];
    int             m_iSizeLv;
};

#endif // !__SLIME_H__