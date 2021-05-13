#pragma once

#ifndef __DEFINE_H__
#define __DEFINE_H__

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

#define TILEX 30
#define TILEY 20

#endif // !__DEFINE_H__
