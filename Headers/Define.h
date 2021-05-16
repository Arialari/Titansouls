#pragma once

#ifndef __DEFINE_H__
#define __DEFINE_H__

#define DELTATIME_MS	10
#define DELTATIME_S		(float)(DELTATIME_MS / 1000.f)

#define WINCX	800
#define WINCY	600

#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }

#define OBJ_NOEVENT		0
#define OBJ_DEAD		1

#define PI	3.141592f

#define PIXELCX 16
#define PIXELCY 16

#define DEFAULTCX 32
#define DEFAULTCY 32

#define TILEX 100
#define TILEY 500

#endif // !__DEFINE_H__
