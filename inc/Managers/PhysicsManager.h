#pragma once
#include "stdafx.h"
#include "Singleton.h"

#define PHYSICS_MANAGER PhysicsManager::getSingletonPtr();
#define GLOBAL_DELTA_TIME PhysicsManager::getDeltaTime();

class PhysicsManager final : Singleton<PhysicsManager>
{
	// CONSTANTS
	// ATTRIBUTES
private:
	static float64 deltaTime;

public:
	static float64 getDeltaTime() { return deltaTime; }
};