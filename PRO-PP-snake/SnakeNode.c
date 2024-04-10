#include "SnakeNode.h";

#include <stdio.h>
#include <stdlib.h>

SnakeNode* newSnakeHead(SnakeNode* snakeHeadNode, int x, int y) {
	SnakeNode* newSnakeNode = (SnakeNode*)malloc(sizeof(SnakeNode));
	if (newSnakeNode == NULL) {
		return NULL;
	}
	newSnakeNode->x = x;
	newSnakeNode->y = y;
	newSnakeNode->next = snakeHeadNode;
	return newSnakeNode;
}

void deleteSnakeLastNode(SnakeNode* snakeHeadNode) {
	while (snakeHeadNode->next->next != NULL) {
		snakeHeadNode = snakeHeadNode->next;
	}
	free(snakeHeadNode->next);
	snakeHeadNode->next = NULL;
}

SnakeNode* deleteSnake(SnakeNode* snakeHeadNode) {
	while (snakeHeadNode != NULL) {
		SnakeNode* next = snakeHeadNode->next;
		free(snakeHeadNode);
		snakeHeadNode = next;
	}
	return NULL;
}