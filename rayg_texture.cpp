#include "rayg_texture.h"
#include "rayg_perlin.h"

#include "common_defines.h"

namespace ray_g {

	//--------------
	//CHECKER TEXTURE
	//--------------

	CheckerTexture::~CheckerTexture()
	{
		SAFE_DELETE(m_odd);
		SAFE_DELETE(m_even);
	}

	Vec3 CheckerTexture::value(float u, float v, const Vec3 & p) const
	{
		float sines = sin(10 * p.x())*sin(10 * p.y())*sin(10 * p.z());
		if (sines < 0)
			return m_odd->value(u, v, p);
		else
			return m_even->value(u, v, p);
	}

	//--------------
	// NOISE TEXTURE
	//--------------

	Vec3 NoiseTexture::value(float u, float v, const Vec3 & p) const
	{
		switch (m_mode)
		{
		case 0:
		default:	//regular noise
			return Vec3(1) * 0.5 * (1+m_noise->turbulence(m_scale*p));
			break;
		case 1:		//turbulence
			return Vec3(1) * m_noise->turbulence(m_scale*p);
			break;
		case 2:		//marble-like
			return Vec3(1) * 0.5 * (1 + sin(m_scale*p.z() + 10*m_noise->turbulence(p)));
			break;
		}
	}
}
