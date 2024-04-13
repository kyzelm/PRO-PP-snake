/*****************************************************************//**
 * \file   InterfaceController.c
 * \brief  Main controller for the game states and menu
 *********************************************************************/

#include "InterfaceController.h"

/**
 * \brief Create a new interface controller
 * Function allocates memory for the InterfaceController structure and initializes starting values for the game state, pause state, mute game, game over state, snake speed, snake step, snake length, snake direction, timer counter, previous snake direction, menu mode and menu cursor. It also initializes the menu strings.
 * 
 * \return pointer to the created interface controller
 */
InterfaceController* createInterfaceController() {
	InterfaceController* interfaceController = (InterfaceController*)malloc(sizeof(InterfaceController));
	interfaceController->gameState = 0;
	interfaceController->isPaused = 0;
	interfaceController->isMuted = 0;
	interfaceController->gameOverState = 0;
	interfaceController->snakeSpeed = 1.0;
	interfaceController->snakeStep = 0.1;
	interfaceController->snakeLength = 3;
	interfaceController->snakeDirection = 0;
	interfaceController->timerCounter = 0;
	interfaceController->prevSnakeDirection = 0;
	interfaceController->menuMode = 0;
	interfaceController->menuCursor = 0;
	strcpy(interfaceController->menu[0][0], "Play");
	strcpy(interfaceController->menu[0][1], "Controls");
	strcpy(interfaceController->menu[0][2], "Exit");
	strcpy(interfaceController->menu[1][0], "Standard");
	strcpy(interfaceController->menu[1][1], "Asia Level");
	strcpy(interfaceController->menu[1][2], "Back");
	return interfaceController;
}

/**
 * \brief Delete the interface controller
 * Function frees memory allocated for the interface controller
 * 
 * \param interfaceController pointer to the interface controller to be deleted
 */
void destroyInterfaceController(InterfaceController* interfaceController) {
	free(interfaceController);
}