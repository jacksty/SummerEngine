#pragma once
#include "stdafx.h"
#include "Singleton.h"

#define INPUT_MANAGER InputManager::getSingletonPtr()

class InputManager final : Singleton<InputManager>
{
	// CONSTANTS

	//tentative
	enum class Key
	{
		K_Q = 1,
		K_T = 5
	};
	typedef Key Button;
	
	// ATTRIBUTES
private:
	/// Functions to be called upon the respective button being pressed down.
	std::unordered_map<Key, void(*)()> onKeyDownRegistry;
	/// Functions to be called upon the respective button being released.
	std::unordered_map<Key, void(*)()> onKeyUpRegistry;

	// CONSTRUCTORS / DESTRUCTORS
	// METHODS
	// GETTERS / SETTERS
};
