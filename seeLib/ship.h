#pragma once

const unsigned amountOfTypes = 5;

enum ShipType
{
	ContainerShip, BulkCarrier, TankerShip, OffshoreVessel, FishingVessel
};

//stores type and capacity of ship
struct Ship
{
	Ship(ShipType type, unsigned int capacity)
		: type(type)
		, capacity(capacity)
	{
	}
	int capacity;
	ShipType type;
};