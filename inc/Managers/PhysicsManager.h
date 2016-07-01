#pragma once
#include "stdafx.h"
#include "Singleton.h"

namespace SE
{
#define PHYSICS_MANAGER PhysicsManager::getSingletonPtr();
#define GLOBAL_DELTA_TIME PhysicsManager::getDeltaTime();

	class PhysicsManager final : Singleton<PhysicsManager>
	{
		// ATTRIBUTES
	private:
		static float64 DeltaTime;

		// METHODS
	public:
		static float64 GetDeltaTime() { return DeltaTime; }
	};
}
