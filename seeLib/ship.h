#pragma once

const unsigned short amoutOfTypes = 6;

enum ShipType
{
	ContainerShip, BulkCarrier, TankerShip, RoRoShip, OffshoreVessel, FishingVessel
};

struct Ship
{
	Ship(ShipType type, unsigned int capacity)
		: type(type),
		capacity(capacity)
	{
	}
	int capacity;
	ShipType type;
};