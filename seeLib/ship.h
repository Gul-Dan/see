#pragma once

enum ShipType
{
	ContainerShip, BulkCarrier, TankerShip, OffshoreVessel, FishingVessel, AmountOfTypes
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

inline std::string shipTypeToString(const ShipType& type)
{
	switch (type)
	{
	case 0:
		return "ContainerShip";
	case 1:
		return "BulkCarrier";
	case 2:
		return "TankerShip";
	case 3:
		return "OffshoreVessel";
	case 4:
		return "FishingVessel";
	}
	return "";
}
