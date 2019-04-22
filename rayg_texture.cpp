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

	//--------------
	// IMAGE TEXTURE
	//--------------

	ImageTexture::~ImageTexture()
	{
		SAFE_DELETE(m_data);
	}

	Vec3 ImageTexture::value(float u, float v, const Vec3 & p) const
	{
		int i = (u) * m_nx;
		int j = (1-v)*m_ny - 0.001;

		if (i < 0) i = 0;
		if (j < 0) j = 0;
		if (i > m_nx - 1) i = m_nx - 1;
		if (j > m_ny - 1) j = m_ny - 1;

		float r = int(m_data[3 * i + 3 * m_nx*j]) / 255.0;
		float g = int(m_data[3 * i + 3 * m_nx*j+1]) / 255.0;
		float b = int(m_data[3 * i + 3 * m_nx*j+2]) / 255.0;

		return Vec3(r, g, b);
	}
}
