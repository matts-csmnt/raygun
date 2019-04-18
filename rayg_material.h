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

	//lambertial material
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
		Metal(const Vec3& a) : m_albedo(a) {}
		bool scatter(const Ray& in, const hit_data& data, Vec3& attenuation, Ray& scattered) const override {
			Vec3 reflected = reflect(unit_vector(in.direction()), data.normal);
			scattered = Ray(data.p, reflected - data.p);
			attenuation = m_albedo;
			return (dot(scattered.direction(), data.normal) > 0);
		}
		Vec3 m_albedo;
	};
}