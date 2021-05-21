#include "stdafx.h"
#include "MyMath.h"

float MyMath::FInterpTo( float _fCurrent, float _fTarget, float _fDeltaTime, float _fInterpSpeed )
{
	if ( _fInterpSpeed <= 0.f )
	{
		return _fTarget;
	}

	const float fDist = _fTarget - _fCurrent;

	if ( sqrt( fDist ) < 0.0001f )
	{
		return _fTarget;
	}

	const float fDeltaMove = fDist * Clamp<float>( _fDeltaTime * _fInterpSpeed, 0.f, 1.f );;

	return _fCurrent + fDeltaMove;
}

float MyMathMgr::fDirectionToRadianAngle[DIRECTION::DIRECTION_END] = { 0.f, PI / 2, PI, PI * 3 / 2, PI * 7 / 4, PI * 5 / 4, PI * 3 / 4, PI / 4 };
MyMathMgr::MyMathMgr()
{
}

MyMathMgr::~MyMathMgr()
{
}

