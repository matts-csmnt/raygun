#include "rayg_translate.h"

namespace ray_g {

	//-------------------
	// Translation Object
	//-------------------

	Translate::Translate(Surface * b, const Vec3 & offset) : m_object(b), m_offset(offset)
	{
	}

	bool Translate::hit(const Ray & r, float t_min, float t_max, hit_data & data) const
	{
		Ray moved(r.origin() - m_offset, r.direction(), r.time());
		if (m_object->hit(moved, t_min, t_max, data))
		{
			data.p += m_offset;
			return true;
		}
		return false;
	}

	void Translate::cleanup()
	{
	}

	bool Translate::boundingBox(float t0, float t1, AABB & bb) const
	{
		if (m_object->boundingBox(t0, t1, bb))
		{
			bb = AABB(bb.min() + m_offset, bb.max() + m_offset);
			return true;
		}
		return false;
	}
}