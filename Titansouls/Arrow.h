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

    virtual void    OnBlocked(CObj* _pBlockedObj ,DIRECTION _eDir) override;

    void            Shoot( float _fAimGaze );
    void            Set_RadianAngle( float _fAngle ) { m_fRadianAngle = _fAngle; }
    void            Add_Speed();
private:
    HDC             m_hMemDc;
    float           m_fRadianAngle;
    const float     m_fFullSpeed;
    const float     m_fReturnAccelator;
    float           m_fSpeed;
};

