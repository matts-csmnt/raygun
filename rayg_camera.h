#pragma once
#include "rayg_ray.h"
#include "common_defines.h"
#include "randf.h"

//ray_g Camera class:
//It's a camera

namespace ray_g {

	//disk gen
	Vec3 random_in_unit_disk() {
		Vec3 p;
		do {
			p = 2.0*Vec3(randf(), randf(), 0) - Vec3(1, 1, 0);
		} while (dot(p, p) >= 1.0);
		return p;
	}

	class Camera {
	public:
		Camera(const Vec3& pos, const Vec3& lookat, const Vec3& up, int sWidth, int sHeight, float fovy, float aperture, float focusDist) {
			m_lensRad = aperture / 2;
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
			m_lowerLeftCrnr = m_origin - halfWidth*focusDist*u - halfHeight*focusDist*v - focusDist*w;
			m_horizontalUnits = 2*halfWidth*focusDist*u;
			m_verticalUnits = 2*halfHeight*focusDist*v;
		};
		Ray getRay(float s, float t) { 
			Vec3 rd = m_lensRad*random_in_unit_disk();
			Vec3 off = u * rd.x() + v * rd.y();
			return Ray(m_origin + off, m_lowerLeftCrnr + s*m_horizontalUnits + t*m_verticalUnits - m_origin - off); 
		};

	private:
		Vec3 m_lowerLeftCrnr;
		Vec3 m_horizontalUnits;
		Vec3 m_verticalUnits;
		Vec3 m_origin;
		Vec3 u, v, w;
		float m_aspect;
		float m_lensRad;
	};
}