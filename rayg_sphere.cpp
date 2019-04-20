#include "rayg_sphere.h"
#include "common_defines.h"

namespace ray_g {

	//-------------
	// SPHERE
	//-------------

	bool Sphere::hit(const Ray& r, float t_min, float t_max, hit_data& data) const
	{
		Vec3 OC = r.origin() - m_center;
		float a = dot(r.direction(), r.direction());
		float b = dot(OC, r.direction());
		float c = dot(OC, OC) - m_radius * m_radius;
		float discriminant = b * b - a * c;

		if (discriminant > 0)
		{
			float dRoot = sqrt(discriminant);

			float tmp = (-b - dRoot) / a;
			if (tmp < t_max && tmp > t_min)
			{
				//we hit and return info
				data.t = tmp;
				data.p = r.point_at_param(data.t);
				data.normal = (data.p - m_center) / m_radius;
				data.mat = m_material;
				return true;
			}

			//retest
			tmp = (-b + dRoot) / a;
			if (tmp < t_max && tmp > t_min)
			{
				//we hit and return info
				data.t = tmp;
				data.p = r.point_at_param(data.t);
				data.normal = (data.p - m_center) / m_radius;
				data.mat = m_material;
				return true;
			}
		}
		return false;
	}

	void Sphere::cleanup()
	{
		SAFE_DELETE(m_material);
	}

	//-------------
	//MOVING SPHERE
	//-------------

	bool MovingSphere::hit(const Ray & r, float tmin, float tmax, hit_data & data) const
	{
		Vec3 cen = center(r.time());
		Vec3 OC = r.origin() - cen;
		float a = dot(r.direction(), r.direction());
		float b = dot(OC, r.direction());
		float c = dot(OC, OC) - m_radius * m_radius;
		float discriminant = b * b - a * c;

		if (discriminant > 0)
		{
			float dRoot = sqrt(discriminant);

			float tmp = (-b - dRoot) / a;
			if (tmp < tmax && tmp > tmin)
			{
				//we hit and return info
				data.t = tmp;
				data.p = r.point_at_param(data.t);
				data.normal = (data.p - cen) / m_radius;
				data.mat = m_material;
				return true;
			}

			//retest
			tmp = (-b + dRoot) / a;
			if (tmp < tmax && tmp > tmin)
			{
				//we hit and return info
				data.t = tmp;
				data.p = r.point_at_param(data.t);
				data.normal = (data.p - cen) / m_radius;
				data.mat = m_material;
				return true;
			}
		}
		return false;
	}

	Vec3 MovingSphere::center(float time) const
	{
		return m_center0 + ((time - m_time0)/(m_time1 - m_time0)) * (m_center1 - m_center0);
	}

	void MovingSphere::cleanup()
	{
		SAFE_DELETE(m_material);
	}
}
