#pragma once

#ifndef __TITAN_H__
#define __TITAN_H__

#include "Pawn.h"
class CPlayer;
class CTitanKillBox;
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
    inline void Set_PosZ( float _z ) { m_fPosZ = _z; }
    inline const float& Get_PosZ() const { return m_fPosZ; }
    inline void Add_PosZ( float _z ) { m_fPosZ += _z; }
    inline virtual void Set_Active() { m_bActive = true; }
    inline const bool& Get_Active() const { return m_bActive; }

    virtual void OnBlocked( CObj* _pBlockedObj, DIRECTION _eDir = DIRECTION_END ) override;
    virtual void OnOverlaped( CObj* _pBlockedObj, DIRECTION _eDir = DIRECTION_END ) override;

protected:
    virtual void Update_Dead() = 0;
    virtual void Update_DamageCollision();
    virtual void    Update_Pattern() = 0;
    virtual void		Update_Shadow();

protected:
    bool        m_bActive;
    float       m_fPosZ;
    CPlayer*    m_pPlayer;
    int         m_iPatternFrame;
    CTitanKillBox* m_pKillBox;
};

#endif // !__TITAN_H__