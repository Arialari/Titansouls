#pragma once

#ifndef __TITANKILLBOX_H__
#define __TITANKILLBOX_H__

#include "Obj.h"
class CTitan;
class CArrow;
class CTitanKillBox :
    public CObj
{
public:

    CTitanKillBox();
    virtual ~CTitanKillBox();

    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render( HDC _DC ) override;
    virtual void Release() override;
    virtual void Update_ColisionRect() override;
    
    virtual void OnOverlaped( CObj* _pBlockedObj, DIRECTION _eDir = DIRECTION_END ) override;

    inline void    Set_iC( int _cx, int _cy ) { m_tInfo.iCX = _cx; m_tInfo.iCY = _cy; }
    inline void     Set_Titan( CTitan* _pTitan ) { m_pTitan = _pTitan; }
    inline void  Set_Active() { m_bIsKillBoxAcive = true; }
public:

private:
    void Update_RenderPoint();
protected:
    CTitan* m_pTitan;
    bool    m_bIsKillBoxAcive;
    float   m_fArrowAngle;
    POINT   m_tRenderPoint[3];
    HDC     m_hMemDc;
    bool    m_bOverlapeOnce;
    CArrow* m_pArrow;
};

#endif // !__TITANKILLBOX_H__