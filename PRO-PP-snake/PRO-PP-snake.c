#include <stdio.h>
#include <stdlib.h>

#include "Map.h";

int main() {
	Map* map = createMap(11, 11);
	randomizeApple(map);
	updateMap(map);
	printMap(map);
	destroyMap(map);

	return 0;
}