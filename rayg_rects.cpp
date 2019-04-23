#include "rayg_rects.h"

#include "common_defines.h"

namespace ray_g {
	
	//-------------
	// XY Rectangle
	//-------------

	bool XYRect::hit(const Ray & r, float t_min, float t_max, hit_data & data) const
	{
		float t = (m_k-r.origin().z()) / r.direction().z();
		if (t < t_min || t > t_max)
			return false;

		float x = r.origin().x() + t * r.direction().x();
		float y = r.origin().y() + t * r.direction().y();
		if (x < m_x0 || x > m_x1 || y < m_y0 || y > m_y1)
			return false;

		data.u = (x - m_x0) / (m_x1 - m_x0);
		data.v = (y - m_y0) / (m_y1 - m_y0);
		data.t = t;
		data.mat = m_material;
		data.p = r.point_at_param(t);
		data.normal = Vec3(0, 0, 1);
		return true;
	}
	
	bool XYRect::boundingBox(float t0, float t1, AABB & bb) const
	{
		bb = AABB(Vec3(m_x0, m_y0, m_k-0.0001), Vec3(m_x1, m_y1, m_k+0.0001));
		return true;
	}

	void XYRect::cleanup()
	{
		SAFE_DELETE(m_material);
	}

	//-------------
	// YZ Rectangle
	//-------------

	bool YZRect::hit(const Ray & r, float t_min, float t_max, hit_data & data) const
	{
		float t = (m_k - r.origin().x()) / r.direction().x();
		if (t < t_min || t > t_max)
			return false;

		float z = r.origin().z() + t * r.direction().z();
		float y = r.origin().y() + t * r.direction().y();
		if (z < m_z0 || z > m_z1 || y < m_y0 || y > m_y1)
			return false;

		data.u = (y - m_y0) / (m_y1 - m_y0); 
		data.v = (z - m_z0) / (m_z1 - m_z0);
		data.t = t;
		data.mat = m_material;
		data.p = r.point_at_param(t);
		data.normal = Vec3(1, 0, 0);
		return true;
	}

	bool YZRect::boundingBox(float t0, float t1, AABB & bb) const
	{
		bb = AABB(Vec3(m_k - 0.0001, m_y0, m_z0), Vec3(m_k + 0.0001, m_y1, m_z1));
		return true;
	}

	void YZRect::cleanup()
	{
		SAFE_DELETE(m_material);
	}

	//-------------
	// XZ Rectangle
	//-------------

	bool XZRect::hit(const Ray & r, float t_min, float t_max, hit_data & data) const
	{
		float t = (m_k - r.origin().y()) / r.direction().y();
		if (t < t_min || t > t_max)
			return false;

		float x = r.origin().x() + t * r.direction().x();
		float z = r.origin().z() + t * r.direction().z();
		if (x < m_x0 || x > m_x1 || z < m_z0 || z > m_z1)
			return false;

		data.u = (x - m_x0) / (m_x1 - m_x0);
		data.v = (z - m_z0) / (m_z1 - m_z0);
		data.t = t;
		data.mat = m_material;
		data.p = r.point_at_param(t);
		data.normal = Vec3(0, 1, 0);
		return true;
	}

	bool XZRect::boundingBox(float t0, float t1, AABB & bb) const
	{
		bb = AABB(Vec3(m_x0, m_k - 0.0001, m_z0), Vec3(m_x1, m_k + 0.0001, m_z1));
		return true;
	}

	void XZRect::cleanup()
	{
		SAFE_DELETE(m_material);
	}
}
