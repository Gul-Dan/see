// googletest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "generator.h"
#include "harbor.h"
#include "coast.h"
#include "tunnel.h"
#include "ship.h"

class CoastMock : public ICoast
{
public:
	MOCK_METHOD1(addShip, bool(const Ship&));
	MOCK_CONST_METHOD1(hasSpace, bool(const ShipType&));
	MOCK_METHOD2(startLoading, void(const Ship&, int));
	MOCK_CONST_METHOD1(findFreeHarbor, int(const ShipType&));
	MOCK_METHOD1(deleteShip, void(const ShipType&));
	MOCK_METHOD1(addHarbor, void(std::unique_ptr<Harbor>));
};

//todo: TEST(Harbor) TEST(Generator)
//TEST(Generator, check_that_different_ships_are_generated)


TEST(Tunnel, when_sendShip_is_called_then_Coast_addShip_is_called_once)
{
	CoastMock coast;
	
	Tunnel tunnel;
	Ship ship(FishingVessel, 50);

	EXPECT_CALL(coast, addShip(testing::_))
		.Times(1);

	tunnel.addShip(ship);
	tunnel.sendShip(coast);
}

TEST(Tunnel, when_Tunnel_queue_is_full_then_addShip_returns_false)
{
	Tunnel tunnel;
	int spaceLimit = 5;
	for (int i = 0; i < spaceLimit; i++)
	{
		tunnel.addShip(Ship(ContainerShip, 50));
	}
	EXPECT_FALSE(tunnel.hasSpace());
}

TEST(Coast, when_addShip_deleteShip_addShip_then_no_exceptions_are_thrown)
{
	Coast coast;
	coast.addShip(Ship(ContainerShip, 50));
	coast.deleteShip(ContainerShip);
	EXPECT_NO_THROW(coast.addShip(Ship(ContainerShip, 80)));
}

TEST(Coast, when_there_is_free_harbor_then_findfreeHarbor_return_index_of_this_harbor)
{
	Coast coast;
	coast.addHarbor(std::make_unique<Harbor>(ContainerShip));
	int index = coast.findFreeHarbor(ContainerShip);
	EXPECT_EQ(index, 0);
}

TEST(Coast, when_there_is_no_free_harbor_then_findfreeHarbor_return_minus_1)
{
	std::shared_ptr<Coast> coast = std::make_shared<Coast>();
	coast->addHarbor(std::make_unique<Harbor>(ContainerShip));
	Ship ship(ContainerShip, 10);
	coast->addShip(ship);
	std::thread load(&Coast::startLoading, coast, ship, 0);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	load.detach();
	int index = coast->findFreeHarbor(ContainerShip);
	EXPECT_EQ(index, -1);
}

TEST(Coast, when_Coast_queue_is_full_then_addShip_returns_false)
{
	Coast coast;
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