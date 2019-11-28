#include "stdafx.h"
#include "generator.h"

//generates random ships
Ship generate()
{
	srand((unsigned)time(nullptr));
	//todo: what is 5? What if ShipType will be increased?
	ShipType type = static_cast<ShipType>(rand() % 5); //from 0 to 4
	int capacity = (rand() % 10 + 1) * 10; //10, 20, 30, ..., 100

	return Ship(type, capacity);
}
