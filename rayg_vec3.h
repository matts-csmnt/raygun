#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>

//ray_g Vector3 class:
//Vector representation of 3 floating point values
//Planned: SIMD?...

namespace ray_g {

	class Vec3 {
	public:
		Vec3() {};
		Vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; };
		Vec3(float e012) { e[0] = e012; e[1] = e012; e[2] = e012;}

		//Accessors
		inline float x() const { return e[0]; };
		inline float y() const { return e[1]; };
		inline float z() const { return e[2]; };
		inline float r() const { return e[0]; };
		inline float g() const { return e[1]; };
		inline float b() const { return e[2]; };

		//Swizzles
		//..planned

		//+/-
		inline const Vec3& operator+() const { return *this; };
		inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); };

		//idx
		inline float operator[](int i) const { return e[i]; };
		inline float& operator[](int i) { return e[i]; };

		//Math
		inline Vec3& operator+=(const Vec3&);
		inline Vec3& operator-=(const Vec3&);
		inline Vec3& operator*=(const Vec3&);
		inline Vec3& operator/=(const Vec3&);
		inline Vec3& operator*=(const float);
		inline Vec3& operator/=(const float);

		inline Vec3& operator+=(const float);

		//More Math
		inline float length() const { return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); };
		inline float squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; };
		inline void make_unit_vector();

		//float array
		float e[3];

	private:
	};

	//Implementation
	//Streams
	inline std::istream& operator>>(std::istream &is, Vec3 &t) 
	{
		is >> t.e[0] >> t.e[1] >> t.e[2];
		return is;
	}

	inline std::ostream& operator<<(std::ostream &os, const Vec3 &t) 
	{
		os << t.e[0] << " " << t.e[1] << " " << t.e[2];
		return os;
	}

	//Dot & Cross
	inline float dot(const Vec3 &v1, const Vec3 &v2) 
	{
		return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
	}

	inline Vec3 cross(const Vec3 &v1, const Vec3 &v2) 
	{
		return Vec3((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
			(-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
			(v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
	}

	//Basic Math
	inline Vec3& Vec3::operator+=(const Vec3 &v) 
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	inline Vec3& Vec3::operator+=(const float f)
	{
		e[0] += f;
		e[1] += f;
		e[2] += f;
		return *this;
	}

	inline Vec3& Vec3::operator*=(const Vec3 &v) 
	{
		e[0] *= v.e[0];
		e[1] *= v.e[1];
		e[2] *= v.e[2];
		return *this;
	}

	inline Vec3& Vec3::operator/=(const Vec3 &v) 
	{
		e[0] /= v.e[0];
		e[1] /= v.e[1];
		e[2] /= v.e[2];
		return *this;
	}

	inline Vec3& Vec3::operator-=(const Vec3& v) 
	{
		e[0] -= v.e[0];
		e[1] -= v.e[1];
		e[2] -= v.e[2];
		return *this;
	}

	inline Vec3& Vec3::operator*=(const float t) 
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	inline Vec3& Vec3::operator/=(const float t) 
	{
		float k = 1.0 / t;

		e[0] *= k;
		e[1] *= k;
		e[2] *= k;
		return *this;
	}

	inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2)
	{
		return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
	}

	inline Vec3 operator+(const Vec3 &v1, const float f)
	{
		return Vec3(v1.e[0] + f, v1.e[1] + f, v1.e[2] + f);
	}

	inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2)
	{
		return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
	}

	inline Vec3 operator-(const Vec3 &v1, const float f)
	{
		return Vec3(v1.e[0] - f, v1.e[1] - f, v1.e[2] - f);
	}

	inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2)
	{
		return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
	}

	inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2)
	{
		return Vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
	}

	inline Vec3 operator*(float t, const Vec3 &v)
	{
		return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
	}

	inline Vec3 operator/(Vec3 v, float t)
	{
		return Vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
	}

	inline Vec3 operator*(const Vec3 &v, float t)
	{
		return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
	}

	//Unit Vector
	inline void Vec3::make_unit_vector()
	{
		float k = 1.0f / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
		e[0] *= k;
		e[1] *= k;
		e[2] *= k;
	}

	inline Vec3 unit_vector(Vec3 v) 
	{
		return v / v.length();
	}

	inline Vec3 reflect(const Vec3& v, const Vec3& n)
	{
		return v - 2 * dot(v, n)*n;
	}
}