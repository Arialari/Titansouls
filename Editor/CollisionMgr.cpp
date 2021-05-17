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

	for ( auto& pDst : _Dst )
	{
		for ( auto& pSrc : _Src )
		{
			
			if ( IsObj_Overlapped( pDst->Get_CollisionRect(), pSrc->Get_CollisionRect()) )
			{
				pDst->Hit();
				pSrc->Hit();
			}
		}
	}
}

void CCollisionMgr::Collision_RectEx( list<CObj*>& _Dst, list<CObj*>& _Src )
{
	float fX = 0.f, fY = 0.f;
	for ( auto& pDst : _Dst )
	{
		for ( auto& pSrc : _Src )
		{
			if ( IsObj_OverlappedEx(pDst->Get_CollisionRect(), pSrc->Get_CollisionRect(),&fX,&fY) )
			{
				if ( fX < fY )
				{
					if ( pDst->Get_Info().fX < pSrc->Get_Info().fX )
						pSrc->Add_PosX( fX );
					else
						pSrc->Add_PosX( -fX );
				}
				else
				{
					if ( pDst->Get_Info().fY < pSrc->Get_Info().fY )
						pSrc->Add_PosY( fY );
					else
						pSrc->Add_PosY( -fY );
				}
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

CObj* CCollisionMgr::Collision_Mouse( const list<CObj*>& _Dst, POINT& _point )
{
	RECT rc = {};
	RECT rcPoint = { _point.x,_point.y,_point.x,_point.y };
	for ( auto& pDst : _Dst )
	{
		if ( IntersectRect( &rc, &pDst->Get_Rect(), &rcPoint ) )
		{
			pDst->Hit();
			return pDst;
		}
	}
	return nullptr;
}

bool CCollisionMgr::IsObj_Overlapped(const vector<RECT>& _Dst, const vector<RECT>& _Src )
{
	RECT rc = {};
	for ( auto& rectDest : _Dst )
	{
		for ( auto& rectSrc : _Src )
		{
			if ( IntersectRect( &rc, &rectDest, &rectSrc ) )
			{
				return true;
			}
		}
	}
	return false;
}

bool CCollisionMgr::IsObj_OverlappedEx( const vector<RECT>& _Dst, const vector<RECT>& _Src, float* _fX, float* _fY )
{
	RECT rc = {};
	for ( auto& rectDest : _Dst )
	{
		for ( auto& rectSrc : _Src )
		{
			if ( Check_Rect( rectDest, rectSrc, _fX, _fY) )
			{
				return true;
			}
		}
	}
	return false;
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

bool CCollisionMgr::Check_Rect(const RECT& _Dst,const RECT& _Src, float* _x, float* _y )
{
	RECT rc = {};
	if ( IntersectRect(&rc, &_Dst,&_Src ) )
	{
		*_x = rc.right - rc.left;
		*_y = rc.bottom - rc.top;
		return true;
	}
	return false;
}
