#pragma once
#include "stdafx.h"

class TransformComponent
{

	// ATTRIBUTES
protected:
	TransformComponent* parent;
	TransformComponent** children;

public:
	vector4 position;
	//Quaternion orientation;
	matrix4x4 worldMatrix;
	matrix4x4 localMatrix;
	bool dirty;

	// CONSTRUCTORS / DESTRUCTORS
public:
	TransformComponent();
};