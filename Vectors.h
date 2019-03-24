#pragma once
#include <ostream>
#include <cmath>

namespace gm 
{
	template<int L, typename T>
	struct Vec
	{
		T values[L];

		T& operator[](int i)
		{
			return *((T*)this + i);
		}
		const T& operator[](int i) const
		{
			return *((T*)this + i);
		}

		static const Vec zero;
		static const Vec one;
			
		Vec() = default;
		Vec(const  Vec<L, T>& v) = default;
		explicit Vec(const T x)
		{ 
			for (int i = 0; i < L; i++)			
				values[i] = x;			
		}
	};

	template<typename T>
	struct Vec<4, T>
	{
		union
		{
			T values[4];
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			struct { Vec<2, T> xy, zw; };
			struct { Vec<2, T> rg, ba; };
			Vec<2, T> xyz;
			Vec<2, T> rgb;
		};

		static const Vec zero;
		static const Vec one;
		static const Vec left;
		static const Vec right;
		static const Vec up;
		static const Vec down;
		static const Vec forward;
		static const Vec backward;


		T& operator[](int i)
		{
			return *((T*)this + i);
		}
		const T& operator[](int i) const
		{
			return *((T*)this + i);
		}

		Vec() = default;
		Vec(const  Vec<4, T>& v) = default;
		explicit Vec(T x) : x(x), y(x), z(x), w(x) { }
		Vec(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) { }
		Vec(T x, const  Vec<2, T>& v, T w) : x(x), y(v.x), z(v.y), w(w) { }
		Vec(const  Vec<2, T>& va, const  Vec<2, T>& vb) : x(va.x), y(va.y), z(vb.x), w(vb.y) { }
		Vec(T x, const Vec<3, T>& v) : x(x), y(v.x), z(v.y), w(v.z) { }
		Vec(const Vec<3, T>& v, T w) : x(v.x), y(v.y), z(v.z), w(w) { }
		explicit Vec(const Vec<3, T>& v) : x(v.x), y(v.y), z(v.z), w(0) { }
		explicit Vec(const  Vec<2, T>& v) : x(v.x), y(v.y), z(0), w(0) { }
	};

	template<typename T>
	struct Vec<3, T>
	{
		union
		{
			T values[3];
			struct { T x, y, z; };
			struct { T r, g, b; };
			Vec<2, T> xy;
			Vec<2, T> rg;
		};

		static const Vec zero;
		static const Vec one;
		static const Vec left;
		static const Vec right;
		static const Vec up;
		static const Vec down;
		static const Vec forward;
		static const Vec backward;

		T& operator[](int i)
		{
			return *((T*)this + i);
		}
		const T& operator[](int i) const
		{
			return *((T*)this + i);
		}

		Vec() = default;
		Vec(const  Vec<3, T>& v) = default;
		explicit Vec(T x) : x(x), y(x), z(x) { }
		Vec(T x, T y, T z) : x(x), y(y), z(z) { }
		Vec(T x, const  Vec<2, T>& v) : x(x), y(v.x), z(v.y) { }
		Vec(const  Vec<2, T>& v, T z) : x(v.x), y(v.y), z(z) { }
		explicit Vec(const Vec<4, T>& v) : x(v.x), y(v.y), z(v.z) { }
		explicit Vec(const  Vec<2, T>& v) : x(v.x), y(v.y), z(0.0f) { }
	};

	template<typename T>
	struct alignas(2 * sizeof(T)) Vec<2, T>
	{
		union
		{
			T values[2];
			struct { T x, y; };
			struct { T r, g; };			
		};

		static const Vec zero;
		static const Vec one;
		static const Vec left;
		static const Vec right;
		static const Vec up;
		static const Vec down;

		T& operator[](int i)
		{
			return *((T*)this + i);
		}
		const T& operator[](int i) const
		{
			return *((T*)this + i);
		}

		Vec() = default;
		Vec(const Vec<2, T>& v) = default;
		explicit Vec(T x) : x(x), y(x) { }
		Vec(T x, T y) : x(x), y(y) { }
		explicit Vec(const Vec<4, T>& v) : x(v.x), y(v.y) { }
		explicit Vec(const Vec<3, T>& v) : x(v.x), y(v.y) { }
	};

	template<int L, typename T>
	const Vec<L, T> Vec<L, T>::zero(0);
	template<int L, typename T>
	const Vec<L, T> Vec<L, T>::one(1);

	template<class T>
	const Vec<4, T> Vec<4, T>::zero(0);
	template<class T>
	const Vec<4, T> Vec<4, T>::one(1);
	template<class T>
	const Vec<4, T> Vec<4, T>::left{-1, 0, 0, 0};
	template<class T>
	const Vec<4, T> Vec<4, T>::right{1, 0, 0, 0};
	template<class T>
	const Vec<4, T> Vec<4, T>::up{0, 1, 0, 0};
	template<class T>
	const Vec<4, T> Vec<4, T>::down{0, -1, 0, 0};
	template<class T>
	const Vec<4, T> Vec<4, T>::forward{0, 0, 1, 0};
	template<class T>
	const Vec<4, T> Vec<4, T>::backward{0, 0, -1, 0};

	template<class T>
	const Vec<3, T> Vec<3, T>::zero(0);
	template<class T>
	const Vec<3, T> Vec<3, T>::one(1);
	template<class T>
	const Vec<3, T> Vec<3, T>::left{-1, 0, 0};
	template<class T>
	const Vec<3, T> Vec<3, T>::right{1, 0, 0};
	template<class T>
	const Vec<3, T> Vec<3, T>::up{0, 1, 0};
	template<class T>
	const Vec<3, T> Vec<3, T>::down{0, -1, 0};
	template<class T>
	const Vec<3, T> Vec<3, T>::forward{0, 0, 1};
	template<class T>
	const Vec<3, T> Vec<3, T>::backward{0, 0, -1};

	template<class T>
	const Vec<2, T> Vec<2, T>::zero(0);
	template<class T>
	const Vec<2, T> Vec<2, T>::one(1);
	template<class T>
	const Vec<2, T> Vec<2, T>::left{-1, 0};
	template<class T>
	const Vec<2, T> Vec<2, T>::right{1, 0};
	template<class T>
	const Vec<2, T> Vec<2, T>::up{0, 1};
	template<class T>
	const Vec<2, T> Vec<2, T>::down{0, -1};


#define OVERLOAD_OP_A(op)																\
	template<int L, typename T>															\
	inline Vec<L, T> operator op (const Vec<L, T> &a, const Vec<L, T> &b) 				\
	{																					\
		Vec<L, T> y;																	\
		for (int i = 0; i < L; ++i) 													\
			y[i] = a[i] op b[i];														\
		return y;																		\
	}																					\
	template<int L, typename T>															\
	inline Vec<L, T> & operator op##= (Vec<L, T> &a, const Vec<L, T> &b) 				\
	{																					\
		for (int i = 0; i < L; ++i) 													\
			a[i] op##= b[i];															\
		return a;																		\
	}																					\
	template<int L, typename T>															\
	inline Vec<L, T> operator op (const T &a, const Vec<L, T> &b) 						\
	{																					\
		Vec<L, T> y;																	\
		for (int i = 0; i < L; ++i) 													\
			y[i] = a op b[i];															\
		return y;																		\
	}																					\

#define OVERLOAD_OP_B(op)																\
	template<int L, typename T>															\
	inline Vec<L, T> operator op (const Vec<L, T> &a, const T &b) 						\
	{																					\
		Vec<L, T> y;																	\
		for (int i = 0; i < L; ++i) 													\
			y[i] = a[i] op b;															\
		return y;																		\
	}																					\
	template<int L, typename T>															\
	inline Vec<L, T> & operator op##= (Vec<L, T> &a, const T &b)						\
	{																					\
		for (int i = 0; i < L; ++i) 													\
			a[i] op##= b;																\
		return a;																		\
	}																					\

	template<int L, typename T>
	std::ostream& operator << (std::ostream& out, const Vec<L, T> &v)
	{
		out << "(" << v[0];
		for (int i = 1; i < L; ++i)
			out << ", " << v[i];		
		out << ")";
		return out;
	}

	OVERLOAD_OP_A(+)
	OVERLOAD_OP_B(+)
	OVERLOAD_OP_A(-)
	OVERLOAD_OP_B(-)
	OVERLOAD_OP_A(*)
	OVERLOAD_OP_B(*)
	OVERLOAD_OP_A(/)
	// division part B 
	OVERLOAD_OP_A(%)
	OVERLOAD_OP_B(%)

	// division part B 
	template<int L, typename T>
	inline Vec<L, T> operator / (const Vec<L, T> &a, const T &b) 
	{
		Vec<L, T> y;
		T invDiv = (T)1 / b;
		for (int i = 0; i < L; ++i) 
			y[i] = a[i] * invDiv;
		return y;
	}
	template<int L, typename T>
	inline Vec<L, T> & operator /= (const Vec<L, T> &a, const T &b) 
	{
		T invDiv = (T)1 / b;
		for (int i = 0; i < L; ++i) 
			a[i] *= invDiv;
		return a;
	}

	template<int L, typename T>
	inline Vec<L, T> operator -(const Vec<L, T>& v) 
	{
		Vec<L, T> y;
		for (int i = 0; i < L; ++i) 
			y[i] = -v[i];
		return y;
	}
}