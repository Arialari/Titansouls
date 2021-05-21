#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "CollisionMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;
CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Update()
{
	for ( int i = 0; i < OBJID::END; ++i )
	{
		if ( i == OBJID::BACKGROUND )
			continue;
		auto iter = m_listObj[i].begin();
		for ( ; iter != m_listObj[i].end(); )
		{
			int iEvent = (*iter)->Update();

			if ( OBJ_DEAD == iEvent )
			{
				SAFE_DELETE( *iter );
				iter = m_listObj[i].erase( iter );
			}
			else
				++iter;
		}
	}

	CCollisionMgr::Collision_BackGroundEx( m_listObj[OBJID::PLAYER] );
	CCollisionMgr::Collision_BackGroundEx( m_listObj[OBJID::ARROW] );
	CCollisionMgr::Collision_Rect( m_listObj[OBJID::PLAYER], m_listObj[OBJID::ARROW] );
	CCollisionMgr::Collision_RectEx( m_listObj[OBJID::TITAN], m_listObj[OBJID::PLAYER] );
	//CCollisionMgr::Collision_Sphere(m_listObj[OBJID::MOUSE], m_listObj[OBJID::MONSTER]);
}

void CObjMgr::Late_Update()
{
	for ( int i = 0; i < OBJID::END; ++i )
	{
		if ( i == OBJID::BACKGROUND )
		{
			Late_Update_BackGround();
			continue;
		}
		for ( auto& pObj : m_listObj[i] )
		{
			pObj->Late_Update();

			if ( m_listObj[i].empty() )
				break;

			RENDERID::ID eID = pObj->Get_RenderID();


			m_listRender[eID].emplace_back( pObj );
		}
	}
}

void CObjMgr::Render( HDC _DC )
{
	for ( int i = 0; i < RENDERID::END; ++i )
	{
		if ( RENDERID::OBJECT == i )
			m_listRender[i].sort( CompareY<CObj*> );

		for ( auto& pObj : m_listRender[i] )
			pObj->Render( _DC );

		m_listRender[i].clear();
	}
}

void CObjMgr::Release()
{
	for ( int i = 0; i < OBJID::END; ++i )
	{
		for_each( m_listObj[i].begin(), m_listObj[i].end(), Safe_Delete<CObj*> );
		m_listObj[i].clear();
	}
}

CObj* CObjMgr::Get_Target( CObj* _pObj, OBJID::ID _eID ) const
{
	CObj* pTarget = nullptr;
	float	fDis = 0.f;

	float	fX = 0.f;
	float	fY = 0.f;
	float	fDia = 0.f;

	for ( auto& pDst : m_listObj[_eID] )
	{
		fX = _pObj->Get_Info().fX - pDst->Get_Info().fX;
		fY = _pObj->Get_Info().fY - pDst->Get_Info().fY;
		fDia = sqrtf( fX * fX + fY * fY );

		if ( fDis > fDia || !pTarget )
		{
			pTarget = pDst;
			fDis = fDia;
		}
	}

	return pTarget;
}

void CObjMgr::Delete_ObjID( OBJID::ID _eID )
{
	for_each( m_listObj[_eID].begin(), m_listObj[_eID].end(), Safe_Delete<CObj*> );
	m_listObj[_eID].clear();
}

void CObjMgr::Late_Update_BackGround()
{
	if ( m_listObj[OBJID::BACKGROUND].empty() )
		return;

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	int	iCullX = abs( iScrollX / DEFAULTCX );
	int	iCullY = abs( iScrollY / DEFAULTCY );

	int iCullEndX = iCullX + (WINCX / DEFAULTCX) + 2;
	int iCullEndY = iCullY + (WINCY / DEFAULTCY) + 2;

	const vector<CObj*> vecTile = CTileMgr::Get_Instance()->Get_vecTile();
	int iTileX = CTileMgr::Get_Instance()->Get_TileLengthX();

	for ( int i = iCullY; i < iCullEndY; ++i )
	{
		for ( int j = iCullX; j < iCullEndX; ++j )
		{
			int iIdx = i * iTileX + j;

			if ( 0 > iIdx || vecTile.size() <= (size_t)iIdx )
				continue;
			//타일은 Late_Update 할게 없음;
			//vecTile[iIdx]->Late_Update();

			RENDERID::ID eID = vecTile[iIdx]->Get_RenderID();

			m_listRender[eID].emplace_back( vecTile[iIdx] );

		}
	}

}
