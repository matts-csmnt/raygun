#include "rayg_vec3.h"
#include "rayg_ray.h"
#include "rayg_surface.h"
#include "rayg_sphere.h"
#include "rayg_material.h"
#include "rayg_renderer.h"

#include "randf.h"

#include "rayg_scenes.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Libraries/stb/stb_image.h"

constexpr int k_px_width = 1200;
constexpr int k_px_height = 600;
constexpr int k_num_aa_samples = 100;
static const ray_g::Vec3 kUpVec = ray_g::Vec3( 0, 1, 0 );

using namespace ray_g;

int main()
{
	//World List
	SurfaceList world = TwoPerlinSpheres();	//RandomScene();

	//Add textured sphere
	int nx, ny, nn;
	unsigned char* textureData = stbi_load("Media/Textures/earth.jpg", &nx, &ny, &nn, 0);
	world.add(new Sphere(Vec3(4, 1, 0), 1, new Lambertian(new ImageTexture(textureData, nx, ny))));

	//Camera Vars
	Vec3 lookfrom(13, 2, 3);
	Vec3 lookat(0, 0, 0);
	float distToFocus = (lookfrom - lookat).length();
	float aperture = 0.1;

	//Renderer Setup
	Renderer render;

	render.SetCamera(lookfrom, lookat, kUpVec, k_px_width, k_px_height, 20, aperture, distToFocus, 0, 1);
	render.SetScene(&world);
	render.SetImageOutput("raytrace_output.bmp");

	//Draw
	render.Draw(k_num_aa_samples);

	return 0;
}