#include "rayg_box.h"
#include "rayg_rects.h"

#include "common_defines.h"

namespace ray_g {

	//-------------
	// BOX
	//-------------

	Box::Box(const Vec3& p0, const Vec3& p1, Material* m)
	{
		m_pmin = p0;
		m_pmax = p1;

		//Build box planes
		m_list.clear();
		m_list.add(new XYRect(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), m));
		m_list.add(new FlipNormals(new XYRect(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), m)));
		m_list.add(new XZRect(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), m));
		m_list.add(new FlipNormals(new XZRect(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), m)));
		m_list.add(new YZRect(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), m));
		m_list.add(new FlipNormals(new YZRect(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), m)));
	}

	bool Box::hit(const Ray & r, float t_min, float t_max, hit_data & data) const
	{
		return m_list.hit(r,t_min,t_max,data);
	}

	void Box::cleanup()
	{
		m_list.cleanup();
	}

	bool Box::boundingBox(float t0, float t1, AABB & bb) const
	{
		bb = AABB(m_pmin, m_pmax);
		return true;
	}
}
