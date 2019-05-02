#include "rayg_constant_med.h"
#include "rayg_material.h"

#include "common_defines.h"
#include "randf.h"

namespace ray_g {

	//-------------------
	// Constant Medium
	//-------------------

	ConstantMedium::ConstantMedium(Surface* b, float d, Texture * m) : m_boundary(b), m_density(d)
	{
		m_phaseFunc = new Isotropic(m);
	}

	bool ConstantMedium::hit(const Ray & r, float t_min, float t_max, hit_data & data) const
	{
		bool db = (randf() < 0.00001);
		db = false;

		hit_data dt1, dt2;
		if (m_boundary->hit(r, -FLT_MAX, FLT_MAX, dt1))
		{
			if (m_boundary->hit(r, dt1.t + 0.0001, FLT_MAX, dt2))
			{
				if (db)
				{
					std::cerr << "\nt0 t1 " << dt1.t << " " << dt2.t << "\n";
				}

				if (dt1.t < t_min)
					dt1.t = t_min;
				if (dt2.t > t_max)
					dt2.t = t_max;

				if (dt1.t >= dt2.t)
					return false;

				if (dt1.t < 0)
					dt1.t = 0;

				float dist_in_boundary = (dt2.t - dt1.t) * r.direction().length();
				float hit_dist = -(1 / m_density)*log(randf());

				if (hit_dist < dist_in_boundary)
				{
					if (db)
						std::cerr << "hit_distance = " << hit_dist << "\n";
					data.t = dt1.t + hit_dist / r.direction().length();

					if (db)
						std::cerr << "data.t = " << data.t << "\n";
					data.p = r.point_at_param(data.t);

					if (db)
						std::cerr << "data.p = " << data.p << "\n";
					data.normal = Vec3(1, 0, 0);	//arbitrary for now...
					data.mat = m_phaseFunc;
					return true;
				}

			}
		}
		return false;
	}

	void ConstantMedium::cleanup()
	{
		SAFE_DELETE(m_phaseFunc);
	}

	bool ConstantMedium::boundingBox(float t0, float t1, AABB & bb) const
	{
		return m_boundary->boundingBox(t0,t1,bb);
	}

}