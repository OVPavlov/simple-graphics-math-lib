#pragma once
#include <ostream>
#include "Vectors.h"
#include "VectorGloabalFuncs.h"
#include "Quaternion.h"

namespace gm
{
	template<int R, int C, typename T>
	struct Mat
	{
		union
		{
			T values[R * C];
			Vec<R, T> base_vecs[C];
		};

		T& operator[](int i)
		{
			return *((T*)this + i);
		}
		const T& operator[](int i) const
		{
			return *((T*)this + i);
		}
	};


	template<int N, int R, int C, typename T>
	inline Mat<R, C, T> operator * (const Mat<R, N, T> &a, const Mat<N, C, T> &b)
	{
		Mat<R, C, T> y;
		T dot;
		for (int c = 0; c < C; ++c)
		{
			for (int r = 0; r < R; ++r)
			{
				dot = a[0 * R + r] * b[c*N + 0];
				for (int n = 1; n < N; n++)
					dot += a[n*R + r] * b[c*N + n];
				y[c*R + r] = dot;
			}
		}
		return y;
	}

	template<int N, int R, typename T>
	inline Vec<R, T> operator * (const Mat<R, N, T> &a, const Vec<N, T> &b)
	{
		Vec<R, T> y;
		T dot;

		for (int r = 0; r < R; ++r)
		{
			dot = a[0 * R + r] * b[0 * N + 0];
			for (int n = 1; n < N; n++)
				dot += a[n*R + r] * b[0 * N + n];
			y[0 * R + r] = dot;
		}

		return y;
	}

	template<int N, int C, typename T>
	inline Vec<C, T> operator * (const Vec<N, T> &a, const Mat<N, C, T> &b)
	{
		Vec<C, T> y;
		T dot;
		for (int c = 0; c < C; ++c)
		{
			dot = a[0 * 1 + 0] * b[c*N + 0];
			for (int n = 1; n < N; n++)
				dot += a[n * 1 + 0] * b[c*N + n];
			y[c * 1 + 0] = dot;
		}
		return y;
	}


	template<int R, int C, typename T>
	std::ostream& operator << (std::ostream& out, const Mat<R, C, T> &m)
	{
		for (int c = 0; c < C; c++)
		{
			out << "|" << m[c*R];
			for (int r = 1; r < R; r++)
				out << ", " << m[c*R + r];
			out << "|\n";
		}
		return out;
	}


	template<typename T>
	inline Mat<2, 2, T> rotation(const T &radians)
	{
		T sin = std::sin(radians), cos = std::cos(radians);
		return {cos, sin, -sin, cos};
	}

	template<typename T>
	inline Mat<3, 3, T> rotation(const Vec<3, T> &normal, const T &radians)
	{
		T cos = std::cos(radians);
		T omcos = (T)1 - cos;
		Vec<3, T> omcosN = normal * omcos;
		T Nxx = omcosN.x * normal.x;
		T Nxy = omcosN.x * normal.y;
		T Nxz = omcosN.x * normal.z;
		T Nyy = omcosN.y * normal.y;
		T Nyz = omcosN.y * normal.z;
		T Nzz = omcosN.z * normal.z;
		Vec<3, T> nSine = normal * std::sin(radians);

		return 
		{
			Nxx + cos, Nxy - nSine.z, Nxz + nSine.y,
			Nxy + nSine.z, Nyy + cos, Nyz - nSine.x,
			Nxz - nSine.y, Nyz + nSine.x, Nzz + cos,
		};
	}

	template<typename T>
	inline Mat<3, 3, T> rotation(const Vec<3, T> &euler)
	{
		Vec<3, T> sin = sin(euler);
		Vec<3, T> cos = cos(euler);
		T sinxy = sin.x * sin.y;
		T cxsy = cos.x * sin.y;
		return 
		{
			cos.y * cos.z, -cos.y * sin.z, sin.y,
			cos.x * sin.z + sinxy * cos.z, cos.x * cos.z - sinxy * sin.z, -cos.y * sin.x,
			sin.x * sin.z - cxsy * cos.z, cos.z * sin.x + cxsy * sin.z, cos.x * cos.y
		};
	}

	template<typename T>
	inline Mat<3, 3, T> rotation(const Quat<T>& q)
	{
		const T _1 = 1;
		Vec <3, T> q2 = (T)2 * q.n;
		T q2xx = q2.x * q.x;
		T q2xy = q2.x * q.y;
		T q2xz = q2.x * q.z;
		T q2xw = q2.x * q.w;
		T q2yy = q2.y * q.y;
		T q2yz = q2.y * q.z;
		T q2yw = q2.y * q.w;
		T q2zz = q2.z * q.z;
		T q2zw = q2.z * q.w;
		return
		{
			_1 - q2yy - q2zz, q2xy + q2zw, q2xz - q2yw,
			q2xy - q2zw, _1 - q2xx - q2zz, q2yz + q2xw,
			q2xz + q2yw, q2yz - q2xw, _1 - q2xx - q2yy
		};
	}

	template<typename T>
	inline Mat<3, 3, T> scale(const Vec<3, T> &normal, const T &scale)
	{
		const T _1 = 1;
		T scmone = scale - (T)1;
		Vec<3, T> scmoneN = normal * scmone;
		T Nxx = scmoneN.x * normal.x;
		T Nxy = scmoneN.x * normal.y;
		T Nxz = scmoneN.x * normal.z;
		T Nyy = scmoneN.y * normal.y;
		T Nyz = scmoneN.y * normal.z;
		T Nzz = scmoneN.z * normal.z;

		return 
		{
			Nxx + _1, Nxy, Nxz,
			Nxy, Nyy + _1, Nyz,
			Nxz, Nyz, Nzz + _1
		};
	}

	template<typename T>
	inline Mat<2, 2, T> scale(const Vec<2, T> &normal, const T &scale)
	{
		const T _1 = 1;
		T scmone = scale - (T)1;
		Vec<2, T> scmoneN = normal * scmone;
		T Nxx = scmoneN.x * normal.x;
		T Nxy = scmoneN.x * normal.y;
		T Nyy = scmoneN.y * normal.y;

		return 
		{
			Nxx + _1, Nxy,
			Nxy, Nyy + _1
		};
	}

	template<int N, typename T>
	constexpr Mat<N, N, T> diagonal(const Vec<N, T> &diaginal)
	{
		Mat<N, N, T> m;
		for (int c = 0; c < N; ++c)
			for (int r = 0; r < N; ++r)
				m[c*N + r] = c == r ? diaginal[c] : (T)0;
		return m;
	}
	template<int N, typename T>
	constexpr Mat<N, N, T> diagonal(const T value)
	{
		Mat<N, N, T> m;
		for (int c = 0; c < N; ++c)
			for (int r = 0; r < N; ++r)
				m[c*N + r] = c == r ? value : (T)0;
		return m;
	}
	template<int N, typename T>
	constexpr Mat<N, N, T> identity()
	{
		return diagonal<N, T>((T)1);
	}

	template<int R, int C, typename T>
	inline Mat<C, R, T> transpose(const Mat<R, C, T> &m)
	{
		Mat<C, R, T> result;
		for (int c = 0; c < C; c++)
			for (int r = 0; r < R; r++)
				result[r*C + c] = m[c*R + r];
		return result;
	}

	template<typename T>
	inline T determinant(const Mat<2, 2, T> &m)
	{
		return m[0] * m[3] - m[1] * m[2];
	}

	template<typename T>
	inline T determinant(const Mat<3, 3, T> &m)
	{
		return
			+ m[0] * (m[4] * m[8] - m[5] * m[7])
			- m[1] * (m[3] * m[8] - m[5] * m[6])
			+ m[2] * (m[3] * m[7] - m[4] * m[6]);
	}

	template<typename T>
	inline T determinant(const Mat<4, 4, T> &m)
	{
		T d2_01 = m[8] * m[13] - m[9] * m[12];
		T d2_02 = m[8] * m[14] - m[10] * m[12];
		T d2_03 = m[8] * m[15] - m[11] * m[12];
		T d2_12 = m[9] * m[14] - m[10] * m[13];
		T d2_13 = m[9] * m[15] - m[11] * m[13];
		T d2_23 = m[10] * m[15] - m[11] * m[14];
		return
			+ m[0] * (m[5] * d2_23 - m[6] * d2_13 + m[7] * d2_12)
			- m[1] * (m[4] * d2_23 - m[6] * d2_03 + m[7] * d2_02)
			+ m[2] * (m[4] * d2_13 - m[5] * d2_03 + m[7] * d2_01)
			- m[3] * (m[4] * d2_12 - m[5] * d2_02 + m[6] * d2_01);
	}

	template<int N, typename T>
	inline T determinant(const Mat<N, N, T> &m)
	{
		T result = m[0] * determinant(minor(m, 0, 0));
		for (int i = 2; i < N; i += 2)
			result += m[i] * determinant(minor(m, 0, i));

		for (int i = 1; i < N; i += 2)
			result -= m[i] * determinant(minor(m, 0, i));

		return result;
	}

	template<int N, typename T>
	inline Mat<N - 1, N - 1, T> minor(const Mat<N, N, T> &m, int i, int j)
	{
		int iN = i * N;
		Mat<N - 1, N - 1, T> result;
		for (int si = 0, ri = 0; ri < (N - 1)*(N - 1); si += N)
		{
			if (si == iN) si += N;
			int riMax = ri + (N - 1);
			for (int sj = 0; ri < riMax; ++sj, ++ri)
			{
				if (sj == j) ++sj;
				result[ri] = m[si + sj];
			}
		}
		return result;
	}

	template<int N, typename T>
	inline T cofactor(const Mat<N, N, T> &m, int i, int j)
	{
		T result = determinant(minor(m, i, j));
		return (i ^ j) & 1 ? -result : result;
	}

	template<int N, typename T>
	inline Mat<N, N, T> inverse(const Mat<N, N, T> &m)
	{
		Mat<N, N, T> comatrix;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				comatrix[i * N + j] = cofactor(m, i, j);

		T det = m[0] * comatrix[0];
		for (int i = 1; i < N; i++)
			det += m[i] * comatrix[i];

		Mat<N, N, T> result = transpose(comatrix);
		result *= (T)1 / determinant(m);
		return result;
	}

	template<typename T>
	inline Mat<4, 4, T> translate(const Mat<3, 3, T> &m, const Vec<3, T> translation)
	{
		const T _0 = 0;
		const T _1 = 1;
		return Mat<4, 4, T>
		{
			m[0], m[1], m[2], _0,
			m[3], m[4], m[5], _0,
			m[6], m[7], m[8], _0,
			translation.x, translation.y, translation.z, _1
		};
	}

	template<typename T>
	inline Mat<4, 4, T> perspective(T fov, T aspect, T near, T far, bool rightHanded = false)
	{
		const T _1 = 1;
		const T _0 = 0;
		T const tanHalfFov = std::tan(fov * (T)0.5);

		T invRange = _1 / (far - near);

		T xs = _1 / (aspect * tanHalfFov);
		T ys = _1 / tanHalfFov;

		T zs = (far + near) * invRange;

		T m23 = _1;
		T m32 = far * near * invRange * (T)(-2);

		if (rightHanded)
		{
			m23 = -m23;
			zs = -zs;
		}
		return
		{
			xs, _0, _0, _0,
			_0, ys, _0, _0,
			_0, _0, zs, m23,
			_0, _0, m32, _0,
		};
	}

	template<typename T>
	inline Mat<4, 4, T> ortho(Vec<3, T> max, Vec<3, T> min, bool rightHanded = false)
	{
		const T _0 = 0;
		const T _1 = 1;
		const T _2 = 2;

		Vec<3, T> invRange = _1 / (max - min);
		Vec<3, T> mul = invRange * _2;
		Vec<3, T> add = invRange * -(max + min);

		if (rightHanded)
		{
			mul.z = -mul.z;
		}
		return 
		{
			mul.x, _0, _0, _0,
			_0, mul.y, _0, _0,
			_0, _0, mul.z, _0,
			add.x, add.y, add.z, _1,
		};
	}

	template<typename T>
	inline Mat<4, 4, T> ortho(T left, T right, T bottom, T top, T near, T far, bool rightHanded = false)
	{
		return ortho({right, top, far}, {left, bottom, near}, rightHanded);
	}


#define OVERLOAD_OP_MAT(op)																	\
	template<int R, int C, typename T>														\
	inline Mat<R, C, T> operator op (const Mat<R, C, T> &a, const Mat<R, C, T> &b)			\
	{																						\
		Mat<R, C, T> y;																		\
		for (int i = 0; i < C * R; i++)														\
			y[i] = a[i] op b[i];															\
		return y;																			\
	}																						\
	template<int R, int C, typename T>														\
	inline Mat<R, C, T> & operator op##= (Mat<R, C, T> &a, const Mat<R, C, T> &b)			\
	{																						\
		for (int i = 0; i < C * R; i++)														\
			a[i] op##= b[i];																\
		return a;																			\
	}																						\

#define OVERLOAD_OP_SCAL(op)																\
	template<int R, int C, typename T>														\
	inline Mat<R, C, T> operator op (const Mat<R, C, T> &a, const T &b)						\
	{																						\
		Mat<R, C, T> y;																		\
		for (int i = 0; i < C * R; i++)														\
			y[i] = a[i] op b;																\
		return y;																			\
	}																						\
	template<int R, int C, typename T>														\
	inline Mat<R, C, T> operator op (const T &a, const Mat<R, C, T> &b)						\
	{																						\
		Mat<R, C, T> y;																		\
		for (int i = 0; i < C * R; i++)														\
			y[i] = a op b[i];																\
		return y;																			\
	}																						\
	template<int R, int C, typename T>														\
	inline Mat<R, C, T> & operator op##= (Mat<R, C, T> &a, const T &b)						\
	{																						\
		for (int i = 0; i < C * R; i++)														\
			a[i] op##= b;																	\
		return a;																			\
	}																						\


	template<int R, int C, typename T>
	inline Mat<R, C, T> operator / (const Mat<R, C, T> &a, const T &b)
	{
		T invDiv = (T)1 / b;
		Mat<R, C, T> y;
		for (int i = 0; i < C * R; i++)
			y[i] = a[i] * invDiv;
		return y;
	}
	template<int R, int C, typename T>
	inline Mat<R, C, T> operator / (const T &a, const Mat<R, C, T> &b)
	{
		Mat<R, C, T> y;
		for (int i = 0; i < C * R; i++)
			y[i] = a / b[i];
		return y;
	}
	template<int R, int C, typename T>
	inline Mat<R, C, T> & operator /= (Mat<R, C, T> &a, const T &b)
	{
		T invDiv = (T)1 / b;
		for (int i = 0; i < C * R; i++)
			a[i] *= invDiv;
		return a;
	}


	OVERLOAD_OP_SCAL(*)
	OVERLOAD_OP_MAT(/)
	OVERLOAD_OP_MAT(+)
	OVERLOAD_OP_SCAL(+)
	OVERLOAD_OP_MAT(-)
	OVERLOAD_OP_SCAL(-)

	template<int R, int C, typename T>
	inline Mat<R, C, T> operator -(const Mat<R, C, T> &b)
	{
		Mat<R, C, T> y;
		for (int i = 0; i < C * R; i++)
			y[i] = -b.values[i];
		return y;
	}

}