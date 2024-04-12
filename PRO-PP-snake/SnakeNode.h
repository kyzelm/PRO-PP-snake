/*****************************************************************//**
 * \file   SnakeNode.h
 * \brief  Snake node element structure and functions declarations
 * 
 * \author Damian Osiñski
 * \date   April 2024
 *********************************************************************/

#pragma once

/**
 * \typedef SnakeNode
 * \brief Snake node element structure
 */
/**
 * \struct SnakeNode
 * \brief Snake node element structure
 * 
 * Structure represents a single node element of the snake
 */
typedef struct SnakeNode {
	int x; /**< x coordinate */
	int y; /**< y coordinate */
	struct SnakeNode* next; /**< pointer to the next node */
} SnakeNode;

SnakeNode* newSnakeHead(SnakeNode* snakeHeadNode, int x, int y);
void deleteSnakeLastNode(SnakeNode* snakeHeadNode);
SnakeNode* deleteSnake(SnakeNode* snakeHeadNode);