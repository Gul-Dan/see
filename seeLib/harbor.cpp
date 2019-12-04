#include "stdafx.h"
#include "harbor.h"

Harbor::Harbor(const ShipType& type)
	:	isLoading_(false),
		type(type)
{
}

void Harbor::load(const Ship& ship)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ship.capacity));
	setIsLoading(false);
}

bool Harbor::isLoading() const
{
	return isLoading_;
}

ShipType Harbor::getType() const
{
	return type;
}

void Harbor::setIsLoading(bool value)
{
	if (isLoading_ && value)
		throw "";
	isLoading_ = value;
}

void Harbor::setIsLoading()
{
	setIsLoading(true);
}