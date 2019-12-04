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
		std::this_thread::sleep_for(std::chrono::seconds(time));
		ship = tunnel.sendShip(coast);
	}
	unsigned harbor;
	while ((harbor = coast.findFreeHarbor(ship.type)) == -1)
	{
		std::this_thread::sleep_for(std::chrono::seconds(time));
	}
	coast.startLoading(ship, harbor);
}

void generatorManager(ICoast& coast, ITunnel& tunnel)
{
	generatorManager(coast, tunnel, sleepingTime);
	int time = (rand() % 5 + 1) * 1;
	std::this_thread::sleep_for(std::chrono::seconds(time));
}

void generatorManager(ICoast& coast, ITunnel& tunnel, int time)
{
	if (tunnel.hasSpace())
	{
		tunnel.addShip(generate());
		std::cout << "Generated new ship! Starting ship manager...\n";
		std::thread manager(shipManager, std::ref(coast), std::ref(tunnel), time);
		manager.detach();
	}
	else
	{
		std::cout << "Can't add new ship - Tunnel queue is full!\n";
	}
}