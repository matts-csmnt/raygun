#pragma once
#include "rayg_vec3.h"
#include "rayg_ray.h"

//ray_g Axis Aligned Bounding Box class:

namespace ray_g {

	//-------------
	//fast min/max
	//-------------

	inline float ffmin(float a, float b) { return a < b ? a : b; }
	inline float ffmax(float a, float b) { return a > b ? a : b; }

	//-------------
	// AABB
	//-------------

	class AABB {
	public:
		AABB() {}
		AABB(const Vec3& a, const Vec3& b) : m_min(a), m_max(b) {}

		Vec3 min() const { return m_min; }
		Vec3 max() const { return m_max; }

		bool hit(const Ray& r, float tmin, float tmax) const;

	private:
		Vec3 m_min;
		Vec3 m_max;
	};

	AABB surroundingBox(const AABB& b0, const AABB& b1);
}