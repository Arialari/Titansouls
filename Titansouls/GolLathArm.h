#pragma once

#ifndef __GOLLATHARM_H__
#define __GOLLATHARM_H__

#include "Titan.h"
class CGolLath;
class CGolLathArm :
    public CTitan
{
private:
    
public:
    CGolLathArm();
    virtual ~CGolLathArm();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render( HDC _DC ) override;
    virtual void Release() override;
    virtual void Update_ColisionRect() override;

    //virtual void OnBlocked( CObj* _pBlockedObj, DIRECTION _eDir = DIRECTION_END ) override;
    virtual void OnOverlaped( CObj* _pBlockedObj, DIRECTION _eDir = DIRECTION_END ) override;
    inline void Set_IsFliped( bool _Flip ) { m_bIsFliped = _Flip; }
    inline void Set_pGolLath( CGolLath* _pGolLath ) { m_pGolLath = _pGolLath; }
    inline void Set_iFrameX( int _iFramex ) { m_tFrame.iFrameX = _iFramex; }
protected:
    virtual void Update_Pattern() override;
    // CTitan을(를) 통해 상속됨
    virtual void Update_Dead() override;
private:
    bool        m_bIsFliped;
    CGolLath*    m_pGolLath;

   
};

#endif // !__GOLLATHARM_H__