#pragma once
#include "rayg_ray.h"
#include "rayg_surface.h"
#include "randf.h"
//ray_g Material class:

namespace ray_g {
	class Material {
	public:
		virtual bool scatter(const Ray& in, const hit_data& data, Vec3& attenuation, Ray& scattered) const = 0;
	};

	//lambertian material
	class Lambertian : public Material {
	public:
		Lambertian(const Vec3& a) : m_albedo(a) {}
		bool scatter(const Ray& in, const hit_data& data, Vec3& attenuation, Ray& scattered) const override {
			Vec3 target = data.p + data.normal + random_in_unit_sphere();
			scattered = Ray(data.p, target - data.p);
			attenuation = m_albedo;
			return true;
		}
		Vec3 m_albedo;
	};

	//metal material
	class Metal : public Material {
	public:
		Metal(const Vec3& a, float f) : m_albedo(a), m_fuzz(f) {}
		bool scatter(const Ray& in, const hit_data& data, Vec3& attenuation, Ray& scattered) const override {
			Vec3 reflected = reflect(unit_vector(in.direction()), data.normal);
			scattered = Ray(data.p, reflected + m_fuzz * random_in_unit_sphere());
			attenuation = m_albedo;
			return (dot(scattered.direction(), data.normal) > 0);
		}
		Vec3 m_albedo;
		float m_fuzz;
	};

	//Dialectric materials
	bool refract(const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refracted)
	{
		Vec3 uv = unit_vector(v);
		float dt = dot(uv, n);
		float discriminant = 1.0 - ni_over_nt * ni_over_nt*(1 - dt * dt);

		if (discriminant > 0)
		{
			//refract!
			refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
			return true;
		}
		else
			return false;
	}

	float schlick(float cos, float refIdx)
	{
		float r0 = (1 - refIdx) / (1 + refIdx);
		r0 *= r0;
		return r0 + (1 - r0)*pow((1 - cos), 5);
	}

	class Dialectric : public Material {
	public:
		Dialectric(float ri) : m_refIdx(ri) {}
		bool scatter(const Ray& in, const hit_data& data, Vec3& attenuation, Ray& scattered) const override {
			Vec3 outwardNormal;
			Vec3 reflected = reflect(in.direction(), data.normal);
			float niOverNt;
			attenuation = Vec3(1, 1, 1);
			Vec3 refracted;
			float reflectProb;
			float cosine;

			if (dot(in.direction(), data.normal) > 0) {
				outwardNormal = -data.normal;
				niOverNt = m_refIdx;
				cosine = m_refIdx * dot(in.direction(), data.normal) / in.direction().length();
			}
			else
			{
				outwardNormal = data.normal;
				niOverNt = 1.0 / m_refIdx;
				cosine = -dot(in.direction(), data.normal) / in.direction().length();
			}

			if (refract(in.direction(), outwardNormal, niOverNt, refracted)) {
				reflectProb = schlick(cosine, m_refIdx);
			}
			else
			{
				reflectProb = 1.0;
			}

			//refract
			if (randf() < reflectProb)
			{
				scattered = Ray(data.p, reflected);
			}
			else
			{
				scattered = Ray(data.p, refracted);
			}
			return true;
		}
		float m_refIdx;
	};
}