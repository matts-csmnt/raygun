#pragma once
#include "rayg_vec3.h"
#include "rayg_ray.h"

namespace ray_g {

	class SurfaceList;
	class Surface;
	class BVHNode;
	class Camera;

	using RGBA_Channels = unsigned char[3];

	//--------------
	//Renderer Class
	//--------------

	class Renderer {
	public:
		Renderer() : m_camera(nullptr), m_bvh(nullptr), m_scene(nullptr), 
			m_pxWidth(1200), m_pxHeight(600), m_aaSamples(50) {};
		~Renderer();

		int SetCamera(const Vec3& pos, const Vec3& lookat, const Vec3& up, int sWidth, int sHeight, 
			float fovy, float aperture, float focusDist, float time0, float time1);
		int SetScene(SurfaceList* scene);
		int SetImageOutput(const char* filepath);

		int Draw(int aa = 25);
		int Draw(SurfaceList* scene, int aa = 25);

	private:
		int m_pxWidth;
		int m_pxHeight;
		int m_aaSamples;
		const char* m_filepath = "output.bmp";

		SurfaceList* m_scene;
		BVHNode* m_bvh;
		Camera* m_camera;

		bool checkMembers();
		Vec3 colour(const Ray& r, Surface* world, int depth);
	};
}