#pragma once

#ifndef __CSlUDGEHEART_SHADOW_H__
#define __CSlUDGEHEART_SHADOW_H__

#include "Titan.h"
class CSlime;
class CSludgeHeart;
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
    void        Update_ColisionRect() override;
    virtual void OnOverlaped( CObj* _pBlockedObj, DIRECTION _eDir = DIRECTION_END ) override;

    void        Set_SludgeHeart( CSludgeHeart* _pHeart ) { m_pSludgeHeart = _pHeart; }
    void       Set_Slime( CSlime* _pSlime ) { m_pSlime = _pSlime; }
    void        Set_MozziX( float _x ) { m_fMozziX = _x;  }
    void        Set_iSizeLv( int _iSizeLv ) { m_iSizeLv = _iSizeLv; }
    void        Reset_Size();
private:
    void        Update_Mozzi();
    virtual void Update_Dead() override;
    virtual void Update_Pattern() override;
private:
    static const int m_iSizeStartX[5];
    static const int m_iSizeStartY[5];
    static const int m_iSizeX[5];
    static const int m_iSizeY[5];
    int             m_iSizeLv;
    CSlime*         m_pSlime;
    CSludgeHeart*   m_pSludgeHeart;
    float           m_fMozziX;
    int             m_iMaxCX;
};

#endif // !__CSlUDGEHEART_SHADOW_H__