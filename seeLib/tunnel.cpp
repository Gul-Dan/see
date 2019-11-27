#include "stdafx.h"
#include "tunnel.h"

Ship Tunnel::sendShip(ICoast& coast)
{
	Ship ship = ships.front();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	if (ships.size())
	{
		if (coast.addShip(ship))
		{
			ships.pop();
		}
	}
	return ship;
}

bool Tunnel::addShip(const Ship& ship)
{
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