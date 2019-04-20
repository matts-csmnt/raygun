#pragma once
#include "rayg_surface.h"

//ray_g Sphere class:
//A Hittable Sphere object

namespace ray_g {

	//-------------
	// SPHERE
	//-------------

	class Sphere : public Surface {
	public:
		Sphere() {};
		Sphere(const Vec3& center, float radius, Material* mat) : m_center(center), m_radius(radius), m_material(mat) {};
		virtual bool hit(const Ray& r, float t_min, float t_max, hit_data& data) const;
		virtual void cleanup();
		virtual bool boundingBox(float t0, float t1, AABB& bb) const;

		const Vec3& getCenter() { return m_center; };
		const float getRadius() { return m_radius; };

		void freeMat() { if (m_material) { delete m_material; m_material = nullptr; } }

	private:
		Vec3 m_center;
		float m_radius;
		Material* m_material = nullptr;
	};

	//-------------
	//MOVING SPHERE
	//-------------

	class MovingSphere : public Surface {
	public:
		MovingSphere() {}
		MovingSphere(const Vec3& cen0, const Vec3& cen1, float t0, float t1, float r, Material* mat) :
			m_center0(cen0), m_center1(cen1), m_time0(t0), m_time1(t1), m_radius(r), m_material(mat) {};
		virtual bool hit(const Ray& r, float tmin, float tmax, hit_data& data) const;
		Vec3 center(float time) const;
		virtual void cleanup();
		virtual bool boundingBox(float t0, float t1, AABB& bb) const;

		Vec3 m_center0, m_center1;
		float m_time0, m_time1;
		float m_radius;
		Material* m_material;
	};
}