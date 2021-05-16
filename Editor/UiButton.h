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
private:

};

#endif // !__UIBUTTON_H__