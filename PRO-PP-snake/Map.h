#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

typedef struct Map {
	int width, height;
	int apple[2];
	int mapTable[30][30];
	float displayWidth, displayHeight;
	ALLEGRO_BITMAP* boardImage;
	ALLEGRO_BITMAP* appleImage;
	ALLEGRO_BITMAP* snakeHeadImage;
	ALLEGRO_BITMAP* snakeTailImage;
} Map;

Map* createMap(int width, int height, ALLEGRO_DISPLAY* display);
void randomizeApple(Map* map);
int updateMap(Map* map, int direction);
void printMap(Map* map, int direction);
void resetSnake(Map* map);
void destroyMap(Map* map);