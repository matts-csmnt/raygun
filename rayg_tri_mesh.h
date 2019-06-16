#pragma once
#include "rayg_triangle.h"
#include "rayg_bvh.h"

namespace ray_g {

	//---------------
	// Triangle based mesh
	//---------------

	class TriangleMesh : public Surface {
	public:
		TriangleMesh() {}
		TriangleMesh(const Vec3& p, Material* m, const char* filepath);
		virtual bool hit(const Ray& r, float t_min, float t_max, hit_data& data) const;
		virtual void cleanup();
		virtual bool boundingBox(float t0, float t1, AABB& bb) const;

		bool loadFromFile(const char* file);
	private:

		Material* m_mat;
		Vec3 m_pos;
		SurfaceList m_triangles;
	};
}