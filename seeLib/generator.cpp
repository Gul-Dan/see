#include "stdafx.h"
#include "generator.h"

//generates random ships
Ship generate()
{
	srand((unsigned)time(nullptr));
	ShipType type = static_cast<ShipType>(rand() % 6); //from 0 to 5
	int capacity = (rand() % 10 + 1) * 10; //10, 20, 30, ..., 100

	return Ship(type, capacity);
}
