#pragma once
#include "rayg_vec3.h"

namespace ray_g {

	class Perlin;	//fwd ref noise

	//--------------
	//TEXTURE CLASS
	//--------------

	class Texture {
	public:
		virtual Vec3 value(float u, float v, const Vec3& p) const = 0;
	};

	//--------------
	//CONST TEXTURE
	//--------------

	class ConstantTexture : public Texture {
	public:
		ConstantTexture() {}
		ConstantTexture(const Vec3& c) : m_colour(c) {}
		virtual Vec3 value(float u, float v, const Vec3& p) const { return m_colour; };
		Vec3 m_colour;
	};

	//--------------
	//CHECKER TEXTURE
	//--------------

	class CheckerTexture : public Texture {
	public:
		CheckerTexture() {}
		~CheckerTexture();
		CheckerTexture(Texture* t0, Texture* t1) : m_odd(t1), m_even(t0) {}
		virtual Vec3 value(float u, float v, const Vec3& p) const;
		Texture* m_odd;
		Texture* m_even;
	};

	//--------------
	// NOISE TEXTURE
	//--------------

	class NoiseTexture : public Texture {
	public:
		NoiseTexture() {}
		NoiseTexture(float sc, int mode = 0) : m_scale(sc), m_mode(mode) {}
		virtual Vec3 value(float u, float v, const Vec3& p) const;
		Perlin* m_noise;
		float m_scale;
		int m_mode;
	};

	//--------------
	// IMAGE TEXTURE
	//--------------

	class ImageTexture : public Texture {
	public:
		ImageTexture() {}
		~ImageTexture();
		ImageTexture(unsigned char* data, int A, int B) : m_data(data), m_nx(A), m_ny(B) {}
		virtual Vec3 value(float u, float v, const Vec3& p) const;
		unsigned char* m_data;
		int m_nx, m_ny;
	};
}