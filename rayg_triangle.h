#pragma once
#include "rayg_surface.h"

namespace ray_g {

	//---------------
	// Triangle
	//---------------

	class Triangle : public Surface {
	public:
		Triangle() {}
		Triangle(const Vec3& p0, const Vec3& p1, const Vec3& p2, Material* m);
		virtual bool hit(const Ray& r, float t_min, float t_max, hit_data& data) const;
		virtual void cleanup();
		virtual bool boundingBox(float t0, float t1, AABB& bb) const;

		void setP0(const Vec3& v);
		void setP1(const Vec3& v);
		void setP2(const Vec3& v);

	private:
		Vec3 m_p0, m_p1, m_p2;
		Material* m_material;
	};
}