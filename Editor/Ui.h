#pragma once

#ifndef __UI__
#define __UI__
#include "Obj.h"
class CUi : public CObj
{
public:
	enum EVENT_CODE { MOVE_LEFT, MOVE_UP, MOVE_RIGHT, MOVE_DOWN, NO_EVENT };


	CUi();
	virtual ~CUi();
public:
	virtual void	Set_Pos( float _x, float _y );
	virtual void	Set_PosX( float _x );
	virtual void	Set_PosY( float _y );
	virtual void	Add_Pos( float _x, float _y );
	virtual void	Add_PosX( float _x );
	virtual void	Add_PosY( float _y );
	void			Set_RelatedX( float _x ) { m_fRelatedX = _x; }
	void			Set_RelatedY( float _y ) { m_fRelatedY = _y; }
	void			Set_IsHovered( bool _bIsHoverd ) { m_bIsHoverd = _bIsHoverd; }
	bool			Get_IsHovered() const { return m_bIsHoverd; }
	void			Set_IsVisible( bool _bIsVisible );
	inline void		Toggle_IsVisible() { Set_IsVisible( !m_bIsVisible ); };
	bool			Get_IsVisible() const { return m_bIsVisible; }
	inline void		ReserveAttachSize( int _c ) { m_vecAttachedUI.reserve( _c ); }
	void			AttachUi( CUi* _pAttachedUi, float _fRelatedX, float _fRelatedY );
	void			SetAttachingUi( CUi* _pUi ) { m_pAttachingUI = _pUi; }
	virtual void	OnEvent( EVENT_CODE _eEventCode ) = 0;
protected:
	void			Update_Hover();
	//Default is False
	bool	m_bIsVisible;
	bool	m_bIsHoverd;
	float	m_fRelatedX;
	float	m_fRelatedY;
	vector<CUi*>	m_vecAttachedUI;
	CUi*			m_pAttachingUI;
	UI_TYPE::ID			m_eUiType;
};

#endif // !__UI__


