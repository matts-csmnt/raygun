#pragma once
#include "rayg_ray.h"

//ray_g Camera class:
//It's a camera

namespace ray_g {

	//-------------
	// Camera
	//-------------

	class Camera {
	public:
		Camera(const Vec3& pos, const Vec3& lookat, const Vec3& up, int sWidth, int sHeight, float fovy, float aperture, float focusDist,
			float t0, float t1);
		Ray getRay(float s, float t);

		float getTime0() const { return m_time0; };
		float getTime1() const { return m_time1; };

	private:
		Vec3 m_lowerLeftCrnr;
		Vec3 m_horizontalUnits;
		Vec3 m_verticalUnits;
		Vec3 m_origin;
		Vec3 u, v, w;
		float m_aspect;
		float m_lensRad;
		float m_time0, m_time1;	//exposure times
	};
}