#pragma once
#include <queue>
#include <mutex>
#include "coast.h"
#include "ship.h"

//stores generated ships
// todo: why from generator? - is it OK?
class ITunnel
{
public:
	//tries to send ship to Coast
	virtual Ship sendShip(ICoast&) = 0;
	//adds ship from generator
	virtual bool addShip(const Ship&) = 0;
	virtual bool hasSpace() const = 0;
};

class Tunnel : public ITunnel
{
	std::queue<Ship> ships;
	const unsigned spaceLimit;
	std::mutex sendShipMutex;
	std::mutex addShipMutex;
	//todo: test with 2 functions

public:
	Tunnel(const unsigned);
	Ship sendShip(ICoast&) override;
	bool addShip(const Ship&) override;
	bool hasSpace() const override;
};