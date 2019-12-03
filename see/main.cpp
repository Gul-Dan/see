#include <chrono>
#include <thread>
#include <memory>
#include <iostream>
#include "ship.h"
#include "harbor.h"
#include "coast.h"
#include "tunnel.h"
#include "generator.h"
#include "manager.h"

int main()
{
	Tunnel tunnel(5);
	Coast coast(3);
	createHarbors(coast);

	srand((unsigned)time(nullptr));

	while (true)
	{
		generatorManager(coast, tunnel);
	}

	return 0;
}