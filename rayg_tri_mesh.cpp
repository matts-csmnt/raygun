#include "rayg_tri_mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "Libraries/tinyobjloader/tiny_obj_loader.h"

ray_g::TriangleMesh::TriangleMesh(const Vec3 & p, Material * m, const char * filepath)
	: m_mat(m), m_pos(p)
{
	loadFromFile(filepath);
}

bool ray_g::TriangleMesh::hit(const Ray & r, float t_min, float t_max, hit_data & data) const
{
	if (m_triangles.hit(r, t_min, t_max, data))
	{
		data.mat = m_mat;
		return true;
	}
	else
		return false;
}

void ray_g::TriangleMesh::cleanup()
{
	m_triangles.cleanup();
}

bool ray_g::TriangleMesh::boundingBox(float t0, float t1, AABB & bb) const
{
	return m_triangles.boundingBox(t0, t1, bb);
}

bool ray_g::TriangleMesh::loadFromFile(const char * file)
{
	std::cout << "Loading " << file << std::endl;

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, file);

	if (!warn.empty()) {
		std::cout << "WARN: " << warn << std::endl;
	}

	if (!err.empty()) {
		std::cerr << "ERR: " << err << std::endl;
	}

	if (!ret) {
		printf("Failed to load/parse .obj.\n");
		return false;
	}

	//create mesh
	m_triangles.cleanup();
	m_triangles.clear();
	Triangle* tri = new Triangle();

	for (tinyobj::shape_t shape : shapes)
	{
		for (int i(0); i < shape.mesh.indices.size(); ++i)
		{
			int mod3 = i % 3;
			tinyobj::index_t idx = shape.mesh.indices.at(i);

			//get vertex
			Vec3 v = attrib.vertices.at(idx.vertex_index);

			switch (mod3)
			{
			case 0: tri->setP0(v); break;
			case 1: tri->setP1(v); break;
			case 2: tri->setP2(v); break;
			}

			//every 3 indices...
			if (!(mod3 % 3))
			{
				m_triangles.add(tri);

				if(i < (shape.mesh.indices.size() - 1))
					tri = new Triangle();
			}
		}
	}

	printf("Loaded OK!\n");

	return true;
}

