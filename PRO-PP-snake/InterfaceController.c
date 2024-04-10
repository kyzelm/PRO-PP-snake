#include "InterfaceController.h"

InterfaceController* createInterfaceController() {
	InterfaceController* interfaceController = (InterfaceController*)malloc(sizeof(InterfaceController));
	interfaceController->gameState = 0;
	interfaceController->isPaused = 0;
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
	strcpy(interfaceController->menu[1][0], "Easy");
	strcpy(interfaceController->menu[1][1], "Hard");
	strcpy(interfaceController->menu[1][2], "Back");
	return interfaceController;
}

void destroyInterfaceController(InterfaceController* interfaceController) {
	free(interfaceController);
}