#pragma once
#include <random>
#include <time.h>
#include "rayg_vec3.h"

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<> dis(0, 1);

using namespace ray_g;

const float randf()
{
	return dis(gen);
}

//random vector in a unit sphere
Vec3 random_in_unit_sphere()
{
	Vec3 p;
	do {
		p = 2.0 * Vec3(randf(), randf(), randf()) - Vec3(1.0, 1.0, 1.0);
	} while (p.squared_length() >= 1.0);
	return p;
}