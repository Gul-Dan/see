#pragma once
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <memory>
#include <mutex>
#include "harbor.h"
#include "ship.h"

typedef std::map<ShipType, std::vector<std::unique_ptr<Harbor>>> harborMap;
typedef std::map<ShipType, std::queue<int>> shipMap;

//control ship flow from tunnel to harbours
class ICoast
{
public:
	ICoast() {}
	ICoast(const unsigned) {}
	virtual ~ICoast() {}
	//add ship from tunnel to harbor queue 'ships'
	virtual bool addShip(const Ship&) = 0; 
	virtual bool hasSpace(const ShipType&) const = 0;
	//if harbor is free - send ship to it
	virtual void startLoading(const Ship&, int) = 0;//todo: what is int? why harbor is int but not a Harbor?
	//finds harbor that is not loading - return its index or -1 otherwise
	virtual int findFreeHarbor(const ShipType&) = 0;
	virtual void deleteShip(const ShipType&) = 0;
	virtual void addHarbor(std::unique_ptr<Harbor>) = 0;
};

class Coast : public ICoast
{
	shipMap ships;
	harborMap harbors;
	const unsigned spaceLimit;
	mutable std::mutex shipsMutex;
	std::mutex loadingMutex;

public:
	Coast(const unsigned);
	bool addShip(const Ship&) override;
	bool hasSpace(const ShipType&) const override;
	void startLoading(const Ship&, int) override;
	int findFreeHarbor(const ShipType&) override;
	void deleteShip(const ShipType&) override;
	void addHarbor(std::unique_ptr<Harbor>) override;
	//statistics? add starting information about harbors and maybe ships. maybe connect it with client
	//todo: statistics: new class + add in main into statistics array
};