#pragma once
#include "rayg_ray.h"
#include "common_defines.h"

//ray_g Camera class:
//It's a camera

namespace ray_g {

	class Camera {
	public:
		Camera(const Vec3& pos, const Vec3& lookat, const Vec3& up, int sWidth, int sHeight, float fovy) {
			Vec3 u, v, w;
			m_aspect = (sWidth / sHeight);
			
			//field of view
			float theta = degToRad(fovy);
			float halfHeight = tan(theta / 2);
			float halfWidth = m_aspect * halfHeight;
			
			//position
			m_origin = pos;
			w = unit_vector(pos - lookat);
			u = unit_vector(cross(up, w));
			v = cross(w, u);

			//image bounds
			m_lowerLeftCrnr = m_origin - halfWidth*u - halfHeight*v - w; //Vec3(-halfWidth, -halfHeight, -1.0f);
			m_horizontalUnits = 2*halfWidth*u;
			m_verticalUnits = 2*halfHeight*v;
		};
		Ray getRay(float u, float v) { return Ray(m_origin, m_lowerLeftCrnr + u*m_horizontalUnits + v*m_verticalUnits - m_origin); };

	private:
		Vec3 m_lowerLeftCrnr;
		Vec3 m_horizontalUnits;
		Vec3 m_verticalUnits;
		Vec3 m_origin;
		float m_aspect;
	};
}