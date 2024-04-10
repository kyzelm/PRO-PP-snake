#include "InterfaceController.h"

InterfaceController* createInterfaceController() {
	InterfaceController* interfaceController = (InterfaceController*)malloc(sizeof(InterfaceController));
	interfaceController->gameState = 0;
	interfaceController->isPaused = 0;
	interfaceController->gameOverState = 0;
	interfaceController->snakeSpeed = 1.0;
	interfaceController->snakeLength = 2;
	interfaceController->snakeDirection = 0;
	interfaceController->isSnakeDirectionChanged = 0;
	interfaceController->menuSelection = 0;
	interfaceController->timerCounter = 0;
	strcpy(interfaceController->menu[0], "Graj");
	strcpy(interfaceController->menu[1], "Sterowanie");
	strcpy(interfaceController->menu[2], "Wyjdz");
	return interfaceController;
}

void destroyInterfaceController(InterfaceController* interfaceController) {
	free(interfaceController);
}