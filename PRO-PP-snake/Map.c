#include "Map.h"
#include "SnakeNode.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

	SnakeNode* newSnakeNode = (SnakeNode*)malloc(sizeof(SnakeNode));
	if (newSnakeNode == NULL) {
		return NULL;
	}
	newSnakeNode->x = width / 2;
	newSnakeNode->y = height / 2;
	newSnakeNode->next = NULL;
	snakeHead = newSnakeNode;

	return map;
}

void updateMap(Map* map) {
	for (int y = 0; y < map->height; y++) {
		for (int x = 0; x < map->width; x++) {
			map->mapTable[y][x] = '.';
		}
	}
	SnakeNode* currentSnakeNode = snakeHead;
	map->mapTable[currentSnakeNode->y][currentSnakeNode->x] = 'H';
	currentSnakeNode = currentSnakeNode->next;
	while (currentSnakeNode != NULL) {
		map->mapTable[currentSnakeNode->y][currentSnakeNode->x] = 'O';
		currentSnakeNode = currentSnakeNode->next;
	}
	if (map->apple[0] != -1 && map->apple[1] != -1) {
		map->mapTable[map->apple[1]][map->apple[0]] = 'A';
	}
}

void destroyMap(Map* map) {
	free(map);
}

void randomizeApple(Map* map) {
	srand((unsigned int)time(NULL));
	map->apple[0] = rand() % map->width;
	map->apple[1] = rand() % map->height;
}

void printMap(Map* map) {
	for (int y = 0; y < map->height; y++) {
		for (int x = 0; x < map->width; x++) {
			printf("%c ", map->mapTable[y][x]);
		}
		printf("\n");
	}
}