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
				if( pDst->Get_IsCheckOverlape() )
					pDst->OnOverlaped(pSrc);
				if ( pSrc->Get_IsCheckOverlape() )
					pSrc->OnOverlaped(pDst);
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
						if(pSrc->Get_IsCheckBlock() )
							pSrc->OnBlocked(pDst, DIRECTION::W);
						if(pDst->Get_IsCheckBlock() )
							pDst->OnBlocked( pSrc, DIRECTION::E );
						continue;
					}
					else
					{
						pSrc->Add_PosX( -fX );
						if ( pSrc->Get_IsCheckBlock() )
							pSrc->OnBlocked( pDst, DIRECTION::E );
						if ( pDst->Get_IsCheckBlock() )
							pDst->OnBlocked( pSrc, DIRECTION::W );
						continue;
					}
				}
				else
				{
					if ( pDst->Get_Info().fY < pSrc->Get_Info().fY )
					{
						pSrc->Add_PosY( fY );
						if ( pSrc->Get_IsCheckBlock() )
							pSrc->OnBlocked( pDst, DIRECTION::N );
						if ( pDst->Get_IsCheckBlock() )
							pDst->OnBlocked( pSrc, DIRECTION::S );
						continue;
					}
					else
					{
						pSrc->Add_PosY( -fY );
						if ( pSrc->Get_IsCheckBlock() )
							pSrc->OnBlocked( pDst, DIRECTION::S );
						if ( pDst->Get_IsCheckBlock() )
							pDst->OnBlocked( pSrc, DIRECTION::N );
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
		int iTileY = CTileMgr::Get_Instance()->Get_TileLengthY();
		int iPosX = (int)pObj->Get_Info().fX;
		int iPosY = (int)pObj->Get_Info().fY;



		//int iX = pObj->Get_Info().fX / DEFAULTCX;
		//int iY = pObj->Get_Info().fY / DEFAULTCY;

		//int iIdxUp = iIdx1 - 100;
		//int iIdxDown = iIdx1 + 100;

		int	iCollisionCheckX = abs( iPosX / DEFAULTCX );
		int	iCollisionCheckY = abs( iPosY / DEFAULTCY );
		int iIdxCenter = iCollisionCheckY * iTileX + iCollisionCheckX;

		int iIdx[DIRECTION_END] = { 
			iIdxCenter + 1, iIdxCenter - iTileX, iIdxCenter -1, iIdxCenter + iTileX
			, iIdxCenter + 101, iIdxCenter + 99, iIdxCenter - 101, iIdxCenter - 99};

		const vector<CObj*> vecTile = CTileMgr::Get_Instance()->Get_vecTile();
		// 대각선 충돌이 우선이기때문에 먼저 판단합니다 --로 말이죠
		for (int i = 0; i<DIRECTION_END; ++i)
		{
			if ( iIdx[i] < 0 || iIdx[i] >= iTileX * iTileY )
				continue;
			CTile* pTile = static_cast<CTile*>(vecTile[iIdx[i]]);
			if ( pTile->Get_IsBlock() )
			{
				float fX = 0, fY = 0;
				if ( IsObj_OverlappedEx( pTile->Get_CollisionRect(), pObj->Get_CollisionRect(), &fX, &fY ) )
				{
					if ( fX < fY )
					{
						if ( pTile->Get_Info().fX < pObj->Get_Info().fX )
						{
							pObj->Add_PosX( fX );
						}
						else
						{
							pObj->Add_PosX( -fX );
						}
					}
					else
					{
						if ( pTile->Get_Info().fY < pObj->Get_Info().fY )
						{
							pObj->Add_PosY( fY );
						}
						else
						{
							pObj->Add_PosY( -fY );
						}
					}
					if ( pObj->Get_IsCheckBlock() )
						pObj->OnBlocked( pTile, (DIRECTION)i );
					//break;
				}
			}
		}
		//int	iCollisionCheckX = abs( iPosX / DEFAULTCX ) - 1;
		//int	iCollisionCheckY = abs( iPosY / DEFAULTCY ) - 1;
		/*for ( int i = iCollisionCheckY; i < iCollisionCheckY + 3; ++i )
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
		}*/
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
				pDst->OnBlocked(pSrc);
				pSrc->OnBlocked(pDst);
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
