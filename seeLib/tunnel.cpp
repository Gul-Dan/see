#include "stdafx.h"
#include "tunnel.h"
#include <chrono>

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

bool Tunnel::addShip(const Ship& ship)
{
	std::lock_guard<std::mutex> guard(shipsMutex);
	bool hadSpace = ships.size() < spaceLimit;
	if (hadSpace)
		ships.push(ship);
	return hadSpace;
}
