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
    virtual void Update_ColisionRect() override;
    void  Set_Alone();
    inline void  EraseSlime( list<CSlime*>::iterator _iter ) { m_pSlime.erase( _iter ); }
    virtual void Update_DamageCollision() override;
    virtual void OnOverlaped( CObj* _pBlockedObj, DIRECTION _eDir = DIRECTION_END ) override;
public:
    void         Create_Slime( float _x, float _y, int _iSizeLv, bool bHaveHeart );
private:
    virtual void Update_Dead() override;
    virtual void Update_Pattern() override;
private:
    list<CSlime*>     m_pSlime;
    CSludgeHeartShadow*       m_pShadow;

    bool            m_bAlone;
};

