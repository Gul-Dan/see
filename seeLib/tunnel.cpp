#include "stdafx.h"
#include "tunnel.h"

Tunnel::Tunnel(const unsigned space)
	: spaceLimit(space)
{
}

Ship Tunnel::sendShip(ICoast& coast)
{
	//todo
	std::lock_guard<std::mutex> guard(shipsMutex);
	Ship ship(ContainerShip, 0);
	if (ships.size())
	{
		if (coast.addShip(ships.front()))
		{
			ship = ships.front();
			ships.pop();
		}
	}
	return ship;
}

void Tunnel::addShip(const Ship& ship)
{
	std::lock_guard<std::mutex> guard(shipsMutex);
	ships.push(ship);
}

bool Tunnel::hasSpace() const
{
	//todo: should we add mutex ahead?
	return !(ships.size() == spaceLimit);
}