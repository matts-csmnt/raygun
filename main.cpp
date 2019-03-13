#include "rayg_vec3.h"
#include "rayg_ray.h"
#include "rayg_surface.h"
#include "rayg_sphere.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "Libraries/stb/stb_image_write.h"

constexpr float kMultiplier = 255.99f;
constexpr int k_px_width = 512;
constexpr int k_px_height = 512;
using RGBA_Channels = unsigned char[3];

using namespace ray_g;

Vec3 colour(const Ray& r, const SurfaceList& world)
{
	hit_data data;

	if (world.hit(r, 0.0, FLT_MAX, data))
	{
		return data.normal * 0.5f + 0.5f;
	}
	else
	{
		Vec3 unit_dir = unit_vector(r.direction());
		float t = 0.5f * (unit_dir.y() + 1.0f);
		return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
	}
}

int main()
{
	RGBA_Channels* pixels = new RGBA_Channels[k_px_width*k_px_height];

	//image bounds
	Vec3 lowerLeftCrnr(-(float)k_px_width / 100, -(float)k_px_height / 100, -1.0f);
	Vec3 horizontalUnits(((float)k_px_width / 100) * 2, 0.0f, 0.0f);
	Vec3 verticalUnits(0.0f, ((float)k_px_height / 100) * 2, 0.0f);
	Vec3 origin(0.0f, 0.0f, 0.0f);

	//World List
	SurfaceList objects;
	objects.append(new Sphere(Vec3(0, 0, -1), 0.5));
	objects.append(new Sphere(Vec3(0, -100.5, -1), 100));

	for (int j(0); j < k_px_height; j++)
	{
		for (int i(0); i < k_px_width; i++)
		{
			int idx((j*k_px_width) + i);

			float u = float(i) / float(k_px_width);
			float v = float(j) / float(k_px_height);

			Ray r(origin, lowerLeftCrnr + u * horizontalUnits + v * verticalUnits);
			Vec3 col(colour(r, objects));

			float ir = int(kMultiplier*col.r());
			float ig = int(kMultiplier*col.g());
			float ib = int(kMultiplier*col.b());

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
		delete pixels;
		pixels = nullptr;
	}

	return 0;
}