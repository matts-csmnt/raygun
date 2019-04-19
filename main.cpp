#include "rayg_vec3.h"
#include "rayg_ray.h"
#include "rayg_surface.h"
#include "rayg_sphere.h"
#include "rayg_camera.h"
#include "rayg_material.h"
#include "randf.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "Libraries/stb/stb_image_write.h"

constexpr double kMultiplier = 255.99;
constexpr int k_px_width = 400;
constexpr int k_px_height = 200;
constexpr int k_num_aa_samples = 25;
using RGBA_Channels = unsigned char[3];

using namespace ray_g;

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

int main()
{
	RGBA_Channels* pixels = new RGBA_Channels[k_px_width*k_px_height];

	//image bounds
	Vec3 lowerLeftCrnr(-(float)k_px_width / 100, -(float)k_px_height / 100, -1.0);
	Vec3 horizontalUnits(((float)k_px_width / 100) * 2, 0.0f, 0.0);
	Vec3 verticalUnits(0.0f, ((float)k_px_height / 100) * 2, 0.0f);
	Vec3 origin(0.0f, 0.0f, 0.0f);

	//World List
	Surface* objects[5];
	objects[0] = new Sphere(Vec3(0, 0, -1),			0.5, new Lambertian(Vec3(0.1,0.2,0.5)));
	objects[1] = new Sphere(Vec3(0, -100.5, -1),	100, new Lambertian(Vec3(0.8, 0.8, 0.0)));
	objects[2] = new Sphere(Vec3(1, 0, -1),			0.5, new Metal(Vec3(0.8, 0.6, 0.2), 0.2));
	objects[3] = new Sphere(Vec3(-1, 0, -1),		0.5, new Dialectric(1.5));
	objects[4] = new Sphere(Vec3(-1, 0, -1),		-0.45, new Dialectric(1.5));
	Surface* world = new SurfaceList(objects, 5);

	//Camera
	Camera cam(k_px_width, k_px_height);

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
				col += colour(r, world, 0);
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

	delete[] world;
	
	return 0;
}