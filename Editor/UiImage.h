#pragma once

#ifndef __UIIMAGE_H__
#define __UIIMAGE_H__

#include "Ui.h"
class CUiImage :
    public CUi
{
public:
    CUiImage();
    virtual ~CUiImage();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render( HDC _DC ) override;
    virtual void Release() override;
    virtual void Update_ColisionRect() override;
    virtual void Set_ImageSize( int _cx, int _cy ) { m_tInfo.iCX = _cx; m_tInfo.iCY = _cy; }
    virtual void OnEvent( EVENT_CODE _eEventCode ) override;
    virtual void Hit() override;
private:
    INFO          m_tModelInfo;
    int           m_iModelEndX;
    int           m_iModelIntervalX;
};

#endif // !__UIIMAGE_H__