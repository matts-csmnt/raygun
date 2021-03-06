#pragma once
#include "rayg_surface.h"

namespace ray_g {

	//-------------------
	// Constant Medium
	//-------------------

	class Texture;

	class ConstantMedium : public Surface {
	public:
		ConstantMedium() {}
		ConstantMedium(Surface* b, float d, Texture * m);
		virtual bool hit(const Ray& r, float t_min, float t_max, hit_data& data) const;
		virtual void cleanup();
		virtual bool boundingBox(float t0, float t1, AABB& bb) const;
	private:
		float m_density;
		Surface* m_boundary;
		Material* m_phaseFunc;
	};
}