#include "rayg_perlin.h"
#include "common_defines.h"

namespace ray_g {

	//-------------
	// Perlin Noise
	//-------------

	Vec3* Perlin::m_randomvec = perlinGenerate();
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

		int i = floor(p.x());
		int j = floor(p.y());
		int k = floor(p.z());

		Vec3 c[2][2][2];
		for (int di(0); di < 2; di++)
			for (int dj(0); dj < 2; dj++)
				for (int dk(0); dk < 2; dk++)
					c[di][dj][dk] = m_randomvec[m_permutationX[(i+di)&255] ^ m_permutationY[(j+dj)&255] ^ m_permutationZ[(k+dk)&255]];	//mod256
		return trilinearInterpolate(c,u,v,w);
	}
	void Perlin::cleanup()
	{
		SAFE_DELETE(m_randomvec);
		SAFE_DELETE(m_permutationX);
		SAFE_DELETE(m_permutationY);
		SAFE_DELETE(m_permutationZ);
	}

	float Perlin::turbulence(const Vec3 & p, int depth) const
	{
		float sum = 0;
		Vec3 tempP = p;
		float weight = 1.0;
		for (int i(0); i < depth; i++)
		{
			sum += weight * noise(tempP);
			weight *= 0.5;
			tempP *= 2;
		}
		return fabs(sum);
	}

	float trilinearInterpolate(Vec3 c[2][2][2], float u, float v, float w)
	{
		float uu = u * u*(3 - 2 * u);	//hermite cubic
		float vv = v * v*(3 - 2 * v);
		float ww = w * w*(3 - 2 * w);

		float sum = 0;
		for (int i(0); i < 2; i++)
			for (int j(0); j < 2; j++)
				for (int k(0); k < 2; k++) {
					Vec3 weight_v(u-i,v-j,w-k);
					sum += (i*uu + (1 - i) * (1 - uu)) *
						(j*vv + (1 - j) * (1 - vv)) *
						(k*ww + (1 - k) * (1 - ww)) *
						dot(c[i][j][k], weight_v);
				}
		return sum;
	}
}