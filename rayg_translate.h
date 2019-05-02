#pragma once
#include "rayg_surface.h"

namespace ray_g {

	//-------------------
	// Translation Object
	//-------------------

	class Texture;

	class Translate : public Surface {
	public:
		Translate() {}
		Translate(Surface* b, const Vec3& offest);
		virtual bool hit(const Ray& r, float t_min, float t_max, hit_data& data) const;
		virtual void cleanup();
		virtual bool boundingBox(float t0, float t1, AABB& bb) const;
	private:
		Surface* m_object;
		Vec3 m_offset;
	};
}