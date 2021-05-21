#pragma once
#include "Obj.h"
class CArrow :
    public CObj
{
public:
    CArrow();
    virtual ~CArrow();
public:

    virtual void    Initialize() override;
    virtual int     Update() override;
    virtual void    Late_Update() override;
    virtual void    Render( HDC _DC ) override;
    virtual void    Release() override;
    virtual void    Update_ColisionRect() override;

    virtual void    OnBlocked(DIRECTION _eDir) override;

    void            Shoot( float _fAimGaze );
    void            Set_RadianAngle( float _fAngle ) { m_fRadianAngle = _fAngle; }
private:
    HDC             m_hMemDc;
    float           m_fRadianAngle;
    float           m_fFullSpeed;
    float           m_fSpeed;
};

