#pragma once

#ifndef __BIGDOOR_H_
#define __BIGDOOR_H_

#include "Obj.h"
class CPlayer;
class CBigDoor :
    public CObj
{
public:
    CBigDoor();
    virtual ~CBigDoor();
public:

    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render( HDC _DC ) override;
    virtual void Release() override;
    virtual void Update_ColisionRect() override;

    inline void Set_Player( CPlayer* _p ) { m_pPlayer = _p; }
private:
    CPlayer*         m_pPlayer;
    int                 m_iPatternFrame;
};

#endif // !__BIGDOOR_H_