#pragma once

#include "Vectors.h"
#include "VectorGloabalFuncs.h"
#include "Matrices.h"
#include "Quaternion.h"

namespace gm
{
	typedef Vec<2, float> float2;
	typedef Vec<3, float> float3;
	typedef Vec<4, float> float4;
	typedef Mat<4, 4, float> float4x4;
	typedef Mat<3, 3, float> float3x3;
	typedef Mat<2, 2, float> float2x2;
	typedef Quat<float> Quaternion;

	const double PIDouble = 3.1415926535897932384626433832795;
	const float PI = PIDouble;
	const float RadToDeg = 180.0 / PI;
	const float DegToRad = PI / 180.0;
}