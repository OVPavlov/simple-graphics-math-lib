#pragma once
#include <ostream>
#include <cmath>

namespace gm 
{
	template<typename T>
	using IsFloat = typename std::enable_if<std::is_floating_point<T>::value, int>::type;
	template<typename T>
	using IsInt = typename std::enable_if<std::is_integral<T>::value, int>::type;
	template<typename T>
	using IsAny = typename std::enable_if<true, int>::type;
	template<bool B>
	using IF = typename std::enable_if<B, int>::type;

	#pragma region VecBase
	template<int L, typename T>
	struct Vec;

	template<int L, typename T>
	struct VecBase
	{
		union {
			T values[L];
		};
		operator Vec<L, T>() const { return reinterpret_cast<Vec<L, T>>(this); }
	};

	template<typename T>
	struct VecBase<2, T>
	{
		union {
			T values[2];
			struct { T x, y; };
		};

		static const VecBase left;
		static const VecBase right;
		static const VecBase up;
		static const VecBase down;
		operator Vec<2, T>() const { return reinterpret_cast<Vec<2, T>>(this); }
	};

	template<class T>
	const VecBase<2, T> VecBase<2, T>::left{-1, 0};
	template<class T>
	const VecBase<2, T> VecBase<2, T>::right{1, 0};
	template<class T>
	const VecBase<2, T> VecBase<2, T>::up{0, 1};
	template<class T>
	const VecBase<2, T> VecBase<2, T>::down{0, -1};

	template<typename T>
	struct VecBase<3, T>
	{
		union {
			T values[3];
			struct { T x, y, z; };
			struct { Vec<2, T> xy; };
		};
		static const VecBase left;
		static const VecBase right;
		static const VecBase up;
		static const VecBase down;
		static const VecBase forward;
		static const VecBase backward;
		operator Vec<3, T>() const { return reinterpret_cast<Vec<3, T>>(this); }
	};

	template<class T>
	const VecBase<3, T> VecBase<3, T>::left{-1, 0, 0};
	template<class T>
	const VecBase<3, T> VecBase<3, T>::right{1, 0, 0};
	template<class T>
	const VecBase<3, T> VecBase<3, T>::up{0, 1, 0};
	template<class T>
	const VecBase<3, T> VecBase<3, T>::down{0, -1, 0};
	template<class T>
	const VecBase<3, T> VecBase<3, T>::forward{0, 0, 1};
	template<class T>
	const VecBase<3, T> VecBase<3, T>::backward{0, 0, -1};

	template<typename T>
	struct VecBase<4, T>
	{
		union {
			T values[4];
			struct {T x, y, z, w;};
			struct {Vec<2, T> xy, zw;};
			struct {Vec<3, T> xyz;};
		};
		static const VecBase left;
		static const VecBase right;
		static const VecBase up;
		static const VecBase down;
		static const VecBase forward;
		static const VecBase backward;
		operator Vec<4, T>() const { return reinterpret_cast<Vec<4, T>>(this); }
	};

	template<class T>
	const VecBase<4, T> VecBase<4, T>::left{-1, 0, 0, 0};
	template<class T>
	const VecBase<4, T> VecBase<4, T>::right{1, 0, 0, 0};
	template<class T>
	const VecBase<4, T> VecBase<4, T>::up{0, 1, 0, 0};
	template<class T>
	const VecBase<4, T> VecBase<4, T>::down{0, -1, 0, 0};
	template<class T>
	const VecBase<4, T> VecBase<4, T>::forward{0, 0, 1, 0};
	template<class T>
	const VecBase<4, T> VecBase<4, T>::backward{0, 0, -1, 0};
	#pragma endregion VecBase


#pragma region OverloadOpMacro

#define OVERLOAD_OP_IN(op)															\
	inline constexpr Vec<L, T> operator op (const Vec<L, T>& other) const {			\
		Vec <L, T> y;																\
		for (int i = 0; i < L; ++i)													\
			y.values[i] = this->values[i] op other.values[i];						\
		return y;																	\
	}																				\
	inline constexpr Vec<L, T> operator op (const T& other) const {					\
		Vec <L, T> y;																\
		for (int i = 0; i < L; ++i)													\
			y.values[i] = this->values[i] op other;									\
		return y;																	\
	}																				\
	inline constexpr Vec<L, T>& operator op##= (const Vec<L, T>& other) {			\
		for (int i = 0; i < L; ++i)													\
			this->values[i] op##= other.values[i];									\
		return *this;																\
	}																				\
	inline constexpr Vec<L, T>& operator op##= (const T& other) {					\
		for (int i = 0; i < L; ++i)													\
			this->values[i] op##= other;											\
		return *this;																\
	}


#define OVERLOAD_OP_A(op, Cond)															\
	template<int L, typename T, Cond<T> = 0>											\
	inline  Vec<L, T> operator op (const Vec<L, T> &a, const Vec<L, T> &b) 				\
	{																					\
		Vec<L, T> y;																	\
		for (int i = 0; i < L; ++i) 													\
			y[i] = a[i] op b[i];														\
		return y;																		\
	}																					\
	template<int L, typename T, Cond<T> = 0>											\
	inline Vec<L, T> & operator op##= (Vec<L, T> &a, const Vec<L, T> &b) 				\
	{																					\
		for (int i = 0; i < L; ++i) 													\
			a[i] op##= b[i];															\
		return a;																		\
	}																					\
	template<int L, typename T, Cond<T> = 0>											\
	inline Vec<L, T> operator op (const Vec<L, T> &a, const T &b) 						\
	{																					\
		Vec<L, T> y;																	\
		for (int i = 0; i < L; ++i) 													\
			y[i] = a[i] op b;															\
		return y;																		\
	}																					\
	template<int L, typename T, Cond<T> = 0>											\
	inline Vec<L, T> & operator op##= (Vec<L, T> &a, const T &b)						\
	{																					\
		for (int i = 0; i < L; ++i) 													\
			a[i] op##= b;																\
		return a;																		\
	}																					\


#define OVERLOAD_OP_B(op, Cond)															\
	template<int L, typename T, Cond<T> = 0>											\
	inline Vec<L, T> operator op (const T &a, const Vec<L, T> &b) 						\
	{																					\
		Vec<L, T> y;																	\
		for (int i = 0; i < L; ++i) 													\
			y[i] = a op b[i];															\
		return y;																		\
	}

#pragma endregion OverloadOpMacro



	template<int L, typename T>
	struct Vec: public VecBase<L, T>
	{
		inline constexpr T& operator[](int i)
		{
			return this->values[i];
		}
		inline constexpr const T& operator[](int i) const
		{
			return this->values[i];
		}

		static const Vec zero;
		static const Vec one;

		inline constexpr Vec() = default;
		inline constexpr Vec(const Vec<L, T>& v) = default;
		inline constexpr Vec(const T x)
		{ 
			for (int i = 0; i < L; i++)
				this->values[i] = x;
		}

		template<typename T2>
		inline constexpr Vec(const Vec<L, T2>& val){
			for (int i = 0; i < L; i++)
				this->values[i] = static_cast<T>(val.values[i]);
		}




		OVERLOAD_OP_IN(+)
		OVERLOAD_OP_IN(-)
		OVERLOAD_OP_IN(*)
		//OVERLOAD_OP_IN(/)
		inline constexpr Vec<L, T> operator/(const Vec<L, T> &other) const {
			Vec<L, T> y;
			for (int i = 0; i < L; ++i)
				y.values[i] = this->values[i] / other.values[i];
			return y;
		}
		inline constexpr Vec<L, T> operator/(const T &other) const {
			Vec<L, T> y;
			T inv = static_cast<T>(1) / other;
			for (int i = 0; i < L; ++i)
				y.values[i] = this->values[i] * inv;
			return y;
		}
		inline constexpr Vec<L, T> &operator/=(const Vec<L, T> &other) const {
			for (int i = 0; i < L; ++i)
				this->values[i] /= other.values[i];
			return *this;
		}
		inline constexpr Vec<L, T> &operator/=(const T &other) const {
			T inv = static_cast<T>(1) / other;
			for (int i = 0; i < L; ++i)
				this->values[i] *= inv;
			return *this;
		}


		#pragma region UniversalConstructor
	private:


		template<typename T>
		struct vsize{static const int I = 1; };
		template<int L, typename T>
		struct vsize<Vec<L, T>>{static const int I = L; };

		template <typename... Rest>
		struct numof;
		template <typename T2, typename...Rest>
		struct numof<T2, Rest...>{static const int N = vsize<T2>::I + numof<Rest...>::N;};
		template <typename T2>
		struct numof<T2>{static const int N = vsize<T2>::I;};

		template<int Idx, int L2, typename T2, typename... Rest>
		inline constexpr void setValues(const Vec<L2, T2>& other, const Rest&... rest)
		{
			for (int i = 0; i < L2; ++i)
			{
				this->values[Idx + i] = static_cast<T>(other.values[i]);
			}
			setValues<Idx+L2>(rest...);
		}

		template<int Idx, typename T2, typename... Rest>
		inline constexpr void setValues(const T2& value, const Rest&... rest)
		{
			this->values[Idx] = static_cast<T>(value);
			setValues<Idx+1>(rest...);
		}

		template<int I>
		inline constexpr void setValues(){}

	public:
		template<typename... Args, IF<(numof<Args...>::N == L)> = 0>
		Vec(Args... args)
		{
			setValues<0>(args...);
		}
		#pragma endregion UniversalConstructor


	};

	template<int L, typename T>
	const Vec<L, T> Vec<L, T>::zero(0);
	template<int L, typename T>
	const Vec<L, T> Vec<L, T>::one(1);


#define OVERLOAD_OP(op, Cond) 	\
OVERLOAD_OP_A( op,	Cond )      \
OVERLOAD_OP_B( op,	Cond )



	OVERLOAD_OP_B(+,		IsAny)
	OVERLOAD_OP_B(-,		IsAny)
	OVERLOAD_OP_B(*,		IsAny)
	OVERLOAD_OP_B(/,		IsAny)

	OVERLOAD_OP(%,		IsInt)
	OVERLOAD_OP(<<,		IsInt)
	OVERLOAD_OP(>>,		IsInt)
	OVERLOAD_OP(&,		IsInt)
	OVERLOAD_OP(|,		IsInt)
	OVERLOAD_OP(^,		IsInt)


	template<int L, typename T>
	std::ostream& operator << (std::ostream& out, const Vec<L, T> &v)
	{
		out << "(" << v[0];
		for (int i = 1; i < L; ++i)
			out << ", " << v[i];
		out << ")";
		return out;
	}


#undef OVERLOAD_OP
#undef OVERLOAD_OP_A
#undef OVERLOAD_OP_B
#undef OVERLOAD_OP_C
#undef OVERLOAD_OP_IN


}