#pragma once
#include "rayg_vec3.h"
#include "randf.h"

namespace ray_g {

	//-------------
	// Perlin Noise
	//-------------

	class Perlin {
	public:
		~Perlin();
		float noise(const Vec3&) const;
		void cleanup();
		float turbulence(const Vec3& p, int depth = 7) const;

		static Vec3* m_randomvec;
		static int* m_permutationX;
		static int* m_permutationY;
		static int* m_permutationZ;
	};

	static Vec3 * perlinGenerate()
	{
		Vec3* p = new Vec3[256];
		for (int i(0); i < 256; ++i)
			p[i] = unit_vector(Vec3(-1 + 2 *randf(), -1 + 2 * randf(), -1 + 2 * randf()));
		return p;
	}

	inline void permute(int * p, int n)
	{
		for (int i = n - 1; i > 0; i--)
		{
			int target = int(randf()*(i + 1));
			int temp = p[i];
			p[i] = p[target];
			p[target] = temp;
		}
	}

	static int * perlinGeneratePerm()
	{
		int* p = new int[256];
		for (int i(0); i < 256; i++)
			p[i] = i;
		permute(p, 256);
		return p;
	}

	float trilinearInterpolate(Vec3[2][2][2], float, float, float);
}
