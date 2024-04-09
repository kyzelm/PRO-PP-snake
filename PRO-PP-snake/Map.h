#pragma once

typedef struct Map {
	int width, height;
	int apple[2];
	char mapTable[30][30];
} Map;

Map* createMap(int width, int height);
void updateMap(Map* map);
void destroyMap(Map* map);
void randomizeApple(Map* map);
void printMap(Map* map);