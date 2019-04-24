#pragma once
#include "rayg_surface.h"

namespace ray_g {

	//-------------
	// BOX
	//-------------

	class Box : public Surface {
	public:
		Box() {}
		Box(const Vec3& p0, const Vec3& p1, Material* m);
		virtual bool hit(const Ray& r, float t_min, float t_max, hit_data& data) const;
		virtual void cleanup();
		virtual bool boundingBox(float t0, float t1, AABB& bb) const;

		SurfaceList m_list;
		Vec3 m_pmin, m_pmax;
	};
}
