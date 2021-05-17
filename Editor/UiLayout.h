#pragma once
#include "Ui.h"
class CUiLayout :
    public CUi
{
public:
    CUiLayout();
    virtual ~CUiLayout();
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render( HDC _DC ) override;
	virtual void Release() override;
	virtual void Update_ColisionRect() override;
	// CUi을(를) 통해 상속됨
	virtual void OnEvent( EVENT_CODE _eEventCode ) override;
public:

private:
	

};

