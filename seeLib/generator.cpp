#include "stdafx.h"
#include "generator.h"

//generates random ships
Ship generate()
{
	ShipType type = static_cast<ShipType>(rand() % amountOfTypes); //from 0 to 4
	int capacity = (rand() % 5 + 1) * 3;

	return Ship(type, capacity);
}

void createHarbors(ICoast& coast)
{
	coast.addHarbor(std::make_unique<Harbor>(ContainerShip));
	coast.addHarbor(std::make_unique<Harbor>(ContainerShip));
	coast.addHarbor(std::make_unique<Harbor>(BulkCarrier));
	coast.addHarbor(std::make_unique<Harbor>(TankerShip));
	coast.addHarbor(std::make_unique<Harbor>(TankerShip));
	coast.addHarbor(std::make_unique<Harbor>(OffshoreVessel));
	coast.addHarbor(std::make_unique<Harbor>(FishingVessel));
	coast.addHarbor(std::make_unique<Harbor>(FishingVessel));
}