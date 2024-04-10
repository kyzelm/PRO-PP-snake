#pragma once

typedef struct InterfaceController {
	int gameState; // 0 = menu, 1 = controls, 2 = game, 3 = game over, 4 = exit
	int isPaused; // 0 = not paused, 1 = paused
	int gameOverState; // 0 = losa , 1 = win
	float snakeSpeed;
	float snakeStep;
	int snakeLength;
	int snakeDirection; // 0 = up, 1 = right, 2 = down, 3 = left
	int prevSnakeDirection; // 0 = up, 1 = right, 2 = down, 3 = left
	int timerCounter;
	int menuMode; // 0 = main, 1 = choose level, 2 = pause
	int menuCursor; // 0 = play, 1 = controls, 2 = exit
	char menu[3][3][10]; // 1st dimension = menuType, 2nd dimension = menuSelection, 3rd dimension = string length
} InterfaceController;

InterfaceController* createInterfaceController();
void destroyInterfaceController(InterfaceController* interfaceController);