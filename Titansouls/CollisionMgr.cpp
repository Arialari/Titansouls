#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "TileMgr.h"
#include "Tile.h"


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
				pDst->OnBlocked();
				pSrc->OnBlocked();
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
					{
						pSrc->Add_PosX( fX );
						pSrc->OnBlocked(DIRECTION::W);
						continue;
					}
					else
					{
						pSrc->Add_PosX( -fX );
						pSrc->OnBlocked( DIRECTION::E );
						continue;
					}
				}
				else
				{
					if ( pDst->Get_Info().fY < pSrc->Get_Info().fY )
					{
						pSrc->Add_PosY( fY );
						pSrc->OnBlocked( DIRECTION::N );
						continue;
					}
					else
					{
						pSrc->Add_PosY( -fY );
						pSrc->OnBlocked( DIRECTION::S );
						continue;
					}
				}
				
			}
		}
	}
}

void CCollisionMgr::Collision_BackGroundEx( list<CObj*>& _Src )
{
	for ( auto& pObj : _Src )
	{
		
		int iTileX = CTileMgr::Get_Instance()->Get_TileLengthX();
		int iPosX = (int)pObj->Get_Info().fX;
		int iPosY = (int)pObj->Get_Info().fY;

		int	iCollisionCheckX = abs( iPosX / DEFAULTCX ) - 1;
		int	iCollisionCheckY = abs( iPosY / DEFAULTCY ) - 1;
		for ( int i = iCollisionCheckY; i < iCollisionCheckY + 3; ++i )
		{
			for ( int j = iCollisionCheckX; j < iCollisionCheckX + 3; ++j )
			{
				int iIdx = i * iTileX + j;
				CTile* pTile = static_cast<CTile*>(CTileMgr::Get_Instance()->Get_vecTile()[iIdx]);
				if ( pTile->Get_IsBlock() )
				{
					float fX, fY;
					if ( IsObj_OverlappedEx( pObj->Get_CollisionRect(), pTile->Get_CollisionRect(), &fX, &fY ) )
					{
						if ( fX < fY )
						{
							if ( pTile->Get_Info().fX < pObj->Get_Info().fX )
							{
								pObj->Add_PosX( fX );
								pObj->OnBlocked( DIRECTION::W );
							}
							else
							{
								pObj->Add_PosX( -fX );
								pObj->OnBlocked( DIRECTION::E );
							}
						}
						else
						{
							if ( pTile->Get_Info().fY < pObj->Get_Info().fY )
							{
								pObj->Add_PosY( fY );
								pObj->OnBlocked( DIRECTION::N );
							}
							else
							{
								pObj->Add_PosY( -fY );
								pObj->OnBlocked( DIRECTION::S );
							}
						}
					}
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
				pDst->OnBlocked();
				pSrc->OnBlocked();
			}
		}
	}
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
