#pragma once

#ifndef __COLLISIONMGR_H__
#define __COLLISIONMGR_H__

class CObj;
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void Collision_Rect( list<CObj*>& _Dst, list<CObj*>& _Src );
	static void Collision_RectEx( list<CObj*>& _Dst, list<CObj*>& _Src );
	static void Collision_Sphere( list<CObj*>& _Dst, list<CObj*>& _Src );

	static bool IsObj_Overlapped(const vector<RECT>& _Dst, const vector<RECT>& _Src );

	static bool IsObj_OverlappedEx( const vector<RECT>& _Dst, const vector<RECT>& _Src, float* _fX, float* _fY );

	static bool Check_Sphere( CObj* _Dst, CObj* _Src );
	static bool Check_Rect(const RECT& _Dst, const RECT& _Src, float* _x, float* _y );
};

#endif // !__COLLISIONMGR_H__