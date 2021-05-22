#pragma once
#include "Obj.h"
class CSceneChanger :
    public CObj
{
public:
    CSceneChanger();
    virtual ~CSceneChanger();

    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render( HDC _DC ) override;
    virtual void Release() override;
    virtual void Update_ColisionRect() override;
    inline void  Set_Scene ( SCENEID::ID _id ) { m_eChangeScene = _id; }

    virtual void OnBlocked( CObj* _pBlockedObj, DIRECTION _eDir ) override;

private:
    SCENEID::ID m_eChangeScene;

};
