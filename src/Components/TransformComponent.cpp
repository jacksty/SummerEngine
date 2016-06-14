#include "stdafx.h"
#include "TransformComponent.h"


TransformComponent::TransformComponent() :
	position(VEC4_ZERO),
	worldMatrix(MAT4_IDENTITY),
	localMatrix(MAT4_IDENTITY)
{}