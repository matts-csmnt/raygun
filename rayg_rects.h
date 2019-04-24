#pragma once
#include "rayg_surface.h"

namespace ray_g {

	class Material;

	//-------------
	// XY Rectangle
	//-------------

	class XYRect : public Surface {
	public:
		XYRect() {}
		XYRect(float x0, float x1, float y0, float y1, float k, Material* mat) :
			m_x0(x0), m_x1(x1), m_y0(y0), m_y1(y1), m_k(k), m_material(mat){};
		virtual bool hit(const Ray& r, float t_min, float t_max, hit_data& data) const;
		virtual bool boundingBox(float t0, float t1, AABB& bb) const;
		virtual void cleanup();

		float m_x0, m_x1, m_y0, m_y1, m_k;
		Material* m_material;
	};

	//-------------
	// YZ Rectangle
	//-------------

	class YZRect : public Surface {
	public:
		YZRect() {}
		YZRect(float y0, float y1, float z0, float z1, float k, Material* mat) :
			m_z0(z0), m_z1(z1), m_y0(y0), m_y1(y1), m_k(k), m_material(mat) {};
		virtual bool hit(const Ray& r, float t_min, float t_max, hit_data& data) const;
		virtual bool boundingBox(float t0, float t1, AABB& bb) const;
		virtual void cleanup();

		float m_z0, m_z1, m_y0, m_y1, m_k;
		Material* m_material;
	};

	//-------------
	// XZ Rectangle
	//-------------

	class XZRect : public Surface {
	public:
		XZRect() {}
		XZRect(float x0, float x1, float z0, float z1, float k, Material* mat) :
			m_x0(x0), m_x1(x1), m_z0(z0), m_z1(z1), m_k(k), m_material(mat) {};
		virtual bool hit(const Ray& r, float t_min, float t_max, hit_data& data) const;
		virtual bool boundingBox(float t0, float t1, AABB& bb) const;
		virtual void cleanup();

		float m_x0, m_x1, m_z0, m_z1, m_k;
		Material* m_material;
	};
}