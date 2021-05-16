#pragma once

#ifndef __UI__
#define __UI__
#include "Obj.h"
class CUi : public CObj
{
public:
	CUi();
	virtual ~CUi();
public:
	//Default is False
	bool	m_bIsVisible;
	bool	m_bIsHoverd;
};

#endif // !__UI__


