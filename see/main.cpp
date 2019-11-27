#include <chrono>
#include <thread>
#include <memory>
#include <iostream>
#include "ship.h"
#include "harbor.h"
#include "coast.h"
#include "tunnel.h"
#include "generator.h"

void createHarbors(ICoast& coast)
{
	coast.addHarbor(std::make_unique<Harbor>(ContainerShip));
	coast.addHarbor(std::make_unique<Harbor>(ContainerShip));
	coast.addHarbor(std::make_unique<Harbor>(BulkCarrier));
	coast.addHarbor(std::make_unique<Harbor>(BulkCarrier));
	coast.addHarbor(std::make_unique<Harbor>(BulkCarrier));
	coast.addHarbor(std::make_unique<Harbor>(TankerShip));
	coast.addHarbor(std::make_unique<Harbor>(TankerShip));
	coast.addHarbor(std::make_unique<Harbor>(OffshoreVessel));
	coast.addHarbor(std::make_unique<Harbor>(FishingVessel));
	coast.addHarbor(std::make_unique<Harbor>(FishingVessel));
}

void shipManager(ICoast& coast, ITunnel& tunnel)
{
	auto ship = tunnel.sendShip(coast);
	unsigned harbor;
	while ((harbor = coast.findFreeHarbor(ship.type)) == -1)
	{
		std::this_thread::sleep_for(std::chrono::seconds(10));
	}
	coast.startLoading(ship, harbor);
}

int main()
{
	Tunnel tunnel;
	Coast coast;
	createHarbors(coast);

	while (true)
	{
		if (tunnel.addShip(generate()))
		{
			std::cout << "Generated new ship! Starting ship manager...\n";
			std::thread manager(shipManager, std::ref(coast), std::ref(tunnel));
			manager.detach();
		}
		srand((unsigned)time(nullptr));
		int time = (rand() % 5 + 1); //from 1 to 5
		std::this_thread::sleep_for(std::chrono::seconds(time));
	}

	return 0;
}