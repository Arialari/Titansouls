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
public:
	virtual void	Set_Pos( float _x, float _y );
	virtual void	Set_PosX( float _x );
	virtual void	Set_PosY( float _y );
	virtual void	Add_Pos( float _x, float _y );
	virtual void	Add_PosX( float _x );
	virtual void	Add_PosY( float _y );
	inline void		ReserveAttachSize( int _c ) { m_vecHavingUI.reserve( _c ); }
	void			AttachUi( CUi* pCUi);
private:
	vector<CUi*>	m_vecHavingUI;
};

