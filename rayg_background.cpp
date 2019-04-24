#include "rayg_background.h"

namespace ray_g {

	//------------------
	// Scene Backgrounds
	//------------------

	Vec3 SkyGrad::getColour(const Ray & r)
	{
		Vec3 unit_dir = unit_vector(r.direction());
		float t = 0.5 * (unit_dir.y() + 1.0);
		return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
	}

	Vec3 ColourBG::getColour(const Ray & r)
	{
		return m_col;
	}

}
