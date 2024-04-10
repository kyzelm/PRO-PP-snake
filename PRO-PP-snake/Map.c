#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "Utils.h"

#include "Map.h"
#include "SnakeNode.h"

SnakeNode* snakeHead = NULL;

Map* createMap(int width, int height, ALLEGRO_DISPLAY* display) {
	Map* map = (Map*)malloc(sizeof(Map));
	if (map == NULL) {
		return NULL;
	}
	map->width = width;
	map->height = height;
	map->displayWidth = al_get_display_width(display);
	map->displayHeight = al_get_display_height(display);
	map->apple[0] = -1;
	map->apple[1] = -1;
	map->boardImage = al_load_bitmap("board.png");
	map->appleImage = al_load_bitmap("apple.png");
	map->snakeHeadImage = al_load_bitmap("snake-head.png");
	map->snakeTailImage = al_load_bitmap("snake-tail.png");

	snakeHead = newSnakeHead(snakeHead, width / 2, height / 2 + 1);
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

void printMap(Map* map, int direction) {
	al_draw_bitmap(map->boardImage, map->displayWidth / 2 - 380, map->displayHeight / 2 - 240, 0);

	for (int y = 0; y < map->height; y++) {
		for (int x = 0; x < map->width; x++) {
			switch (map->mapTable[y][x]) {
			case 0:
				break;
			case 1:
				al_draw_rotated_bitmap(map->snakeHeadImage, 18, 18, map->displayWidth / 2 - 320 + x * 40, map->displayHeight / 2 - 180 + y * 40, direction * 1.5708, 0);
				break;
			case 2:
				al_draw_bitmap(map->snakeTailImage, map->displayWidth / 2 - 338 + x * 40, map->displayHeight / 2 - 198 + y * 40, 0);
				break;
			case 10:
				al_draw_bitmap(map->appleImage, map->displayWidth / 2 - 338 + x * 40, map->displayHeight / 2 - 198 + y * 40, 0);
				break;
			default:
				break;
			}
		}
		printf("\n");
	}
}

void resetSnake(Map* map) {
	snakeHead = deleteSnake(snakeHead);
	snakeHead = newSnakeHead(snakeHead, map->width / 2, map->height / 2 + 1);
	snakeHead = newSnakeHead(snakeHead, map->width / 2, map->height / 2);

	randomizeApple(map);
	updateMap(map, 0);
}

void destroyMap(Map* map) {
	al_destroy_bitmap(map->appleImage);
	al_destroy_bitmap(map->snakeHeadImage);
	al_destroy_bitmap(map->snakeTailImage);
	free(map);
	snakeHead = deleteSnake(snakeHead);
}