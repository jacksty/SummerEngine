#include "stdafx.h"
#include "AABB.h"

AABB::AABB() :
	min(VEC4_ZERO), max(VEC4_ZERO)
{}


AABB::AABB(vector4 min, vector4 max) :
	min(min), max(max)
{}


void AABB::buildFromList(const vector4* list, int length)
{
	min = vector4(list[0]);
	max = vector4(list[0]);

	for (int i = 0; i < length; ++i)
	{
		if (list[i].x < min.x)
			min.x = list[i].x;
		else if (list[i].x > max.x)
			max.x = list[i].x;

		if (list[i].y < min.y)
			min.y = list[i].y;
		else if (list[i].y > max.y)
			max.y = list[i].y;

		if (list[i].z < min.z)
			min.z = list[i].z;
		else if (list[i].z > max.z)
			max.z = list[i].z;
	}
}


bool AABB::containsPoint(vector4 point) const
{
	bool x = point.x >= min.x && point.x <= max.x;
	bool y = point.y >= min.y && point.y <= max.y;
	bool z = point.z >= min.z && point.z <= max.z;

	return x && y && z;
}
