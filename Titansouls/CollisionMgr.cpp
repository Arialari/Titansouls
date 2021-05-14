#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect( list<CObj*>& _Dst, list<CObj*>& _Src )
{
	RECT rc = {};
	for ( auto& pDst : _Dst )
	{
		for ( auto& pSrc : _Src )
		{
			if ( IntersectRect( &rc, &pDst->Get_Rect(), &pSrc->Get_Rect() ) )
			{
				pDst->Hit();
				pSrc->Hit();
			}
		}
	}
}

void CCollisionMgr::Collision_Sphere( list<CObj*>& _Dst, list<CObj*>& _Src )
{
	for ( auto& pDst : _Dst )
	{
		for ( auto& pSrc : _Src )
		{
			if ( Check_Sphere( pDst, pSrc ) )
			{
				pDst->Hit();
				pSrc->Hit();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere( CObj* _Dst, CObj* _Src )
{
	float fX = abs( _Dst->Get_Info().fX - _Src->Get_Info().fX );
	float fY = abs( _Dst->Get_Info().fY - _Src->Get_Info().fY );
	float fDia = sqrtf( fX * fX + fY * fY );

	float fDis = (float)((_Dst->Get_Info().iCX + _Src->Get_Info().iCX) >> 1);

	if ( fDia <= fDis )
		return true;

	return false;
}
