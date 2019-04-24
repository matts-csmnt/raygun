#include "rayg_scenes.h"
#include "rayg_material.h"
#include "rayg_sphere.h"
#include "rayg_rects.h"
#include "rayg_box.h"

#include "randf.h"

namespace ray_g{

	//-------------
	// Random Scenes
	//-------------

	SurfaceList RandomScene()
	{
		SurfaceList sl;

		//floor
		sl.add(new Sphere(Vec3(0, -1000, 0), 1000,
			new Lambertian(new CheckerTexture(
				new ConstantTexture(Vec3(0.2, 0.3, 0.1)),
				new ConstantTexture(Vec3(0.9))
			))));
		//roof
		/*sl.add(new Sphere(Vec3(0, 1001, 0), 1000,
			new Lambertian(new CheckerTexture(
				new ConstantTexture(Vec3(0.1, 0.6, 0.6)),
				new ConstantTexture(Vec3(0.9))
			))));*/

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
							new Lambertian(new ConstantTexture(Vec3(randf()*randf(), randf()*randf(), randf()*randf())))));
					}
					else if (chooseMat < 0.95) {	//Metallics
						sl.add(new Sphere(center, 0.2,
							new Metal(new ConstantTexture(Vec3(0.5*(1 + randf()), 0.5*(1 + randf()), 0.5*(1 + randf()))), 0.5*(1 + randf()))));
					}
					else {	//glass/dielectrics
						sl.add(new Sphere(center, 0.2, new Dielectric(1.5)));
					}
				}
			}
		}

		//Add main focus points (large spheres)
		sl.add(new Sphere(Vec3(0, 1, 0), 1.0, new Dielectric(1.5)));
		sl.add(new Sphere(Vec3(-4, 1, 0), 1.0, new Lambertian(new ConstantTexture(Vec3(0.4, 0.4, 0.1)))));
		sl.add(new Sphere(Vec3(4, 1, 0), 1.0, new Metal(new ConstantTexture(Vec3(0.7, 0.6, 0.5)), 0.0)));	//chrome!

		return sl;
	}

	//-------------
	// Test Scenes
	//-------------

	SurfaceList TwoPerlinSpheres()
	{
		SurfaceList sl;
		Texture* pPerlin = new NoiseTexture(5, 0);
		sl.add(new Sphere(Vec3(0, -1000, 0), 1000, new Lambertian(pPerlin)));
		sl.add(new Sphere(Vec3(0, 2, 0), 2, new Lambertian(pPerlin)));
		return sl;
	}

	SurfaceList CornellBox()
	{
		SurfaceList sl;
		Material* white = new Lambertian(new ConstantTexture(Vec3(0.73)));
		Material* red = new Lambertian(new ConstantTexture(Vec3(0.65,0.05,0.05)));
		Material* green = new Lambertian(new ConstantTexture(Vec3(0.12,0.45,0.15)));
		Material* light = new DiffuseLight(new ConstantTexture(Vec3(15)));

		sl.add(new FlipNormals(new YZRect(0,555,0,555,555,green)));
		sl.add(new YZRect(0, 555, 0, 555, 0, red));
		sl.add(new XZRect(213, 343, 227, 332, 554, light));
		sl.add(new FlipNormals(new XZRect(0, 555, 0, 555, 555, white)));
		sl.add(new XZRect(0, 555, 0, 555, 0, white));
		sl.add(new FlipNormals(new XYRect(0, 555, 0, 555, 555, white)));

		sl.add(new Box(Vec3(130, 0, 65), Vec3(295, 165, 230), white));
		sl.add(new Box(Vec3(265, 0, 295), Vec3(430, 330, 460), white));

		return sl;
	}
}
