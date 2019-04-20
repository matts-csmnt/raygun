#include "rayg_surface.h"
#include "common_defines.h"

namespace ray_g {

	//----------------
	// Surface List
	//----------------

	void SurfaceList::cleanup() {
		for (Surface* s : m_vList) {
			s->cleanup();
			SAFE_DELETE(s);
		}
	}

	bool SurfaceList::hit(const Ray& r, float t_min, float t_max, hit_data& rec) const {
		hit_data temp_rec;
		bool hit_anything = false;
		double closest_so_far = t_max;
		for (Surface* s : m_vList) {
			if (s->hit(r, t_min, closest_so_far, temp_rec)) {
				hit_anything = true;
				closest_so_far = temp_rec.t;
				rec = temp_rec;
			}
		}
		return hit_anything;
	}
}