#include "rayg_triangle.h"
#include "common_defines.h"

namespace ray_g {
	
	//---------------
	// Triangle
	//---------------

	Triangle::Triangle(const Vec3 & p0, const Vec3 & p1, const Vec3 & p2, Material * m)
	{
		m_p0 = p0;
		m_p1 = p1;
		m_p2 = p2;
		m_material = m;
	}

	bool Triangle::hit(const Ray & r, float t_min, float t_max, hit_data & data) const
	{
		//Möller–Trumbore intersection algorithm
		const float EPSILON = 0.0000001;

		float det, inv_det, u, v;
		Vec3 edge1 = m_p1 - m_p0;
		Vec3 edge2 = m_p2 - m_p0;
		Vec3 pvec = cross(r.direction(), edge2);
		det = dot(edge1, pvec);

		Vec3 tvec = r.origin() - m_p0;
		inv_det = 1.0 / det;

		Vec3 qvec = cross(tvec, edge1);

		if (det > EPSILON)
		{
			u = dot(tvec, pvec);
			if (u < 0.0 || u > det)
				return 0;

			/* calculate V parameter and test bounds */
			v = dot(r.direction(), qvec);
			if (v < 0.0 || u + v > det)
				return 0;

		}
		else if (det < -EPSILON)
		{
			/* calculate U parameter and test bounds */
			u = dot(tvec, pvec);
			if (u > 0.0 || u < det)
				return 0;

			/* calculate V parameter and test bounds */
			v = dot(r.direction(), qvec);
			if (v > 0.0 || u + v < det)
				return 0;
		}
		else return 0;  /* ray is parallell to the plane of the triangle */

		float t = dot(edge2, qvec) * inv_det;
		u *= inv_det;
		v *= inv_det;

		//HIT
		data.mat = m_material;
		data.t = t;
		data.p = r.point_at_param(t);
		data.u = u;
		data.v = v;
		data.normal = cross(edge1, edge2);
		return true;
	}

	void Triangle::cleanup()
	{
		SAFE_DELETE(m_material);
	}

	bool Triangle::boundingBox(float t0, float t1, AABB & bb) const
	{
		Vec3 min, max;
		float xmin = ffmin(ffmin(m_p0.x(), m_p1.x()), m_p2.x());
		float ymin = ffmin(ffmin(m_p0.y(), m_p1.y()), m_p2.y());
		float zmin = ffmin(ffmin(m_p0.z(), m_p1.z()), m_p2.z());

		float xmax = ffmax(ffmax(m_p0.x(), m_p1.x()), m_p2.x());
		float ymax = ffmax(ffmax(m_p0.y(), m_p1.y()), m_p2.y());
		float zmax = ffmax(ffmax(m_p0.z(), m_p1.z()), m_p2.z());

		bb = AABB(Vec3(xmin,ymin,zmin), Vec3(xmax,ymax,zmax));
		return true;
	}
}