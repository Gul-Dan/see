#include "stdafx.h"
#include <iostream>
#include "manager.h"
#include "generator.h"

const int sleepingTime = 3;

void shipManager(ICoast& coast, ITunnel& tunnel, int time)
{
	//todo: can be divided
	auto ship = tunnel.sendShip(coast);
	while (!ship.capacity)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(time));
		ship = tunnel.sendShip(coast);
	}
	unsigned harbor;
	while ((harbor = coast.findFreeHarbor(ship.type)) == -1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(time));
	}
	coast.startLoading(ship, harbor);
}

void generatorManager(ICoast& coast, ITunnel& tunnel)
{
	generatorManager(coast, tunnel, sleepingTime);
	int time = (rand() % 5 + 1) * 1;
	std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

void generatorManager(ICoast& coast, ITunnel& tunnel, int time)
{
	auto& ship = generate();
	while (!tunnel.addShip(ship))
	{	
		std::cout << "Generated new ship! Starting ship manager..." << shipTypeToString(ship.type) << "\n";
		std::thread manager(shipManager, std::ref(coast), std::ref(tunnel), time);
		manager.detach();
	}
}