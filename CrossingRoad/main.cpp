#include <iostream>
#include "CrossingRoad.h"

int main() {
	CrossingRoad CrossyRoad;
	srand(time(NULL));

	CrossyRoad.Init();
	CrossyRoad.Start();

	return 0;
}