#include "rayg_aabb.h"

namespace ray_g {
	
	//-------------
	// AABB
	//-------------

	//slower method
	/*bool AABB::hit(const Ray& r, float tmin, float tmax) const {
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

	bool AABB::hit(const Ray& r, float tmin, float tmax) const {
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

	AABB surroundingBox(const AABB & b0, const AABB & b1)
	{
		//combine boxes and return a big surrounding box
		Vec3 small(
			ffmin(b0.min().x(), b1.min().x()),
			ffmin(b0.min().y(), b1.min().y()),
			ffmin(b0.min().z(), b1.min().z())
			);
		Vec3 big(
			ffmax(b0.max().x(), b1.max().x()),
			ffmax(b0.max().y(), b1.max().y()),
			ffmax(b0.max().z(), b1.max().z())
		);
		return AABB(small, big);
	}
}
