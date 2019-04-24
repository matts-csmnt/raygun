#pragma once
#include "rayg_ray.h"

namespace ray_g {

	//------------------
	// Scene Background
	//------------------

	class Background {
	public:
		virtual Vec3 getColour(const Ray& r) = 0;
	};

	//------------------
	// Sky Gradient 
	//------------------

	class SkyGrad : public Background {
	public:
		virtual Vec3 getColour(const Ray& r);
	};

	//------------------
	// Block Colour
	//------------------

	class ColourBG : public Background {
	public:
		ColourBG() : m_col(Vec3(0, 0, 0)) {}
		ColourBG(const Vec3& col) : m_col(col) {}
		virtual Vec3 getColour(const Ray& r);
	private:
		Vec3 m_col;
	};
}