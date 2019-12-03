#pragma once
#include <mutex>
#include <memory>
#include "ship.h"

//loads ships
class IHarbor
{
public:
	virtual ~IHarbor() {}
	virtual bool isLoading() const = 0;
	//creates thread that loads ship and detaches it
	virtual void load(const Ship& ship) = 0;
	virtual ShipType getType() const = 0;
	virtual void setIsLoading() = 0;
};

class Harbor : public IHarbor
{
	//todo: atomic object
	bool isLoading_;
	ShipType type;

	void setIsLoading(bool value);

public:
	Harbor(const ShipType& type);
	bool isLoading() const override;
	void load(const Ship& ship) override;
	ShipType getType() const override;
	void setIsLoading() override;
};