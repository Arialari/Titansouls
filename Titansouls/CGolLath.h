#pragma once

#ifndef __GOLLATH_H__
#define __GOLLATH_H__

#include "Titan.h"
class CGolLathArm;
class CGolLath :
    public CTitan
{
private:
    enum Arm { LEFT, RIGHT };
public:
    CGolLath();
    virtual ~CGolLath();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render( HDC _DC ) override;
    virtual void Release() override;
private:
    virtual void Update_Pattern() override;
    void        AttackPattern( Arm _arm);
    void        ShieldPattern( Arm _arm);
private:
    virtual void Update_ColisionRect() override;
    const float     m_fMaxShoulderY;
    float           m_fShoulderY;
    const float     m_fMaxBodyY;
    float           m_fBodyY;
    float           m_fHeadY;
    float           m_fRenderModelY;
    CGolLathArm*    m_pArm[2];
    bool            m_bPatterning;
    int             m_iAttackStartFrame;
    int             m_iShieldStartFrame;
};

#endif // !__GOLLATH_H__