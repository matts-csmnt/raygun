#pragma once
#include "rayg_ray.h"
#include <vector>
#include "common_defines.h"

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
		virtual void cleanup() = 0;
	};

	//--
	class SurfaceList : public Surface {
	public:
		SurfaceList() { m_vList.clear(); }
		virtual bool hit(const Ray& r, float tmin, float tmax, hit_data& rec) const;

		//Vector accessors
		void add(Surface* s) { m_vList.push_back(s); }
		void clear() { m_vList.clear(); }
		int size() const { m_vList.size(); }

		void cleanup() {
			for (Surface* s : m_vList) {
				s->cleanup();
				SAFE_DELETE(s);
			} 
		}

	private:
		std::vector<Surface*> m_vList;
	};

	bool SurfaceList::hit(const Ray& r, float t_min, float t_max, hit_data& rec) const {
		hit_data temp_rec;
		bool hit_anything = false;
		double closest_so_far = t_max;
		for (Surface* s:  m_vList) {
			if (s->hit(r, t_min, closest_so_far, temp_rec)) {
				hit_anything = true;
				closest_so_far = temp_rec.t;
				rec = temp_rec;
			}
		}
		return hit_anything;
	}
}