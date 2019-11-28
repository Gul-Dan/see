#include "stdafx.h"
#include "tunnel.h"

Ship Tunnel::sendShip(ICoast& coast)
{
	std::lock_guard<std::mutex> guard(sendShipMutex);
	Ship ship(ContainerShip, 0);
	std::this_thread::sleep_for(std::chrono::seconds(1));
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
	std::lock_guard<std::mutex> guard(addShipMutex);
	if (hasSpace())
	{
		ships.push(ship);
		return true;
	}
	else
	{
		std::cout << "Can't add new ship - Tunnel queue is full!\n";
	}
	return false;
}

bool Tunnel::hasSpace() const
{
	return !(ships.size() == spaceLimit);
}