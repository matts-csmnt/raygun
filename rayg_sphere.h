#pragma once
#include "rayg_surface.h"

//ray_g Sphere class:
//A Hittable Sphere object

namespace ray_g {

	class Sphere : public Surface {
	public:
		Sphere() {};
		Sphere(const Vec3& center, float radius, Material* mat) : m_center(center), m_radius(radius), m_material(mat) {};
		virtual bool hit(const Ray& r, float t_min, float t_max, hit_data& data) const;

		const Vec3& getCenter() { return m_center; };
		const float getRadius() { return m_radius; };

		void freeMat() { if (m_material) { delete m_material; m_material = nullptr; } }

	private:
		Vec3 m_center;
		float m_radius;
		Material* m_material = nullptr;
	};

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
}