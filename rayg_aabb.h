#pragma once
#include "rayg_vec3.h"
#include "rayg_ray.h"

//ray_g Axis Aligned Bounding Box class:

namespace ray_g {

	//fast min/max
	inline float ffmin(float a, float b) { return a < b ? a : b; }
	inline float ffmax(float a, float b) { return a > b ? a : b; }

	class AABB {
	public:
		AABB() {}
		AABB(const Vec3& a, const Vec3& b) : m_min(a), m_max(b) {}

		Vec3 min() const { return m_min; }
		Vec3 max() const { return m_max; }

		//slower method
		/*bool hit(const Ray& r, float tmin, float tmax) const {
			for (int a(0); a < 3; a++)
			{
				float t0 = ffmin(
					(m_min[a] - r.origin()[a]) / r.direction()[a],
					(m_max[a] - r.origin()[a]) / r.direction()[a]
				);
				float t1 = ffmax(
					(m_min[a] - r.origin()[a]) / r.direction()[a],
					(m_max[a] - r.origin()[a]) / r.direction()[a]
				);

				tmin = ffmax(t0, tmin);
				tmax = ffmin(t1, tmax);

				if (tmax <= tmin) {
					return false;
				}

				return true;
			}*/

		bool hit(const Ray& r, float tmin, float tmax) const {
			for (int a(0); a < 3; a++)
			{
				float invD = 1.0f / r.direction()[a];
				float t0 = (m_min[a] - r.origin()[a]) * invD;
				float t1 = (m_max[a] - r.origin()[a]) * invD;
				if (invD < 0.0f) {
					std::swap(t0, t1);
				}
				tmin = t0 > tmin ? t0 : tmin;
				tmax = t1 < tmax ? t0 : tmax;

				if (tmax <= tmin) {
					return false;
				}

				return true;
			}
		};

	private:
		Vec3 m_min;
		Vec3 m_max;
	};
}