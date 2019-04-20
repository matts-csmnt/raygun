#include "rayg_bvh.h"
#include "randf.h"
#include "common_defines.h"
#include<iostream>

namespace ray_g {

	//-------------------------
	// Axis Splitting compares
	//-------------------------

	int box_x_cmp(const void * a, const void * b)
	{
		AABB boxLeft, boxRight;
		Surface* ah = *(Surface**)a;
		Surface* bh = *(Surface**)b;

		if (!ah->boundingBox(0, 0, boxLeft) || !bh->boundingBox(0, 0, boxRight))
		{
			std::cerr << "no bounding box in BVHNode constructor...\n";
		}

		if (boxLeft.min().x() - boxRight.min().x() < 0.0)
		{
			return -1;
		}
		else
			return 1;
	}

	int box_y_cmp(const void * a, const void * b)
	{
		AABB boxLeft, boxRight;
		Surface* ah = *(Surface**)a;
		Surface* bh = *(Surface**)b;

		if (!ah->boundingBox(0, 0, boxLeft) || !bh->boundingBox(0, 0, boxRight))
		{
			std::cerr << "no bounding box in BVHNode constructor...\n";
		}

		if (boxLeft.min().y() - boxRight.min().y() < 0.0)
		{
			return -1;
		}
		else
			return 1;
	}

	int box_z_cmp(const void * a, const void * b)
	{
		AABB boxLeft, boxRight;
		Surface* ah = *(Surface**)a;
		Surface* bh = *(Surface**)b;

		if (!ah->boundingBox(0, 0, boxLeft) || !bh->boundingBox(0, 0, boxRight))
		{
			std::cerr << "no bounding box in BVHNode constructor...\n";
		}

		if (boxLeft.min().z() - boxRight.min().z() < 0.0)
		{
			return -1;
		}
		else
			return 1;
	}

	//--------------------------
	// Bounding Volume Hierarchy
	//--------------------------

	BVHNode::BVHNode(Surface** s, int n, float time0, float time1)
	{
		int axis = int(3*randf());

		//Split the list through an axis
		if (axis == 0)
			qsort(s, n, sizeof(Surface*), box_x_cmp);
		else if(axis == 1)
			qsort(s, n, sizeof(Surface*), box_y_cmp);
		else
			qsort(s, n, sizeof(Surface*), box_z_cmp);

		//split
		if (n == 1)
		{
			m_right = m_left = s[0];
		}
		else if (n == 2)
		{
			m_left = s[0];
			m_right = s[1];
		}
		else
		{
			m_left = new BVHNode(s, n / 2, time0, time1);
			m_right = new BVHNode(s + n / 2, n - n / 2, time0, time1);
		}

		AABB boxLeft, boxRight;
		if (!m_left->boundingBox(time0, time1, boxLeft) || !m_right->boundingBox(time0, time1, boxRight))
		{
			std::cerr << "no bounding box in BVHNode constructor...\n";
		}
		m_box = surroundingBox(boxLeft, boxRight);
	}

	BVHNode::~BVHNode()
	{
		cleanup();
	}

	bool BVHNode::hit(const Ray & r, float tmin, float tmax, hit_data & data) const
	{
		if (m_box.hit(r, tmin, tmax))	//has the box been hit?
		{
			hit_data leftData, rightData;
			bool hitLeft = m_left->hit(r, tmin, tmax, leftData);
			bool hitRight = m_left->hit(r, tmin, tmax, rightData);

			if (hitLeft && hitRight)
			{
				if (leftData.t < rightData.t)
					data = leftData;
				else
					data = rightData;
				return true;
			}
			else if (hitLeft)
			{
				data = leftData;
				return true;
			}
			else if (hitRight)
			{
				data = rightData;
				return true;
			}
			else
				return false;
		}
		return false;
	}

	bool BVHNode::boundingBox(float t0, float t1, AABB & bb) const
	{
		bb = m_box;
		return true;
	}

	void BVHNode::cleanup()
	{
		SAFE_DELETE(m_left);
		SAFE_DELETE(m_right);
	}
}