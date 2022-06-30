#include "Upgrade.h"

Upgrade::Upgrade(uint8_t level, uint8_t maxLevel, uint64_t cost, float costMult) :
	level_(level),
	maxLevel_(maxLevel),
	cost_(cost),
	costMult_(costMult)
{}

void Upgrade::unlock()
{
	++level_;
	cost_ = static_cast<uint64_t>(cost_ * costMult_);
}

uint8_t Upgrade::getLevel() const
{
	return level_;
}

uint8_t Upgrade::getMaxLevel() const
{
	return maxLevel_;
}

uint64_t Upgrade::getCost() const
{
	return cost_;
}