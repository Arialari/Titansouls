#pragma once

#ifndef __ENUM_H__
#define __ENUM_H__

namespace OBJID
{
	enum ID { BACKGROUND, PLAYER, TITAN, ARROW, COLLISION , UI, END };
}

namespace RENDERID
{
	enum ID { BACKGROUND, FOLIAGE, OBJECT, CELLING, EFFECT, UI, END };
}
namespace SCENEID
{
	enum ID { HALLWAY_UNDER, SLUDGE, BARIN_FREEZE, EYE_CUBE, GOL_SET, SCENDID_END };
}
namespace UI_TYPE
{
	enum ID { LAYOUT, BUTTON, IMAGE, UI_TYPE_END };
}

enum DIRECTION { E, N, W, S, SE, SW, NW, NE, DIRECTION_END };

#endif // !__ENUM_H__
