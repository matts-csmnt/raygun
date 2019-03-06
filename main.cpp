#include "rayg_vec3.h"
#include "rayg_ray.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "Libraries/stb/stb_image_write.h"

constexpr float kMultiplier = 255.99f;
constexpr int k_px_width = 1024;
constexpr int k_px_height = 1024;
using RGBA_Channels = unsigned char[3];

using namespace ray_g;

float sphere_intersect(const vec3& center, float radius, const ray& r)
{
	vec3 OC = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0f * dot(OC, r.direction());
	float c = dot(OC, OC) - radius * radius;
	float discriminant = b * b - 4 * a*c;
	
	if (discriminant < 0)
		return -1.0f;
	else
		return (-b - sqrt(discriminant)) / (2.0f*a);
}

vec3 colour(const ray& r)
{
	float t = (sphere_intersect(vec3(0, 0, -1), 0.75f, r));
	if (t > 0.0f)
	{
		vec3 N = unit_vector(r.point_at_param(t) - vec3(0, 0, -1));
		return 0.5f*vec3(N.x() + 1, N.y() + 1, N.z() + 1);
	}

	//bg col
	vec3 unit_dir = unit_vector(r.direction());
	t = 0.5f * (unit_dir.y() + 1.0f);
	return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}

int main()
{
	RGBA_Channels* pixels = new RGBA_Channels[k_px_width*k_px_height];

	//image bounds
	vec3 lowerLeftCrnr(-(float)k_px_width / 100, -(float)k_px_height / 100, -1.0f);
	vec3 horizontalUnits(((float)k_px_width / 100) * 2, 0.0f, 0.0f);
	vec3 verticalUnits(0.0f, ((float)k_px_height / 100) * 2, 0.0f);
	vec3 origin(0.0f, 0.0f, 0.0f);

	for (int j(0); j < k_px_height; j++)
	{
		for (int i(0); i < k_px_width; i++)
		{
			int idx((j*k_px_width) + i);

			float u = float(i) / float(k_px_width);
			float v = float(j) / float(k_px_height);

			ray r(origin, lowerLeftCrnr + u * horizontalUnits + v * verticalUnits);
			vec3 col(colour(r));

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