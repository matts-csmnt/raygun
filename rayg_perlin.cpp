#include "rayg_perlin.h"
#include "common_defines.h"

namespace ray_g {

	//-------------
	// Perlin Noise
	//-------------

	float* Perlin::m_randomf = perlinGenerate();
	int* Perlin::m_permutationX = perlinGeneratePerm();
	int* Perlin::m_permutationY = perlinGeneratePerm();
	int* Perlin::m_permutationZ = perlinGeneratePerm();

	Perlin::~Perlin()
	{
		cleanup();
	}

	float Perlin::noise(const Vec3 & p) const
	{
		float u = p.x() - floor(p.x());
		float v = p.y() - floor(p.y());
		float w = p.z() - floor(p.z());

		int i = int(4 * p.x()) & 255;	//mod 256
		int j = int(4 * p.y()) & 255;
		int k = int(4 * p.z()) & 255;

		return m_randomf[m_permutationX[i] ^ m_permutationY[j] ^ m_permutationZ[k]];
	}
	void Perlin::cleanup()
	{
		SAFE_DELETE(m_randomf);
		SAFE_DELETE(m_permutationX);
		SAFE_DELETE(m_permutationY);
		SAFE_DELETE(m_permutationZ);
	}
}