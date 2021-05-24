#pragma once
#include "Titan.h"
class CSlime;
class CSlimeShadow;
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
private:
    virtual void Update_Dead() override;
    virtual void Update_Pattern() override;
private:
    CSlime*     m_pSlime[16];
    CSlimeShadow* m_pShadow;
};

