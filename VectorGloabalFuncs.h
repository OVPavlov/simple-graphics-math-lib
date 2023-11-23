#pragma once
#include <cmath>
#include "Vectors.h"

namespace gm
{

#define MATH_UN_FUNC(name, func, Cond)									\
	template<int L, typename T, Cond<T> = true>							\
	inline constexpr Vec<L, T> name##(Vec<L, T> const& v) noexcept {	\
		Vec<L, T> y;													\
		for (int i = 0; i < L; ++i) 									\
			y[i] = func##(v[i]);										\
		return y;														\
	}																	\

#define MATH_BIN_FUNC(name, func, Cond)										\
	template<int L, typename T, Cond<T> = true>								\
	inline constexpr Vec<L, T> name##(Vec<L, T>const& a, Vec<L, T>const& b) noexcept   		\
	{																		\
		Vec<L, T> y;														\
		for (int i = 0; i < L; ++i)  										\
			y[i] = func##(a[i], b[i]);										\
		return y;															\
	}																		\
	template<int L, typename T, Cond<T> = true>								\
	inline constexpr Vec<L, T> name##(Vec<L, T>const& a, T const& b) noexcept   \
	{																		\
		Vec<L, T> y;														\
		for (int i = 0; i < L; ++i)  										\
			y[i] = func##(a[i], b);											\
		return y;															\
	}																		\
	template<int L, typename T, Cond<T> = true>								\
	inline constexpr Vec<L, T> name##(T const& a, Vec<L, T>const& b) noexcept  	\
	{																		\
		Vec<L, T> y;														\
		for (int i = 0; i < L; ++i)  										\
			y[i] = func##(a, b[i]);											\
		return y;															\
	}																		\


#define MATH_TRIN_FUNC(name, func)															\
	template<int L, typename T>																\
	inline constexpr Vec<L, T> name##(const Vec<L, T>& a, const Vec<L, T>& b, const Vec<L, T>& c) noexcept  \
	{																						\
		Vec<L, T> y;																		\
		for (int i = 0; i < L; ++i)  														\
			y[i] = func##(a[i], b[i], c[i]);												\
		return y;																			\
	}																						\
	template<int L, typename T>																\
	inline constexpr Vec<L, T> name##(const Vec<L, T>& a, const Vec<L, T>& b, const T& c) noexcept  \
	{																						\
		Vec<L, T> y;																		\
		for (int i = 0; i < L; ++i)   														\
			y[i] = func##(a[i], b[i], c);													\
		return y;																			\
	}																						\
	template<int L, typename T>																\
	inline constexpr Vec<L, T> name##(const Vec<L, T>& a, const T& b, const Vec<L, T>& c) noexcept  \
	{																						\
		Vec<L, T> y;																		\
		for (int i = 0; i < L; ++i)   														\
			y[i] = func##(a[i], b, c[i]);													\
		return y;																			\
	}																						\
	template<int L, typename T>																\
	inline constexpr Vec<L, T> name##(const Vec<L, T>& a, const T& b, const T& c) noexcept  \
	{																						\
		Vec<L, T> y;																		\
		for (int i = 0; i < L; ++i)  														\
			y[i] = func##(a[i], b, c);														\
		return y;																			\
	}																						\
	template<int L, typename T>																\
	inline constexpr Vec<L, T> name##(const T& a, const Vec<L, T>& b, const Vec<L, T>& c) noexcept  \
	{																						\
		Vec<L, T> y;																		\
		for (int i = 0; i < L; ++i)   														\
			y[i] = func##(a, b[i], c[i]);													\
		return y;																			\
	}																						\
	template<int L, typename T>																\
	inline constexpr Vec<L, T> name##(const T& a, const Vec<L, T>& b, const T& c) noexcept  \
	{																						\
		Vec<L, T> y;																		\
		for (int i = 0; i < L; ++i)   														\
			y[i] = func##(a, b[i], c);														\
		return y;																			\
	}																						\
	template<int L, typename T>																\
	inline constexpr Vec<L, T> name##(const T& a, const T& b, const Vec<L, T>& c) noexcept  \
	{																						\
		Vec<L, T> y;																		\
		for (int i = 0; i < L; ++i)   														\
			y[i] = func##(a, b, c[i]);														\
		return y;																			\
	}																						\


	MATH_UN_FUNC(abs, 	::abs,	IsAny)
	MATH_UN_FUNC(acos, 	::acos,	IsFloat)
	MATH_UN_FUNC(asin, 	::asin,	IsFloat)
	MATH_UN_FUNC(atan, 	::atan,	IsFloat)
	MATH_UN_FUNC(cos, 	::cos,	IsFloat)
	MATH_UN_FUNC(ceil, 	::ceil,	IsFloat)
	MATH_UN_FUNC(cosh, 	::cosh,	IsFloat)
	MATH_UN_FUNC(exp, 	::exp,	IsFloat)
	MATH_UN_FUNC(exp2, 	::exp2,	IsFloat)
	MATH_UN_FUNC(floor, ::floor,IsFloat)
	MATH_UN_FUNC(log, 	::log,	IsFloat)
	MATH_UN_FUNC(log2, 	::log2,	IsFloat)
	MATH_UN_FUNC(log10, ::log10,IsFloat)
	MATH_UN_FUNC(round, ::round,IsFloat)
	MATH_UN_FUNC(sin, 	::sin,	IsFloat)
	MATH_UN_FUNC(sinh, 	::sinh,	IsFloat)
	MATH_UN_FUNC(sqrt, 	::sqrt,	IsFloat)
	MATH_UN_FUNC(tan, 	::tan,	IsFloat)
	MATH_UN_FUNC(tanh, 	::tanh,	IsFloat)

	MATH_BIN_FUNC(pow,	::pow,		IsFloat)
	MATH_BIN_FUNC(atan2,::atan2,	IsFloat)
	MATH_BIN_FUNC(mod, 	::fmod,		IsFloat)
	MATH_BIN_FUNC(min, 	std::min,	IsAny)
	MATH_BIN_FUNC(max, 	std::fmax,	IsAny)


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


	template<int L, typename T, IsFloat<T> = true>
	inline T dot(const Vec<L, T>& a, const Vec<L, T>& b)
	{
		T result = a[0] * b[0];
		for (int i = 1; i < L; ++i)		
			result += a[i] * b[i];		
		return result;
	}

	template<int L, typename T, IsFloat<T> = true>
	inline T sqrLength(const Vec<L, T>& a)
	{
		return dot(a, a);
	}

	template<int L, typename T, IsFloat<T> = true>
	inline T length(const Vec<L, T>& a)
	{
		return std::sqrt(sqrLength(a));
	}

	template<int L, typename T, IsFloat<T> = true>
	inline T sqrDistance(const Vec<L, T>& a, const Vec<L, T>& b)
	{
		return sqrLength(a - b);
	}

	template<int L, typename T, IsFloat<T> = true>
	inline T distance(const Vec<L, T>& a, const Vec<L, T>& b)
	{
		return std::sqrt(sqrDistance(a, b));
	}

	template<int L, typename T, IsFloat<T> = true>
	inline Vec<L, T> normalize(const Vec<L, T>& a)
	{
		T invLength = (T)1 / length(a);
		return a * invLength;
	}

	template<int L, typename T, IsFloat<T> = true>
	inline T angle(const Vec<L, T>& from, const Vec<L, T>& to)
	{
		const T cosTheta = dot(from, to) / std::sqrt(sqrLength(from) * sqrLength(to));
		return std::acos(std::min((T)1, cosTheta));
	}

	template<typename T, IsFloat<T> = true>
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