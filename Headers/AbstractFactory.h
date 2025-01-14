#pragma once

#ifndef __ABSTRACTFACTORY_H__
#define __ABSTRACTFACTORY_H__

class CObj;
template <typename T>
class CAbstractFactory
{
public:
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Update_Rect();
		pObj->Update_ColisionRect();

		return pObj;
	}

	static CObj* Create(float _x, float _y)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_x, _y);
		pObj->Update_Rect();
		pObj->Update_ColisionRect();

		return pObj;
	}

	static CObj* Create(float _x, float _y, float _fAngle)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_x, _y);
		pObj->Set_Angle(_fAngle);
		pObj->Update_Rect();
		pObj->Update_ColisionRect();

		return pObj;
	}

	static CObj* Create( float _x, float _y, bool _bIsRender )
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos( _x, _y );
		pObj->Set_IsRender( _bIsRender );
		pObj->Update_Rect();
		pObj->Update_ColisionRect();

		return pObj;
	}

};

#endif // !__ABSTRACTFACTORY_H__
