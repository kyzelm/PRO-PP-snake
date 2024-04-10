#pragma once

typedef struct SnakeNode {
	int x, y;
	struct SnakeNode* next;
} SnakeNode;

SnakeNode* newSnakeHead(SnakeNode* snakeHeadNode, int x, int y);
void deleteSnakeLastNode(SnakeNode* snakeHeadNode);
SnakeNode* deleteSnake(SnakeNode* snakeHeadNode);