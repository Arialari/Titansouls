#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "Pawn.h"
#include "IAnimation.h"
class CPlayer : public CPawn
{
public:
	enum STATE { IDLE, WALK, ROLL, RUN, AIM, DEAD, STATE_END };
	enum DIRECTION { E, N, W, S, SE, SW, NW, NE, DIRECTION_END};

public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
	virtual	void Hit() override;

private:
	void Key_Check();
	void State_Change();
	void OffSet();
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
};

#endif // !__PLAYER_H__

