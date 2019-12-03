#include "stdafx.h"
#include "manager.h"
#include "generator.h"
#include "harbor.h"
#include "coast.h"
#include "tunnel.h"
#include "ship.h"

class CoastMock : public ICoast
{
public:
	CoastMock(const unsigned space)
		: ICoast(space)
	{
	}
	MOCK_METHOD1(addShip, bool(const Ship&));
	MOCK_CONST_METHOD1(hasSpace, bool(const ShipType&));
	MOCK_METHOD2(startLoading, void(const Ship&, int));
	MOCK_METHOD1(findFreeHarbor, int(const ShipType&));
	MOCK_METHOD1(deleteShip, void(const ShipType&));
	MOCK_METHOD1(addHarbor, void(std::unique_ptr<Harbor>));
};

static void createHarbors(ICoast& coast)
{
	coast.addHarbor(std::make_unique<Harbor>(ContainerShip));
	coast.addHarbor(std::make_unique<Harbor>(ContainerShip));
	coast.addHarbor(std::make_unique<Harbor>(BulkCarrier));
	coast.addHarbor(std::make_unique<Harbor>(TankerShip));
	coast.addHarbor(std::make_unique<Harbor>(TankerShip));
	coast.addHarbor(std::make_unique<Harbor>(OffshoreVessel));
	coast.addHarbor(std::make_unique<Harbor>(FishingVessel));
	coast.addHarbor(std::make_unique<Harbor>(FishingVessel));
}

static Ship generate()
{
	static int x = rand() % amountOfTypes;
	if (x == 4)
	{
		x = 0;
	}
	else
	{
		++x;
	}
	return Ship(static_cast<ShipType>(x), 1);
}

TEST(load, when_1000_ships_are_generated_then_no_exception)
{
	Tunnel tunnel(5);
	Coast coast(3);
	createHarbors(coast);
	int testNumber = 1000;

	for (int i = 0; i < testNumber; i++)
	{
		generatorManager(coast, tunnel, 0);
	}
	std::this_thread::sleep_for(std::chrono::seconds(44));
	
	SUCCEED();
}

void function1(Tunnel& tunnel)
{
	for (int i = 0; i < 100; i++)
	{
		tunnel.addShip(generate());
	}
}

void function2(Tunnel& tunnel, Coast& coast)
{
	for (int i = 0; i < 100; i++)
	{
		tunnel.sendShip(coast);
	}
}

TEST(mutex, WhenTwoFunctionsAreCalledImmediatelyThenNoException)
{
	Tunnel tunnel(5);
	Coast coast(3);
	createHarbors(coast);

	std::thread thread1(function1, std::ref(tunnel));
	std::thread thread2(function2, std::ref(tunnel), std::ref(coast));
	thread1.detach();
	thread2.detach();
	std::this_thread::sleep_for(std::chrono::seconds(3));

	SUCCEED();
}

TEST(Tunnel, when_sendShip_is_called_then_Coast_addShip_is_called_once)
{
	CoastMock coast(3);
	
	Tunnel tunnel(5);
	Ship ship(FishingVessel, 50);

	EXPECT_CALL(coast, addShip(testing::_))
		.Times(1);

	tunnel.addShip(ship);
	tunnel.sendShip(coast);
}

TEST(Tunnel, when_Tunnel_queue_is_full_then_addShip_returns_false)
{
	Tunnel tunnel(5);
	int spaceLimit = 5;
	for (int i = 0; i < spaceLimit; i++)
	{
		tunnel.addShip(Ship(ContainerShip, 50));
	}
	EXPECT_FALSE(tunnel.hasSpace());
}

TEST(Coast, when_addShip_deleteShip_addShip_then_no_exceptions_are_thrown)
{
	Coast coast(3);
	coast.addShip(Ship(ContainerShip, 50));
	coast.deleteShip(ContainerShip);
	EXPECT_NO_THROW(coast.addShip(Ship(ContainerShip, 80)));
}

TEST(Coast, when_there_is_free_harbor_then_findfreeHarbor_return_index_of_this_harbor)
{
	Coast coast(3);
	coast.addHarbor(std::make_unique<Harbor>(ContainerShip));
	coast.addShip(Ship(ContainerShip, 10));
	int index = coast.findFreeHarbor(ContainerShip);
	EXPECT_EQ(index, 0);
}

TEST(Coast, when_there_is_no_free_harbor_then_findfreeHarbor_return_minus_1)
{
	std::shared_ptr<Coast> coast = std::make_shared<Coast>(3);
	coast->addHarbor(std::make_unique<Harbor>(ContainerShip));
	Ship ship(ContainerShip, 10);
	coast->addShip(ship);
	coast->findFreeHarbor(ContainerShip);
	std::thread load(&Coast::startLoading, coast, ship, 0);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	load.detach();
	int index = coast->findFreeHarbor(ContainerShip);
	EXPECT_EQ(index, -1);
}

TEST(Coast, when_Coast_queue_is_full_then_addShip_returns_false)
{
	Coast coast(3);
	int spaceLimit = 3;
	for (int i = 0; i < spaceLimit; i++)
	{
		coast.addShip(Ship(ContainerShip, 50));
	}

	EXPECT_FALSE(coast.addShip(Ship(ContainerShip, 50)));
}

GTEST_API_ int main(int argc, char **argv) {
	printf("Running main() from %s\n", __FILE__);
	testing::InitGoogleMock(&argc, argv);
	auto rc = RUN_ALL_TESTS();
	system("pause");
	return rc;
}