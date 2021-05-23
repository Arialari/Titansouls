#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "Pawn.h"
#include "IAnimation.h"
class CArrow;
class CPlayer : public CPawn
{
public:
	enum STATE { IDLE, WALK, ROLL, RUN, AIM, RETURN, DEAD, STATE_END };
	

public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
	virtual void Set_Pos( float _x, float _y ) override;
	virtual void OnBlocked( CObj* _pBlockedObj, DIRECTION _eDir ) override;
	virtual void OnOverlaped( CObj* _pBlockedObj, DIRECTION _eDir = DIRECTION_END ) override;

public:
	inline  void Pick_Arrow() { m_bHoldArrow = true; }
	const bool& Get_IsHolingArrow() const { return m_bHoldArrow; }
	

private:
	void Key_Check();
	void State_Change();
	void OffSet();
	void Update_Dead();
	void Update_Aim();
	void Update_Return();
	virtual void Update_Animation_Frame() override;
	virtual void Update_ColisionRect() override;

private:
	STATE		m_ePreState;
	STATE		m_eCurState;
	DIRECTION	m_ePreDirection;
	DIRECTION	m_eCurDirection;
	const float		m_fRunSpeed;
	const float		m_fWalkSpeed;
	const float		m_fRollSpeed;
	CArrow*		m_pArrow;
	bool		m_bHoldArrow;
	bool		m_bIsAiming;
	bool		m_bIsReturning;
	bool		m_bWasRetrun;
	float		m_fAimGaze;
	const int	m_iDeadTime;
	int			m_iDeadFrame;
};

#endif // !__PLAYER_H__

