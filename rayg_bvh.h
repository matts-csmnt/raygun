#pragma once
#include "rayg_surface.h"

namespace ray_g {

	//-------------------------
	// Axis Splitting compares
	//-------------------------

	int box_x_cmp(const void* a, const void* b);
	int box_y_cmp(const void* a, const void* b);
	int box_z_cmp(const void* a, const void* b);

	//--------------------------
	// Bounding Volume Hierarchy
	//--------------------------

	class BVHNode : public Surface {
	public:
		BVHNode() {}
		BVHNode(Surface** s, int n, float time0, float time1);
		~BVHNode();
		virtual bool hit(const Ray& r, float tmin, float tmax, hit_data& data) const;
		virtual bool boundingBox(float t0, float t1, AABB& bb) const;
		virtual void cleanup();

		Surface* m_left;
		Surface* m_right;
		AABB m_box;
	};
}