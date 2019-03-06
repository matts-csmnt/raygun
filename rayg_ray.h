#pragma once
#include "rayg_vec3.h"

//ray_g ray class:
//3D Ray from an origin in a direction

namespace ray_g {

	class ray {
	public:
		ray() {};
		ray(const vec3& a, const vec3& b) { A = a; B = b; };

		vec3 origin() const { return A; };
		vec3 direction() const { return B; };
		vec3 point_at_param(float t) const { return A + B; };

		vec3 A;	//Origin
		vec3 B;	//Direction
	};
}