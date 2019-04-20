#pragma once
#include "rayg_ray.h"
#include "rayg_aabb.h"

#include <vector>

namespace ray_g {

	class Material;	//fwd ref the mat

	//---------------
	// Hit Data Log
	//---------------

	struct hit_data {
		float t;
		Vec3 p;
		Vec3 normal;
		Material* mat;
	};

	//---------------
	// Surface
	//---------------

	class Surface {
	public:
		//pure virtual hit func
		virtual bool hit(const Ray& r, float t_min, float t_max, hit_data& data) const = 0;
		virtual void cleanup() = 0;
		virtual bool boundingBox(float t0, float t1, AABB& bb) const = 0;
	};

	//---------------
	// Surface List
	//---------------

	class SurfaceList : public Surface {
	public:
		SurfaceList() { m_vList.clear(); }
		virtual bool hit(const Ray& r, float tmin, float tmax, hit_data& rec) const;
		virtual bool boundingBox(float t0, float t1, AABB& bb) const;
		//Vector accessors
		void add(Surface* s) { m_vList.push_back(s); }
		void clear() { m_vList.clear(); }
		int size() const { return m_vList.size(); }
		std::vector<Surface*>& getList() { return m_vList; }
		void cleanup();

	private:
		std::vector<Surface*> m_vList;
		AABB m_box;
	};
}