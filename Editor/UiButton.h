#pragma once
#ifndef __UIBUTTON_H__
#define __UIBUTTON_H__

#include "Ui.h"
class CUiButton :
    public CUi
{
public:
    CUiButton();
    virtual ~CUiButton();

    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render( HDC _DC ) override;
    virtual void Release() override;
    virtual void Update_ColisionRect() override;
    void Set_EventCode( EVENT_CODE _eCode ) { m_eEventCode = _eCode; }
    virtual void Hit() override;

    // CUi을(를) 통해 상속됨
    virtual void OnEvent( EVENT_CODE _eEventCode ) override;
private:
    EVENT_CODE m_eEventCode;
};

#endif // !__UIBUTTON_H__