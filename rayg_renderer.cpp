#include "rayg_renderer.h"
#include "rayg_camera.h"
#include "rayg_bvh.h"
#include "rayg_surface.h"
#include "rayg_material.h"
#include "rayg_background.h"

#include "common_defines.h"
#include "randf.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "Libraries/stb/stb_image_write.h"

namespace ray_g {
	
	//--------------
	//Renderer Class
	//--------------

	Renderer::~Renderer()
	{
	}

	int Renderer::SetCamera(const Vec3 & pos, const Vec3 & lookat, const Vec3 & up, int sWidth, int sHeight, float fovy, float aperture, float focusDist, float time0, float time1)
	{
		SAFE_DELETE(m_camera);	//try delete old camera

		m_camera = new Camera(pos, lookat, up, sWidth, sHeight, fovy, aperture, focusDist, time0, time1);
		if (m_camera)
			return 1;
		else
		{
			printf("failed to create camera. \n");
			return 0;
		}
	}

	int Renderer::SetScene(SurfaceList* scene)
	{
		m_scene = scene;
		if (m_scene)
			return 1;
		else
		{
			printf("failed to load scene. \n");
			return 0;
		}
	}

	int Renderer::SetImageOutput(const char * filepath)
	{
		m_filepath = filepath;
		if(m_filepath)
			return 1;
		else
		{
			printf("failed to set output filename. \n");
			return 0;
		}
	}

	int Renderer::SetBackground(Background * bg)
	{
		m_bg = bg;
		if (m_bg)
			return 1;
		else
		{
			printf("failed to set background. \n");
			return 0;
		}
	}

	int Renderer::Draw(int aa)
	{
		if (checkMembers())
		{
			m_aaSamples = aa;
			m_bvh = new BVHNode(&m_scene->getList()[0], m_scene->size(), m_camera->getTime0(), m_camera->getTime1());

			if (!m_bvh)
			{
				printf("failed to create BVH Tree. \n");
				return 0;
			}

			//Get memory for output...
			RGBA_Channels* pixels = new RGBA_Channels[m_pxWidth*m_pxHeight];
			if (!pixels)
			{
				printf("failed to allocate memory for output image. \n");
				return 0;
			}

			//Draw...
			for (int j = m_pxHeight - 1; j >= 0; j--)
			{
				for (int i(0); i < m_pxWidth; i++)
				{
					int idx((j*m_pxWidth) + i);
					Vec3 col(0, 0, 0);

					//AA Samples
					for (int s(0); s < m_aaSamples; ++s)
					{
						float u = float(i + randf()) / float(m_pxWidth);
						float v = float(j + randf()) / float(m_pxHeight);

						Ray r = m_camera->getRay(u, v);
						col += colour(r, m_bvh, 0);
					}

					col /= float(m_aaSamples);

					//gamma correct
					col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

					int ir = int(255.99*col.r());
					int ig = int(255.99*col.g());
					int ib = int(255.99*col.b());

					pixels[idx][0] = ir;
					pixels[idx][1] = ig;
					pixels[idx][2] = ib;
				}
			}

			//output
			stbi_flip_vertically_on_write(1);
			//stbi_write_png("raytrace_output.png", k_px_width, k_px_height, 4, &pixels, sizeof(RGBA_Channels)*k_px_width);
			stbi_write_bmp("raytrace_output.bmp", m_pxWidth, m_pxHeight, 3, *pixels);

			SAFE_DELETE(pixels);

			m_bvh->cleanup();
			//world.cleanup(); -- tree cleans up surfaces...
		}
	}

	int Renderer::Draw(SurfaceList* scene, int aa)
	{
		SetScene(scene);
		Draw(aa);
	}

	bool Renderer::checkMembers()
	{
		if (!m_camera || !m_scene)
			return false;
		else
			return true;
	}

	Vec3 Renderer::colour(const Ray& r, Surface* world, int depth)
	{
		hit_data data;
		if (world->hit(r, 0.001, FLT_MAX, data))
		{
			Ray scattered;
			Vec3 attenuation;
			Vec3 emitted = data.mat->emittted(data.u, data.v, data.p);
			if (depth < 50 && data.mat->scatter(r, data, attenuation, scattered))
			{
				Vec3 col = colour(scattered, world, depth + 1);
				return emitted + attenuation * col;
			}
			else
			{
				return emitted;
			}
		}
		else
		{
			if (m_bg)
				return m_bg->getColour(r);
			else
				return Vec3(0, 0, 0);
		}
	}
}