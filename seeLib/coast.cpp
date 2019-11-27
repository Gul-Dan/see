#include "stdafx.h"
#include "coast.h"

Coast::Coast()
{
	harbors.emplace(ContainerShip, std::vector<std::unique_ptr<Harbor>>());
	harbors.emplace(BulkCarrier, std::vector<std::unique_ptr<Harbor>>());
	harbors.emplace(TankerShip, std::vector<std::unique_ptr<Harbor>>());
	harbors.emplace(RoRoShip, std::vector<std::unique_ptr<Harbor>>());
	harbors.emplace(OffshoreVessel, std::vector<std::unique_ptr<Harbor>>());
	harbors.emplace(FishingVessel, std::vector<std::unique_ptr<Harbor>>());

	ships.emplace(ContainerShip, std::queue<int>());
	ships.emplace(BulkCarrier, std::queue<int>());
	ships.emplace(TankerShip, std::queue<int>());
	ships.emplace(RoRoShip, std::queue<int>());
	ships.emplace(OffshoreVessel, std::queue<int>());
	ships.emplace(FishingVessel, std::queue<int>());
}

void Coast::addHarbor(std::unique_ptr<Harbor> harbor)
{
	harbors.at(harbor->getType()).push_back(std::move(harbor));
}

bool Coast::addShip(const Ship& ship)
{
	std::lock_guard<std::mutex> guard(addShipMutex);
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
	std::cout << "Start of loading " << shipTypeToString(ship.type) << ", capacity " << ship.capacity << "\n";
	deleteShip(ship.type);
	harbors.at(ship.type)[harbor]->load(ship);
}

void Coast::deleteShip(const ShipType& type)
{
	ships.at(type).pop();
}

std::string Coast::shipTypeToString(const ShipType& type) const
{
	switch (type)
	{
	case 0:
		return "ContainerShip";
	case 1:
		return "BulkCarrier";
	case 2:
		return "TankerShip";
	case 3:
		return "RoRoShip";
	case 4:
		return "OffshoreVessel";
	case 5:
		return "FishingVessel";
	}
	return "";
}

int Coast::findFreeHarbor(const ShipType& type) const
{
	//todo: problem here. 2 threads can get same harbor
	int res = -1;
	for (size_t i = 0; i < harbors.at(type).size(); i++)
	{
		if (!harbors.at(type)[i]->isLoading())
		{
			res = i;
			break;
		}
	}
	return res;
}