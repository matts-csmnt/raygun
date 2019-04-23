#pragma once
#include "rayg_surface.h"
#include "rayg_texture.h"
#include "rayg_ray.h"

#include "common_defines.h"

namespace ray_g {
	
	//-------------
	// Base Class
	//-------------

	class Material {
	public:
		virtual ~Material() {};
		virtual bool scatter(const Ray& in, const hit_data& data, Vec3& attenuation, Ray& scattered) const = 0;
		virtual Vec3 emittted(float u, float v, const Vec3& p) const;
	};

	//---------------------
	// Lambertian (Diffuse)
	//---------------------

	class Lambertian : public Material {
	public:
		Lambertian(Texture* a) : m_albedo(a) {}
		~Lambertian() { SAFE_DELETE(m_albedo); }
		bool scatter(const Ray& in, const hit_data& data, Vec3& attenuation, Ray& scattered) const;
		Texture* m_albedo;
	};

	//-------------
	// Metallic
	//-------------

	class Metal : public Material {
	public:
		Metal(Texture* a, float f) : m_albedo(a), m_fuzz(f) {}
		~Metal() { SAFE_DELETE(m_albedo); }
		bool scatter(const Ray& in, const hit_data& data, Vec3& attenuation, Ray& scattered) const;
		float m_fuzz;
		Texture* m_albedo;
	};

	//-------------
	// Dielectrics
	//-------------

	class Dielectric : public Material {
	public:
		~Dielectric() {}
		Dielectric(float ri) : m_refIdx(ri) {}
		bool scatter(const Ray& in, const hit_data& data, Vec3& attenuation, Ray& scattered) const;
		float m_refIdx;
	};

	//-------------
	//Diffuse Light
	//-------------

	class DiffuseLight : public Material {
	public:
		DiffuseLight(Texture* a) : m_emit(a) {}
		~DiffuseLight();
		virtual bool scatter(const Ray& in, const hit_data& data, Vec3& attenuation, Ray& scattered) const { return false; }
		virtual Vec3 emittted(float u, float v, const Vec3& p) const;
		Texture* m_emit;
	};
}