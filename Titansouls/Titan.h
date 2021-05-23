#pragma once

#ifndef __TITAN_H__
#define __TITAN_H__

#include "Pawn.h"
class CPlayer;
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
    inline void  Set_Player( CPlayer* _pPlayer ) { m_pPlayer = _pPlayer; }

    virtual void OnBlocked( CObj* _pBlockedObj, DIRECTION _eDir = DIRECTION_END ) override;
    virtual void OnOverlaped( CObj* _pBlockedObj, DIRECTION _eDir = DIRECTION_END ) override;
protected:
    void        Update_DamageCollision();
    virtual void    Update_Pattern() = 0;

protected:
    bool        m_bActive;
    float       m_fPosZ;
    CPlayer*    m_pPlayer;
    int         m_iPatternFrame;
};

#endif // !__TITAN_H__