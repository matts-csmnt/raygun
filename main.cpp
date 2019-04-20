#include "rayg_vec3.h"
#include "rayg_ray.h"
#include "rayg_surface.h"
#include "rayg_sphere.h"
#include "rayg_camera.h"
#include "rayg_material.h"
#include "rayg_bvh.h"
#include "randf.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "Libraries/stb/stb_image_write.h"

constexpr double kMultiplier = 255.99;
constexpr int k_px_width = 1200;
constexpr int k_px_height = 600;
constexpr int k_num_aa_samples = 25;
using RGBA_Channels = unsigned char[3];
static const ray_g::Vec3 kUpVec = ray_g::Vec3( 0, 1, 0 );

namespace ray_g {
	Vec3 colour(const Ray& r, Surface* world, int depth)
	{
		hit_data data;
		if (world->hit(r, 0.001, FLT_MAX, data))
		{
			Ray scattered;
			Vec3 attenuation;
			if (depth < 50 && data.mat->scatter(r, data, attenuation, scattered))
			{
				Vec3 col = colour(scattered, world, depth + 1);
				return attenuation * col;
			}
			else
			{
				return Vec3(0, 0, 0);
			}
		}
		else
		{
			Vec3 unit_dir = unit_vector(r.direction());
			float t = 0.5 * (unit_dir.y() + 1.0);
			return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
		}
	}

	//random scene
	SurfaceList RandomScene()
	{
		SurfaceList sl;

		//floor
		sl.add(new Sphere(Vec3(0, -1000, 0), 1000, new Lambertian(Vec3((0.8, 0.8, 0.1)))));

		for (int a = -11; a < 11; a++)
		{
			for (int b = -11; b < 11; b++)
			{
				float chooseMat = randf();
				Vec3 center(a + 0.9*randf(), 0.2, b + 0.9*randf());

				if ((center - Vec3(4, 0.2, 0)).length() > 0.9)
				{
					if (chooseMat < 0.8) {	//diffuse material
						//sl.add(new Sphere(center, 0.2,
						//	new Lambertian(Vec3(randf()*randf(), randf()*randf(), randf()*randf()))));
						sl.add(new MovingSphere(center, center + Vec3(0, 0.5*randf(), 0), 0, 1, 0.2,
							new Lambertian(Vec3(randf()*randf(), randf()*randf(), randf()*randf()))));
					}
					else if (chooseMat < 0.95) {	//Metallics
						sl.add(new Sphere(center, 0.2,
							new Metal(Vec3(0.5*(1 + randf()), 0.5*(1 + randf()), 0.5*(1 + randf())), 0.5*(1 + randf()))));
					}
					else {	//glass/dielectrics
						sl.add(new Sphere(center, 0.2, new Dielectric(1.5)));
					}
				}
			}
		}

		//Add main focus points (large spheres)
		sl.add(new Sphere(Vec3(0, 1, 0), 1.0, new Dielectric(1.5)));
		sl.add(new Sphere(Vec3(-4, 1, 0), 1.0, new Lambertian(Vec3(0.4, 0.4, 0.1))));
		sl.add(new Sphere(Vec3(4, 1, 0), 1.0, new Metal(Vec3(0.7, 0.6, 0.5), 0.0)));	//chrome!

		return sl;
	}
}

using namespace ray_g;

int main()
{
	RGBA_Channels* pixels = new RGBA_Channels[k_px_width*k_px_height];

	//World List
	SurfaceList world;
	//world.add(new Sphere(Vec3(0, 0, -1),			1, new Lambertian(Vec3(0.1,0.2,0.5))));
	//world.add(new Sphere(Vec3(0, -100.5, -1),	100, new Lambertian(Vec3(0.8, 0.8, 0.0))));
	//world.add(new Sphere(Vec3(1, 0, -1),			1, new Metal(Vec3(0.8, 0.6, 0.2), 0.2)));
	//world.add(new Sphere(Vec3(-1, 0, -1),		1, new Dielectric(1.5)));
	//world.add(new Sphere(Vec3(-1, 0, -1),		-0.9, new Dielectric(1.5)));

	world = RandomScene();

	//Camera
	Vec3 lookfrom(13, 2, 3);
	Vec3 lookat(0, 0, 0);
	float distToFocus = (lookfrom - lookat).length();
	float aperture = 0.1;

	Camera cam(lookfrom, lookat, kUpVec, k_px_width, k_px_height, 20, aperture, distToFocus, 0, 1);

	BVHNode worldTree(&world.getList()[0], world.size(), 0.0, 1.0);

	for (int j = k_px_height - 1; j >= 0; j--)
	{
		for (int i(0); i < k_px_width; i++)
		{
			int idx((j*k_px_width) + i);
			Vec3 col(0, 0, 0);

			//AA Samples
			for (int s(0); s < k_num_aa_samples; ++s)
			{
				float u = float(i + randf()) / float(k_px_width);
				float v = float(j + randf()) / float(k_px_height);

				Ray r = cam.getRay(u, v);
				col += colour(r, &worldTree, 0);
			}

			col /= float(k_num_aa_samples);

			//gamma correct
			col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

			int ir = int(kMultiplier*col.r());
			int ig = int(kMultiplier*col.g());
			int ib = int(kMultiplier*col.b());

			pixels[idx][0] = ir;
			pixels[idx][1] = ig;
			pixels[idx][2] = ib;
		}
	}

	//output
	stbi_flip_vertically_on_write(1);
	//stbi_write_png("raytrace_output.png", k_px_width, k_px_height, 4, &pixels, sizeof(RGBA_Channels)*k_px_width);
	stbi_write_bmp("raytrace_output.bmp", k_px_width, k_px_height, 3, *pixels);

	if (pixels)
	{
		delete[] pixels;
		pixels = nullptr;
	}

	world.cleanup();
	
	return 0;
}