#pragma once
#include "rayg_surface.h"
#include "rayg_ray.h"

namespace ray_g {
	
	//-------------
	// Base Class
	//-------------

	class Material {
	public:
		virtual bool scatter(const Ray& in, const hit_data& data, Vec3& attenuation, Ray& scattered) const = 0;
	};

	//---------------------
	// Lambertian (Diffuse)
	//---------------------

	class Lambertian : public Material {
	public:
		Lambertian(const Vec3& a) : m_albedo(a) {}
		bool scatter(const Ray& in, const hit_data& data, Vec3& attenuation, Ray& scattered) const;
		Vec3 m_albedo;
	};

	//-------------
	// Metallic
	//-------------

	class Metal : public Material {
	public:
		Metal(const Vec3& a, float f) : m_albedo(a), m_fuzz(f) {}
		bool scatter(const Ray& in, const hit_data& data, Vec3& attenuation, Ray& scattered) const;
		Vec3 m_albedo;
		float m_fuzz;
	};

	//-------------
	// Dielectrics
	//-------------

	class Dielectric : public Material {
	public:
		Dielectric(float ri) : m_refIdx(ri) {}
		bool scatter(const Ray& in, const hit_data& data, Vec3& attenuation, Ray& scattered) const;
		float m_refIdx;
	};
}