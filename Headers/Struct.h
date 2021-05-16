#pragma once

#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct tagInfo
{
	float	fX;
	float	fY;
	int		iCX;
	int		iCY;
}INFO;

typedef struct tagLinePos
{
	tagLinePos() { ZeroMemory(this, sizeof(tagLinePos)); }
	tagLinePos(float _x, float _y) : fX(_x), fY(_y) {}

	float	fX;
	float	fY;
}LINEPOS;

typedef struct tagLineInfo
{
	tagLineInfo() { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(LINEPOS& _tLeftPos, LINEPOS& _tRightPos)
		: tLeftPos(_tLeftPos), tRightPos(_tRightPos) {}


	LINEPOS		tLeftPos;
	LINEPOS		tRightPos;
}LINEINFO;

typedef struct tagFrame
{
	enum PLAYTYPE { LOOP, NO_LOOP, REVERSE_NO_LOOP, PLAYTYPE_END};
	int		iStartX;
	int		iEndX;
	int		iFrameX;
	int		iModelY;
	DWORD	dwDelay;
	DWORD	dwTime;
	PLAYTYPE	ePlayType;
}FRAME;

typedef struct tagHit
{
	enum ECOLLISIONTYPE { NO_COLLOSION=1, BLOCK, KILL};
	int				iX;
	int				iY;
	ECOLLISIONTYPE	eHitType;
}HITINFO;

#endif // !__STRUCT_H__
