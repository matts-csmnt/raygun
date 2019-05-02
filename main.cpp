#include "rayg_vec3.h"
#include "rayg_ray.h"
#include "rayg_surface.h"
#include "rayg_sphere.h"
#include "rayg_rects.h"
#include "rayg_material.h"
#include "rayg_renderer.h"
#include "rayg_background.h"

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
	SurfaceList world = CornellSmoke();

	//Add textured sphere
	//int nx, ny, nn;
	//unsigned char* textureData = stbi_load("Media/Textures/earth.jpg", &nx, &ny, &nn, 0);
	//world.add(new Sphere(Vec3(4, 1, 0), 1, new Lambertian(new ImageTexture(textureData, nx, ny))));

	//Add lights
	//world.add(new XYRect(3, 5, 1, 3, -2, new DiffuseLight(new ConstantTexture(Vec3(4)))));

	//BG
	Background* bg = new SkyGrad();

	//Camera Vars
	//Vec3 lookfrom(13, 2, 3);
	//Vec3 lookat(0, 0, 0);
	//float distToFocus = (lookfrom - lookat).length();
	//float aperture = 0.1;
	//float fovy = 20.0;
	Vec3 lookfrom(278, 278, -800);
	Vec3 lookat(278, 278, 0);
	float distToFocus = 10;
	float aperture = 0;
	float fovy = 40.0;

	//Renderer Setup
	Renderer render;

	render.SetCamera(lookfrom, lookat, kUpVec, k_px_width, k_px_height, fovy, aperture, distToFocus, 0, 1);
	render.SetScene(&world);
	render.SetImageOutput("raytrace_output.bmp");
	render.SetBackground(bg);

	//Draw
	render.Draw(k_num_aa_samples);

	//cleanup
	SAFE_DELETE(bg);

	return 0;
}