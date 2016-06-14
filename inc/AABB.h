#pragma once
#include "stdafx.h"

class AABB
{
	// ATTRIBUTES
public:
	vector4 min;
	vector4 max;

	// CONSTRUCTORS / DESTRUCTORS
public:
	AABB(vector4 min, vector4 max);
	AABB();

	// METHODS
public:
	/// Builds the AABB based on points from the list of vectors.
	void buildFromList(const vector4* list, int length);
	/// Is this point contained in the AABB?
	bool containsPoint(vector4 point) const;
};