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
    virtual void    OnOverlaped( CObj* _pBlockedObj, DIRECTION _eDir = DIRECTION_END ) override;

    void            Update_RenderPoint();
    void            Shoot( float _fAimGaze );
    void            Set_RadianAngle( float _fAngle ) { m_fRadianAngle = _fAngle; }
    void            Add_Speed();
    void            Set_IsReturning( bool _bIsReturning ) { m_bIsReturning = _bIsReturning; }
    const bool&     Get_IsDamage() const { return m_bIsDamage; }
private:
    HDC             m_hMemDc;
    float           m_fRadianAngle;
    const float     m_fFullSpeed;
    const float     m_fReturnAccelator;
    float           m_fSpeed;
    bool            m_bHolded;
    bool            m_bIsReturning;
    POINT           m_tRenderPoint[3];
    bool            m_bIsDamage;
};

