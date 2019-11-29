#pragma once

const unsigned short amoutOfTypes = 6;

enum ShipType
{
	ContainerShip, BulkCarrier, TankerShip, OffshoreVessel, FishingVessel
};

//stores type and capacity of ship
struct Ship
{
	Ship(ShipType type, unsigned int capacity)
		: type(type),
		capacity(capacity)
		// todo: which indent is recommended? can I comment 1 row from initialization list?
	{
	}
	int capacity;
	ShipType type;
};