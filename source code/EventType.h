#pragma once

#include <cinttypes>

enum class EventType : uint8_t
{
	ChangeDriverState,
	ChangeDriverStateExplicit,
	Quit,
	PlayerMoved,
	BlockMined,
	GameOver
};