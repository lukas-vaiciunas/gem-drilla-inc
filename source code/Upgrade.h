#pragma once

#include <cinttypes>

class Upgrade
{
public:
	Upgrade(uint8_t level, uint8_t maxLevel, uint64_t cost, float costMult);

	void unlock();

	uint8_t getLevel() const;
	uint8_t getMaxLevel() const;
	uint64_t getCost() const;
private:
	uint8_t level_;
	uint8_t maxLevel_;
	uint64_t cost_;
	float costMult_;
};