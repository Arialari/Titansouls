#pragma once
#include "Titan.h"
class CSludgeHeart;
class CSludgeHeartShadow :
    public CTitan
{
public:
    CSludgeHeartShadow();
    virtual ~CSludgeHeartShadow();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render( HDC _DC ) override;
    virtual void Release() override;
    void        Update_ColisionRect() override;

private:
    virtual void Update_Dead() override;
    virtual void Update_Pattern() override;
private:
    CSludgeHeart* m_pSludgeHeart;
};

