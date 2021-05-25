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
    inline void Set_SludgeHeart( CSludgeHeart* _pSludge ) { m_pSludeHeart = _pSludge; }
    inline void Set_HaveHeart() {m_bHaveHeart = true; }
    void Set_ThisIter( list<CSlime*>::iterator _iter );
    void Set_iSizeLv( int _iSizeLv );
    virtual void Set_Active() override;
    void        Reset_Size();
    inline const bool& Get_bHaveHeart() const { return m_bHaveHeart; }
    virtual void			Set_Dead( bool _bDead );
private:
    virtual void Update_DamageCollision() override;
    virtual void Update_Dead() override;
    virtual void Update_Pattern() override;
    virtual void Update_Shadow() override;
    void    Update_Heart();
    
    void        Update_Mozzi();
private:
    CSlimeShadow*         m_pShadow;
    CSludgeHeart*       m_pSludeHeart;
    static const int    m_iSizeStartX[5];
    static const int    m_iSize[5];
    static const float    m_fMozziMinX;
    static const float    m_fMozziMinY;
    int             m_iSizeLv;
    bool            m_bHaveHeart;
    float           m_fMozziX;
    float           m_fMozziY;
    bool            m_bIsHomingPlayer;
    int                         m_iMaxCX;
    int                         m_iMaxCY;
    float                       m_fTargetX;
    float                       m_fTargetY;
    list<CSlime*>::iterator     m_iterThis;
    int                         m_iShakeStartFrame;
};

#endif // !__SLIME_H__

