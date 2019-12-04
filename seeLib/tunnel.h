#pragma once
#include <queue>
#include <mutex>
#include "coast.h"
#include "ship.h"

//stores generated ships
class ITunnel
{
public:
	//tries to send ship to Coast
	virtual Ship sendShip(ICoast&) = 0;
	//adds ship from generator
	virtual bool addShip(const Ship&) = 0;
};

class Tunnel : public ITunnel
{
	std::queue<Ship> ships;
	const unsigned spaceLimit;
	mutable std::mutex shipsMutex;

public:
	Tunnel(const unsigned);
	Ship sendShip(ICoast&) override;
	bool addShip(const Ship&) override;
};