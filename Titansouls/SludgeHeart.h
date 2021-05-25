#pragma once
#include "Titan.h"
class CSlime;
class CSludgeHeartShadow;
class CSludgeHeart :
    public CTitan
{
public:
    CSludgeHeart();
    virtual ~CSludgeHeart();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render( HDC _DC ) override;
    virtual void Release() override;
    virtual void Set_Active() override;
    inline void  Set_Alone() { m_bAlone = true; }
public:
    void         Create_Slime( float _x, float _y, int _iSizeLv );
private:
    virtual void Update_Dead() override;
    virtual void Update_Pattern() override;
private:
    vector<CSlime*>     m_pSlime;
    CSludgeHeartShadow*       m_pShadow;

    bool            m_bAlone;
};

