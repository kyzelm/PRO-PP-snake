/*****************************************************************//**
 * \file   Map.h
 * \brief  Map structure and functions declarations
 *********************************************************************/

#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

/**
 * \typedef Map
 * \brief Game map structure
 */
/**
 * \struct Map
 * \brief Game map structure
 * 
 * Structure represents the game map and its elements
 */
typedef struct Map {
	int width; /**< map width (in tiles) */
	int height; /**< map height (in tiles) */
	int apple[2]; /**< apple coordinates */
	int mapTable[30][30]; /**< map table of elements */
	float displayWidth; /**< ALLEGRO_DISPLAY instance width */
	float displayHeight; /**< ALLEGRO_DISPLAY instance height */
	ALLEGRO_BITMAP* boardImage; /**< board background image */
	ALLEGRO_BITMAP* appleImage; /**< apple image */
	ALLEGRO_BITMAP* snakeHeadImage; /**< snake head image */
	ALLEGRO_BITMAP* snakeTailImage; /**< snake tail image */
} Map;

Map* createMap(int width, int height, ALLEGRO_DISPLAY* display);
void randomizeApple(Map* map);
int updateMap(Map* map, int direction);
void printMap(Map* map, int direction);
void resetSnake(Map* map);
void destroyMap(Map* map);