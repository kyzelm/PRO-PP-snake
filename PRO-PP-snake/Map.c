#include "Map.h"
#include "SnakeNode.h"

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_font.h>


SnakeNode* snakeHead = NULL;

Map* createMap(int width, int height) {
	Map* map = (Map*)malloc(sizeof(Map));
	if (map == NULL) {
		return NULL;
	}
	map->width = width;
	map->height = height;
	map->apple[0] = -1;
	map->apple[1] = -1;

	snakeHead = newSnakeHead(snakeHead, width / 2, height / 2);

	randomizeApple(map);
	updateMap(map, 0);

	return map;
}

void randomizeApple(Map* map) {
	map->apple[0] = rand() % map->width;
	map->apple[1] = rand() % map->height;
}

int updateMap(Map* map, int direction) {
	for (int y = 0; y < map->height; y++) {
		for (int x = 0; x < map->width; x++) {
			map->mapTable[y][x] = 0;
		}
	}

	if (snakeHead == NULL) {
		return -2;
	}
	
	SnakeNode* currentSnakeNode = snakeHead;
	while (currentSnakeNode != NULL) {
		map->mapTable[currentSnakeNode->y][currentSnakeNode->x] = 2;
		currentSnakeNode = currentSnakeNode->next;
	}
	
	if (map->apple[0] != -1 && map->apple[1] != -1) {
		map->mapTable[map->apple[1]][map->apple[0]] = 10;
	}

	switch (direction) {
	case 0:
		snakeHead = newSnakeHead(snakeHead, snakeHead->x, snakeHead->y - 1);
		break;
	case 1:
		snakeHead = newSnakeHead(snakeHead, snakeHead->x + 1, snakeHead->y);
		break;
	case 2:
		snakeHead = newSnakeHead(snakeHead, snakeHead->x, snakeHead->y + 1);
		break;
	case 3:
		snakeHead = newSnakeHead(snakeHead, snakeHead->x - 1, snakeHead->y);
		break;
	default:
		break;
	}

	if (map->mapTable[snakeHead->y][snakeHead->x] == 2) {
		return -1; // snake ate itself
	}

	map->mapTable[snakeHead->y][snakeHead->x] = 1;

	if (snakeHead->x == map->apple[0] && snakeHead->y == map->apple[1]) {
		do
			randomizeApple(map);
		while (map->mapTable[map->apple[1]][map->apple[0]] != 0);
		return 1; // apple eaten
	} 
	else if(snakeHead->x < 0 || snakeHead->x >= map->width || snakeHead->y < 0 || snakeHead->y >= map->height){
		return -1; // out of bounds
	}
	else {
		deleteSnakeLastNode(snakeHead);
		return 0; // nothing happened
	}
}

void printMap(Map* map, ALLEGRO_FONT* font) {
	for (int y = 0; y < map->height; y++) {
		for (int x = 0; x < map->width; x++) {
			char character = ' ';
			switch (map->mapTable[y][x]) {
			case 0:
				character = '.';
				break;
			case 1:
				character = 'O';
				break;
			case 2:
				character = 'o';
				break;
			case 10:
				character = 'X';
				break;
			default:
				break;
			}
			al_draw_textf(font, al_map_rgb(255, 255, 255), (1200.0 / 2.0 - 30.0 * map->width / 2.0) + 30 * x, (800.0 / 2.0 - 30.0 * map->height / 2.0) + 30 * y, ALLEGRO_ALIGN_CENTER, "%c", character);
		}
		printf("\n");
	}
}

void resetSnake(Map* map) {
	snakeHead = deleteSnake(snakeHead);
	snakeHead = newSnakeHead(snakeHead, map->width / 2, map->height / 2);

	randomizeApple(map);
	updateMap(map, 0);
}