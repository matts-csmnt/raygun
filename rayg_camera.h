#pragma once
#include "rayg_ray.h"

//ray_g Camera class:
//It's a camera

namespace ray_g {

	class Camera {
	public:
		Camera(int sWidth, int sHeight) {
			//image bounds
			m_lowerLeftCrnr = Vec3(-(float)sWidth / 100, -(float)sHeight / 100, -1.0f);
			m_horizontalUnits = Vec3(((float)sWidth / 100) * 2, 0.0f, 0.0f);
			m_verticalUnits = Vec3(0.0f, ((float)sHeight / 100) * 2, 0.0f);
			m_origin = Vec3(0.0f, 0.0f, 0.0f);
		};
		Ray getRay(float u, float v) { return Ray(m_origin, m_lowerLeftCrnr + u*m_horizontalUnits + v*m_verticalUnits - m_origin); };

	private:
		Vec3 m_lowerLeftCrnr;
		Vec3 m_horizontalUnits;
		Vec3 m_verticalUnits;
		Vec3 m_origin;
	};
}