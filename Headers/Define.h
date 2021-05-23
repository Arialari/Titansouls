#pragma once

#ifndef __DEFINE_H__
#define __DEFINE_H__

#define DELTATIME_MS	10
#define DELTATIME_S		(float)(DELTATIME_MS / 1000.f)

#define WINCX	1024
#define WINCY	768

#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }

#define OBJ_NOEVENT		0
#define OBJ_DESTROYED	1

#define PI	3.141592f

#define PIXELCX 16
#define PIXELCY 16

#define DEFAULTCX 40
#define DEFAULTCY 40

#define TILEX 300
#define TILEY 1000

#endif // !__DEFINE_H__
