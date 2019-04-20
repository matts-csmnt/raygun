#include "rayg_camera.h"

#include "common_defines.h"
#include "randf.h"

namespace ray_g {

	//-------------
	// Disk Gen
	//-------------

	Vec3 random_in_unit_disk() {
		Vec3 p;
		do {
			p = 2.0*Vec3(randf(), randf(), 0) - Vec3(1, 1, 0);
		} while (dot(p, p) >= 1.0);
		return p;
	}

	//-------------
	// Camera
	//-------------

	Camera::Camera(const Vec3& pos, const Vec3& lookat, const Vec3& up, int sWidth, int sHeight, float fovy, float aperture, float focusDist,
		float t0, float t1) {
		m_time0 = t0;
		m_time1 = t1;

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
		m_horizontalUnits = 2 * halfWidth*focusDist*u;
		m_verticalUnits = 2 * halfHeight*focusDist*v;
	};

	Ray Camera::getRay(float s, float t) {
		Vec3 rd = m_lensRad*random_in_unit_disk();
		Vec3 off = u * rd.x() + v * rd.y();
		float time = m_time0 + randf() * (m_time1 - m_time0);
		return Ray(m_origin + off, m_lowerLeftCrnr + s*m_horizontalUnits + t*m_verticalUnits - m_origin - off, time);
	};
}