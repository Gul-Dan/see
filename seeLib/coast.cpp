#include "stdafx.h"
#include "coast.h"

Coast::Coast(const unsigned space)
	: spaceLimit(space)
{
	harbors.emplace(ContainerShip, std::vector<std::unique_ptr<Harbor>>());
	harbors.emplace(BulkCarrier, std::vector<std::unique_ptr<Harbor>>());
	harbors.emplace(TankerShip, std::vector<std::unique_ptr<Harbor>>());
	harbors.emplace(OffshoreVessel, std::vector<std::unique_ptr<Harbor>>());
	harbors.emplace(FishingVessel, std::vector<std::unique_ptr<Harbor>>());

	ships.emplace(ContainerShip, std::queue<int>());
	ships.emplace(BulkCarrier, std::queue<int>());
	ships.emplace(TankerShip, std::queue<int>());
	ships.emplace(OffshoreVessel, std::queue<int>());
	ships.emplace(FishingVessel, std::queue<int>());
}

void Coast::addHarbor(std::unique_ptr<Harbor> harbor)
{
	harbors.at(harbor->getType()).push_back(std::move(harbor));
}

bool Coast::addShip(const Ship& ship)
{
	std::lock_guard<std::mutex> guard(shipsMutex);
	if (hasSpace(ship.type))
	{
		ships.at(ship.type).push(ship.capacity);
		return true;
	}
	else
	{
		std::cout << "Can't add new ship - " << shipTypeToString(ship.type) << " queue is full!\n";
	}
	return false;
}

bool Coast::hasSpace(const ShipType& type) const
{
	return !(ships.at(type).size() == spaceLimit);
}

void Coast::startLoading(const Ship& ship, int harbor)
{
	deleteShip(ship.type);
	std::cout << "Start of loading " << shipTypeToString(ship.type) << ", capacity " << ship.capacity << "\n";
	harbors.at(ship.type)[harbor]->load(ship);
}

void Coast::deleteShip(const ShipType& type)
{
	std::lock_guard<std::mutex> guard(shipsMutex);
	auto& queue = ships.at(type);
	if (queue.size())
		queue.pop();
}

int Coast::findFreeHarbor(const ShipType& type) //todo: Can this function be const?
{
	std::lock_guard<std::mutex> guard(loadingMutex);
	for (size_t i = 0; i < harbors.at(type).size(); i++)
	{
		if (!harbors.at(type)[i]->isLoading())
		{
			harbors.at(type)[i]->setIsLoading();
			return static_cast<int>(i);
		}
	}
	std::cout << "Can't start loading " << shipTypeToString(type) << " - all harbors are busy!\n";
	return -1;
}