#pragma once
#include "rayg_ray.h"

//ray_g Surface class:
//A Hittable object & the Hit record data

//ray_g SurfaceList class:
//A List of Hittable objects & the Hit record data

namespace ray_g {

	class Material;	//fwd ref the mat

	struct hit_data {
		float t;
		Vec3 p;
		Vec3 normal;
		Material* mat;
	};

	class Surface {
	public:
		//pure virtual hit func
		virtual bool hit(const Ray& r, float t_min, float t_max, hit_data& data) const = 0;
	};

	//--
	class SurfaceList : public Surface {
	public:
		SurfaceList() {}
		SurfaceList(Surface **l, int n) { m_list = l; m_listSize = n; }
		virtual bool hit(const Ray& r, float tmin, float tmax, hit_data& rec) const;
		Surface **m_list;
		int m_listSize;
	};

	bool SurfaceList::hit(const Ray& r, float t_min, float t_max, hit_data& rec) const {
		hit_data temp_rec;
		bool hit_anything = false;
		double closest_so_far = t_max;
		for (int i = 0; i < m_listSize; i++) {
			if (m_list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
				hit_anything = true;
				closest_so_far = temp_rec.t;
				rec = temp_rec;
			}
		}
		return hit_anything;
	}
}