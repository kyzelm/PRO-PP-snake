/*****************************************************************//**
 * \file   SnakeNode.c
 * \brief  Snake movement simulation and memory management functions
 * 
 * \author Damian Osiñski
 * \date   April 2024
 *********************************************************************/

#include "SnakeNode.h";

#include <stdio.h>
#include <stdlib.h>

/**
 * \brief Add new head node element to the snake
 *	Function creates new head node element of the snake with given coordinates x and y and returns it to simulate movement of the snake
 * 
 * \param snakeHeadNode previos head node element pointer of the snake
 * \param x first coordinate of the snake
 * \param y second coordinate of the snake
 * \return pointer to the new head node element of the snake
 */
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

/**
 * \brief Delete last node element of the snake
 * Function deletes last node element of the snake to coordinate the snake movement with newSankeHead function
 * 
 * \param snakeHeadNode head node element pointer of the snake
 */
void deleteSnakeLastNode(SnakeNode* snakeHeadNode) {
	while (snakeHeadNode->next->next != NULL) {
		snakeHeadNode = snakeHeadNode->next;
	}
	free(snakeHeadNode->next);
	snakeHeadNode->next = NULL;
}

/**
 * \brief Delete all node elements of the snake
 * Function deletes all node elements of the snake to free memory and allow to start new game
 * 
 * \param snakeHeadNode head node element pointer of the snake
 * \return NULL to set snakeHeadNode to NULL
 */
SnakeNode* deleteSnake(SnakeNode* snakeHeadNode) {
	while (snakeHeadNode != NULL) {
		SnakeNode* next = snakeHeadNode->next;
		free(snakeHeadNode);
		snakeHeadNode = next;
	}
	return NULL;
}