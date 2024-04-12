/*****************************************************************//**
 * \file   InterfaceController.h
 * \brief  Interface states controller structure and functions declarations
 * 
 * \author Damian Osiñski
 * \date   April 2024
 *********************************************************************/

#pragma once

/**
 * \typedef InterfaceController
 * \brief Interface states controller structure
 */
/**
 * \struct InterfaceController
 * \brief Interface states controller structure
 * 
 * Structure contains all the necessary variables to control the game state and the game interface
 */
typedef struct InterfaceController {
	int gameState; /**< Main state determining what part of the game is currently displayed (0 - menu, 1 - controls, 2 - game, 3 - game over) */
	int isPaused; /**< Flag determining if the game is paused (0 - not paused, 1 - paused) */
	int gameOverState; /**< State determining what type of game over screen is displayed (0 - lose, 1 - win) */
	float snakeSpeed; /**< Timer tick multiplier determining the count of ticks between snake moves */
	float snakeStep; /**< Snake speed value modifier */
	int snakeLength; /**< Snake length */
	int snakeDirection; /**< Snake actual direction (0 - up, 1 - right, 2 - down, 3 - left) */
	int prevSnakeDirection; /**< Snake direction from the previous move (0 - up, 1 - right, 2 - down, 3 - left) */
	int timerCounter; /**< Timer counter allowing to control the game speed */
	int menuMode; /**< Menu state determining which menu is currently displayed (0 - main menu, 1 - controls menu) */
	int menuCursor; /**< Menu cursor position (0 - first option, 1 - second option, 2 - third option) */
	char menu[2][3][10]; /**< Menu options table (2 menus, 3 options in each menu, maximum 10 characters in each option) */
} InterfaceController;

InterfaceController* createInterfaceController();
void destroyInterfaceController(InterfaceController* interfaceController);