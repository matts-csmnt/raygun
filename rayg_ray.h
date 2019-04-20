#pragma once
#include "rayg_vec3.h"

//ray_g ray class:
//3D Ray from an origin in a direction

namespace ray_g {

	class Ray {
	public:
		Ray() {};
		Ray(const Vec3& a, const Vec3& b, float t = 0.0) { A = a; B = b; m_time = t; };

		Vec3 origin() const { return A; };
		Vec3 direction() const { return B; };
		float time() const { return m_time; }
		Vec3 point_at_param(float t) const { return A + t*B; };

		Vec3 A;	//Origin
		Vec3 B;	//Direction
		float m_time;
	};
}