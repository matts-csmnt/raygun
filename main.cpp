#include "rayg_vec3.h"
#include "rayg_ray.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "Libraries/stb/stb_image_write.h"

constexpr float kMultiplier = 255.99f;
constexpr int k_px_width = 600;
constexpr int k_px_height = 300;
using RGBA_Channels = unsigned char[3];

using namespace ray_g;

vec3 colour(const ray& r)
{
	vec3 unit_dir = unit_vector(r.direction());
	float t = 0.5f * (unit_dir.y() + 1.0f);
	return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}

int main()
{
	RGBA_Channels pixels[k_px_height][k_px_width];

	//image bounds
	vec3 lowerLeftCrnr(-(float)k_px_width / 100, -(float)k_px_height / 100, -1.0f);
	vec3 horizontalUnits(((float)k_px_width / 100) * 2, 0.0f, 0.0f);
	vec3 verticalUnits(0.0f, ((float)k_px_height / 100) * 2, 0.0f);
	vec3 origin(0.0f, 0.0f, 0.0f);

	for (int j(0); j < k_px_height; j++)
	{
		for (int i(0); i < k_px_width; i++)
		{
			float u = float(i) / float(k_px_width);
			float v = float(j) / float(k_px_height);

			ray r(origin, lowerLeftCrnr + u * horizontalUnits + v * verticalUnits);
			vec3 col(colour(r));

			float ir = int(kMultiplier*col.r());
			float ig = int(kMultiplier*col.g());
			float ib = int(kMultiplier*col.b());

			(pixels[j][i])[0] = ir;
			(pixels[j][i])[1] = ig;
			(pixels[j][i])[2] = ib;
			//(pixels[j][i])[3] = 1;
		}
	}

	//output
	stbi_flip_vertically_on_write(1);
	//stbi_write_png("raytrace_output.png", k_px_width, k_px_height, 4, &pixels, sizeof(RGBA_Channels)*k_px_width);
	stbi_write_bmp("raytrace_output.bmp", k_px_width, k_px_height, 3, &pixels);
	return 0;
}