#pragma once

#include <cinttypes>

enum class DriverStateType : uint8_t
{
	None,
	Menu,
	Upgrades,
	Game,
	Results,
	Transition
};