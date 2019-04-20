#include "rayg_material.h"

#include "randf.h"

namespace ray_g {

	//-------------
	// Sphere Gen
	//-------------

	Vec3 random_in_unit_sphere()
	{
		Vec3 p;
		do {
			p = 2.0 * Vec3(randf(), randf(), randf()) - Vec3(1.0, 1.0, 1.0);
		} while (p.squared_length() >= 1.0);
		return p;
	}

	//-------------
	// Lambertian
	//-------------

	bool Lambertian::scatter(const Ray& in, const hit_data& data, Vec3& attenuation, Ray& scattered) const {
		Vec3 target = data.p + data.normal + random_in_unit_sphere();
		scattered = Ray(data.p, target - data.p, in.time());
		attenuation = m_albedo;
		return true;
	}

	//-------------
	// Metallics
	//-------------

	bool Metal::scatter(const Ray& in, const hit_data& data, Vec3& attenuation, Ray& scattered) const {
		Vec3 reflected = reflect(unit_vector(in.direction()), data.normal);
		scattered = Ray(data.p, reflected + m_fuzz * random_in_unit_sphere(), in.time());
		attenuation = m_albedo;
		return (dot(scattered.direction(), data.normal) > 0);
	}

	//-------------
	// Dielectrics
	//-------------

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

	bool Dielectric::scatter(const Ray& in, const hit_data& data, Vec3& attenuation, Ray& scattered) const {
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
}