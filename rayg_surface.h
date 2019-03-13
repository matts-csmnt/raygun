#pragma once
#include "rayg_ray.h"
#include <vector>

//ray_g Surface class:
//A Hittable object & the Hit record data

//ray_g SurfaceList class:
//A List of Hittable objects & the Hit record data

namespace ray_g {

	struct hit_data {
		float t;
		Vec3 p;
		Vec3 normal;
	};

	class Surface {
	public:
		//pure virtual hit func
		virtual bool hit(const Ray& r, float t_min, float t_max, hit_data& data) const = 0;
	};

	//--

	class SurfaceList : public Surface
	{
	public:
		SurfaceList() {};
		~SurfaceList();

		virtual bool hit(const Ray& r, float t_min, float t_max, hit_data& data) const;

		void append(Surface* s);
		void clear() { free();  m_vList.clear(); };
		const int size() const { return m_vList.size(); };

	private:
		std::vector<Surface*> m_vList;

		void free();
	};

	SurfaceList::~SurfaceList()
	{
		free();
	}

	bool SurfaceList::hit(const Ray& r, float t_min, float t_max, hit_data& data) const
	{
		hit_data tempData;
		bool hitSurface = false;
		double closest = t_max;

		//Check for hits and output
		for (int i(0); i < m_vList.size(); ++i)
		{
			if (m_vList[i]->hit(r, t_min, closest, tempData))
			{
				hitSurface = true;
				closest = tempData.t;
				data = tempData;
			}
		}
		return hitSurface;
	}

	void SurfaceList::append(Surface* s)
	{
		m_vList.push_back(s);
	}

	void SurfaceList::free()
	{
		if (m_vList.size() > 0)
			for (Surface* s : m_vList)
				if (s)
				{
					delete s;
					s = nullptr;
				}
	}
}