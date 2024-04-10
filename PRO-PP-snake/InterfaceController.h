#pragma once

typedef struct InterfaceController {
	int gameState; // 0 = menu, 1 = controls, 2 = game, 3 = game over, 4 = exit
	int isPaused; // 0 = not paused, 1 = paused
	int gameOverState; // 0 = losa , 1 = win
	float snakeSpeed;
	int snakeLength;
	int snakeDirection; // 0 = up, 1 = right, 2 = down, 3 = left
	int isSnakeDirectionChanged;
	int timerCounter;
	//int menuType; // 0 = main, 1 = choose level
	int menuSelection; // 0 = play, 1 = controls, 2 = exit
	char menu[3][12];
} InterfaceController;

InterfaceController* createInterfaceController();
void destroyInterfaceController(InterfaceController* interfaceController);