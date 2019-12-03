#include "stdafx.h"
#include "harbor.h"

Harbor::Harbor(const ShipType& type)
	:	isLoading_(false),
		type(type)
{
}

void Harbor::load(const Ship& ship)
{
	std::this_thread::sleep_for(std::chrono::seconds(ship.capacity));
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
	isLoading_ = value;
}

void Harbor::setIsLoading()
{
	setIsLoading(true);
}