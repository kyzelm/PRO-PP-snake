#pragma once

#include <allegro5/allegro_font.h>

typedef struct Map {
	int width, height;
	int apple[2];
	int mapTable[30][30];
} Map;

Map* createMap(int width, int height);
void randomizeApple(Map* map);
int updateMap(Map* map, int direction);
void printMap(Map* map, ALLEGRO_FONT* font);
void resetSnake(Map* map);