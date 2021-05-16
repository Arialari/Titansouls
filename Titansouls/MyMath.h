#pragma once

#ifndef __MYMAYH_H__
#define __MYMAYH_H__

namespace MyMath
{
	template <typename T>
	const T& Clamp( const T& t, const T& min, const T& max )
	{
		if ( t < min )
			return min;
		else if ( t > max )
			return max;
		else
			return t;
	}

	float FInterpTo( float _fCurrent, float _fTarget, float _fDeltaTime, float _fInterpSpeed );

}


#endif // !__MYMAYH_H__
