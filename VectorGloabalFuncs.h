#pragma once
#include <cmath>
#include "Vectors.h"

namespace gm
{

#define STD_MATH_FUNC(func)											\
	template<int L, typename T>										\
	inline Vec<L, T> func##(Vec<L, T> const& v)   					\
	{																\
		Vec<L, T> y;												\
		for (int i = 0; i < L; ++i) 								\
			y[i] = std::##func##(v[i]);								\
		return y;													\
	}																\

#define STD_MATH_BIN_FUNC(func)												\
	template<int L, typename T>												\
	inline Vec<L, T> func##(Vec<L, T>const& a, Vec<L, T>const& b)   		\
	{																		\
		Vec<L, T> y;														\
		for (int i = 0; i < L; ++i)  										\
			y[i] = std::##func##(a[i], b[i]);								\
		return y;															\
	}																		\
	template<int L, typename T>												\
	inline Vec<L, T> func##(Vec<L, T>const& a, T const& b)   				\
	{																		\
		Vec<L, T> y;														\
		for (int i = 0; i < L; ++i)  										\
			y[i] = std::##func##(a[i], b);									\
		return y;															\
	}																		\
	template<int L, typename T>												\
	inline Vec<L, T> func##(T const& a, Vec<L, T>const& b)   				\
	{																		\
		Vec<L, T> y;														\
		for (int i = 0; i < L; ++i)  										\
			y[i] = std::##func##(a, b[i]);									\
		return y;															\
	}																		\


#define MATH_TRIN_FUNC(name, func)															\
	template<int L, typename T>																\
	inline Vec<L, T> name##(const Vec<L, T>& a, const Vec<L, T>& b, const Vec<L, T>& c)   	\
	{																						\
		Vec<L, T> y;																		\
		for (int i = 0; i < L; ++i)  														\
			y[i] = func##(a[i], b[i], c[i]);												\
		return y;																			\
	}																						\
	template<int L, typename T>																\
	inline Vec<L, T> name##(const Vec<L, T>& a, const Vec<L, T>& b, const T& c)   			\
	{																						\
		Vec<L, T> y;																		\
		for (int i = 0; i < L; ++i)   														\
			y[i] = func##(a[i], b[i], c);													\
		return y;																			\
	}																						\
	template<int L, typename T>																\
	inline Vec<L, T> name##(const Vec<L, T>& a, const T& b, const Vec<L, T>& c)   			\
	{																						\
		Vec<L, T> y;																		\
		for (int i = 0; i < L; ++i)   														\
			y[i] = func##(a[i], b, c[i]);													\
		return y;																			\
	}																						\
	template<int L, typename T>																\
	inline Vec<L, T> name##(const Vec<L, T>& a, const T& b, const T& c)   					\
	{																						\
		Vec<L, T> y;																		\
		for (int i = 0; i < L; ++i)  														\
			y[i] = func##(a[i], b, c);														\
		return y;																			\
	}																						\
	template<int L, typename T>																\
	inline Vec<L, T> name##(const T& a, const Vec<L, T>& b, const Vec<L, T>& c)   			\
	{																						\
		Vec<L, T> y;																		\
		for (int i = 0; i < L; ++i)   														\
			y[i] = func##(a, b[i], c[i]);													\
		return y;																			\
	}																						\
	template<int L, typename T>																\
	inline Vec<L, T> name##(const T& a, const Vec<L, T>& b, const T& c)   					\
	{																						\
		Vec<L, T> y;																		\
		for (int i = 0; i < L; ++i)   														\
			y[i] = func##(a, b[i], c);														\
		return y;																			\
	}																						\
	template<int L, typename T>																\
	inline Vec<L, T> name##(const T& a, const T& b, const Vec<L, T>& c)   					\
	{																						\
		Vec<L, T> y;																		\
		for (int i = 0; i < L; ++i)   														\
			y[i] = func##(a, b, c[i]);														\
		return y;																			\
	}																						\


	STD_MATH_FUNC(abs)
	STD_MATH_FUNC(acos)
	STD_MATH_FUNC(asin)
	STD_MATH_FUNC(atan)
	STD_MATH_FUNC(cos)
	STD_MATH_FUNC(ceil)
	STD_MATH_FUNC(cosh)
	STD_MATH_FUNC(exp)
	STD_MATH_FUNC(exp2)
	STD_MATH_FUNC(floor)
	STD_MATH_FUNC(log)
	STD_MATH_FUNC(log2)
	STD_MATH_FUNC(log10)
	//STD_MATH_FUNC(max)
	//STD_MATH_FUNC(min)
	STD_MATH_FUNC(round)
	STD_MATH_FUNC(sin)
	STD_MATH_FUNC(sinh)
	STD_MATH_FUNC(sqrt)
	STD_MATH_FUNC(tan)
	STD_MATH_FUNC(tanh)

	STD_MATH_BIN_FUNC(pow)
	STD_MATH_BIN_FUNC(atan2)
	STD_MATH_BIN_FUNC(fmod)
	STD_MATH_BIN_FUNC(fmin)
	STD_MATH_BIN_FUNC(fmax)


	template<typename T>
	inline T lerp(const T &a, const T &b, const T &t)
	{
		return a + (b - a) * t;
	}
	template<typename T>
	inline T clamp(const T &v, const T &min, const T &max) 
	{
		return std::max(min, std::min(v, max));
	}
	MATH_TRIN_FUNC(lerp, lerp)
	MATH_TRIN_FUNC(clamp, clamp)


	template<int L, typename T>
	inline T dot(const Vec<L, T>& a, const Vec<L, T>& b)
	{
		T result = a[0] * b[0];
		for (int i = 1; i < L; ++i)		
			result += a[i] * b[i];		
		return result;
	}

	template<int L, typename T>
	inline T sqrLength(const Vec<L, T>& a)
	{
		return dot(a, a);
	}

	template<int L, typename T>
	inline T length(const Vec<L, T>& a)
	{
		return std::sqrt(sqrLength(a));
	}

	template<int L, typename T>
	inline T sqrDistance(const Vec<L, T>& a, const Vec<L, T>& b)
	{
		return sqrLength(a - b);
	}

	template<int L, typename T>
	inline T distance(const Vec<L, T>& a, const Vec<L, T>& b)
	{
		return std::sqrt(sqrDistance(a, b));
	}

	template<int L, typename T>
	inline Vec<L, T> normalize(const Vec<L, T>& a)
	{
		T invLength = (T)1 / length(a);
		return a * invLength;
	}

	template<int L, typename T>
	inline T angle(const Vec<L, T>& from, const Vec<L, T>& to)
	{
		const T cosTheta = dot(from, to) / std::sqrt(sqrLength(from) * sqrLength(to));
		return std::acos(std::min((T)1, cosTheta));
	}

	template<typename T>
	inline Vec<3, T> cross(const Vec<3, T>& a, const Vec<3, T>& b) 
	{
		return Vec<3, T> 
		{
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		};
	}


}