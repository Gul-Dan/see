#pragma once
#include <queue>
#include <mutex>
#include "coast.h"
#include "ship.h"

//stores ships from generator
// todo: why from generator?
class ITunnel
{
public:
	virtual Ship sendShip(ICoast&) = 0; //tries to send ship to Coast
	virtual bool addShip(const Ship&) = 0; //adds ship from generator
	virtual bool hasSpace() const = 0;
};

class Tunnel : public ITunnel
{
	std::queue<Ship> ships;
	const unsigned short spaceLimit = 5; // todo: why it's not parametrized

public:
	Ship sendShip(ICoast&) override;
	bool addShip(const Ship&) override;
	bool hasSpace() const override;
};