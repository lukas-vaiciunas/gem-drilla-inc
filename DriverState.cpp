#include "DriverState.h"

DriverState::DriverState(DriverStateType type) :
	sf::Drawable(),
	type_(type)
{}

DriverStateType DriverState::getType() const
{
	return type_;
}