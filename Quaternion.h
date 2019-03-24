#pragma once
#include "Vectors.h"
#include <ostream>
#include <cmath>

namespace gm
{
	template<typename T>
	struct alignas(4 * sizeof(T)) Quat
	{
		union
		{
			struct { T x, y, z, w; };
			struct { T i, j, k; };
			Vec<3, T> n;
			Vec<4, T> vec4;
		};

		static const Quat identity;

		T& operator[](int i)
		{
			return *((T*)this + i);
		}
		const T& operator[](int i) const
		{
			return *((T*)this + i);
		}

		Quat() = default;
		Quat(const Quat<T>& v) = default;
		Quat(const Vec<3, T>& n, T w) : x(n.x), y(n.y), z(n.z), w(w) {}
		Quat(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

		Vec<3, T> right() const
		{
			const T _1 = 1;
			const T _2 = 2;
			return
			{
				_1 - _2 * (y * y + z * z),
				_2 * (x * y + z * w),
				_2 * (x * z - y * w)
			};
		}

		Vec<3, T> up() const
		{
			const T _1 = 1;
			const T _2 = 2;
			return
			{
				_2 * (x * y - z * w),
				_1 - _2 * (x * x + z * z),
				_2 * (y * z + x * w),
			};
		}

		Vec<3, T> forward() const
		{
			const T _1 = 1;
			const T _2 = 2;
			return
			{
				_2 * (x * z + y * w),
				_2 * (y * z - x * w),
				_1 - _2 * (x * x + y * y)
			};
		}

		static Quat angleAxis(const Vec<3, T>& axis, T angle);
		static Quat euler(const Vec<3, T>& euler);
		static Quat euler(const T& x, const T& y, const T& z);
	};

	template<class T>
	const Quat<T> Quat<T>::identity(0, 0, 0, 1);

	template<class T>
	Quat<T> Quat<T>::angleAxis(const Vec<3, T>& axis, T angle)
	{
		T halfAngle = angle * (T)0.5;
		return Quat<T>(axis * std::sin(halfAngle), std::cos(halfAngle));
	}

	template<class T>
	Quat<T> Quat<T>::euler(const Vec<3, T>& degrees)
	{
		Vec<3, T> halfRad = degrees * (T)0.00872664625995;
		Vec<3, T> cosA = cos(halfRad);
		Vec<3, T> sinA = sin(halfRad);
		return Quat<T>(
			sinA.x * cosA.y * cosA.z + cosA.x * sinA.y * sinA.z,
			cosA.x * sinA.y * cosA.z - sinA.x * cosA.y * sinA.z,
			cosA.x * cosA.y * sinA.z + sinA.x * sinA.y * cosA.z,
			cosA.x * cosA.y * cosA.z - sinA.x * sinA.y * sinA.z);
	}

	template<class T>
	Quat<T> Quat<T>::euler(const T& xDegrees, const T& yDegrees, const T& zDegrees)
	{
		return Quat<T>::euler(Vec<3, T>(xDegrees, yDegrees, zDegrees));
	}

	template<typename T>
	inline Quat<T> lerp(const Quat<T> &a, const Quat<T> &b, T t)
	{
		return a + (b - a) * t;
	}

	template<typename T>
	inline Quat<T> slerp(Quat<T> a, const Quat<T> &b, T t)
	{
		const T _0 = 0;
		const T _1 = 1;

		T cosA = dot(a.vec4, b.vec4);
		if (cosA < _0)
		{
			a.vec4 = -a.vec4;
			cosA = -cosA;
		}
		cosA = std::fmin(cosA, _1);



		T aMul, bMul;
		if (std::abs(cosA) > static_cast<T>(0.9999))
		{
			aMul = _1 - t;
			bMul = t;
		}
		else
		{
			T angle = std::acos(cosA);
			T sin = std::sin(angle);

			T invSin = _1 / sin;
			aMul = invSin * std::sin(angle * (_1 - t));
			bMul = invSin * std::sin(angle * t);
		}
		return a * aMul + b * bMul;
	}

	template<typename T>
	inline Quat<T> pow(const Quat<T> &q, const T p)
	{
		T aOld = std::acos(q.w);
		T aNew = aOld * p;
		//todo n *= sqrt(1-aNew*aNew) / sqrt(1-a.w*a.w)
		return Quat<T>(q.n * std::sin(aNew) / std::sin(aOld), std::cos(aNew));
	}

	template<typename T>
	inline Quat<T> inverse(const Quat<T> &q)
	{
		return Quat<T>{-q.x, -q.y, -q.z, q.w};
	}

	template<typename T>
	inline Quat<T> operator*(const Quat<T>& a, const T &b)
	{
		return Quat<T>{a.x * b, a.y * b, a.z * b, a.w * b};
	}
	template<typename T>
	inline Quat<T> operator*(const T &a, const Quat<T>& b)
	{
		return Quat<T>{b.x * a, b.y * a, b.z * a, b.w * a};
	}
	template<typename T>
	inline Quat<T> & operator *= (Quat<T> &a, const T &b)
	{
		a.x *= b;
		a.y *= b;
		a.z *= b;
		a.w *= b;
		return a;
	}

	template<typename T>
	inline Quat<T> operator+(const Quat<T>& a, const T &b)
	{
		return Quat<T>{a.x + b, a.y + b, a.z + b, a.w + b};
	}
	template<typename T>
	inline Quat<T> operator+(const T &a, const Quat<T>& b)
	{
		return Quat<T>{b.x + a, b.y + a, b.z + a, b.w + a};
	}
	template<typename T>
	inline Quat<T> & operator += (Quat<T> &a, const T &b)
	{
		a.x += b;
		a.y += b;
		a.z += b;
		a.w += b;
		return a;
	}
	template<typename T>
	inline Quat<T> operator+(const Quat<T>& a, const Quat<T>& b)
	{
		return Quat<T>{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
	}
	template<typename T>
	inline Quat<T> & operator += (Quat<T> &a, const Quat<T>& b)
	{
		a.x += b.x;
		a.y += b.y;
		a.z += b.z;
		a.w += b.w;
		return a;
	}

	template<typename T>
	inline Quat<T> operator-(const Quat<T>& a, const T &b)
	{
		return Quat<T>{a.x - b, a.y - b, a.z - b, a.w - b};
	}
	template<typename T>
	inline Quat<T> operator-(const T &a, const Quat<T>& b)
	{
		return Quat<T>{b.x - a, b.y - a, b.z - a, b.w - a};
	}
	template<typename T>
	inline Quat<T> & operator -= (Quat<T> &a, const T &b)
	{
		a.x -= b;
		a.y -= b;
		a.z -= b;
		a.w -= b;
		return a;
	}
	template<typename T>
	inline Quat<T> operator-(const Quat<T>& a, const Quat<T>& b)
	{
		return Quat<T>{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
	}
	template<typename T>
	inline Quat<T> & operator -= (Quat<T> &a, const Quat<T>& b)
	{
		a.x -= b.x;
		a.y -= b.y;
		a.z -= b.z;
		a.w -= b.w;
		return a;
	}

	template<typename T>
	inline Quat<T> operator*(const Quat<T>& a, const Quat<T>& b)
	{
		return Quat<T>
		{
			a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
			a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z,
			a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x,
			a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z
		};
	}
	template<typename T>
	inline Quat<T> & operator *= (Quat<T> &a, const Quat<T>& b)
	{
		a.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
		a.y = a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z;
		a.z = a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x;
		a.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
		return a;
	}

	template<typename T>
	inline Vec<3, T> operator*(const Quat<T>& q, const Vec<3, T>& v)
	{
		const Vec<3, T> t = 2.0f * cross(q.n, v);
		return v + q.w * t + cross(q.n, t);
	}

	template<typename T>
	std::ostream& operator << (std::ostream& out, const Quat<T>& q)
	{
		out << "(" << q.i << "i + " << q.j << "j + " << q.k << "k + " << q.w << ")";
		return out;
	}
}