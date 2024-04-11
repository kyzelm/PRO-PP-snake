#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "Utils.h"

#include "Map.h"
#include "InterfaceController.h"

int main() {

	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_FONT* hugeFont = NULL, * font = NULL, * mediumFont = NULL, * smallFont = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_TIMER* timer = NULL;
	ALLEGRO_BITMAP* background = NULL, * title = NULL;

	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();

	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	al_set_window_title(display, "Snake");
	al_set_display_icon(display, al_load_bitmap("apple.png"));

	background = al_load_bitmap("main-background.png");
	title = al_load_bitmap("title.png");
	hugeFont = al_load_ttf_font("Silkscreen-Regular.ttf", 128, 0);
	font = al_load_ttf_font("Silkscreen-Regular.ttf", 64, 0);
	mediumFont = al_load_ttf_font("Silkscreen-Regular.ttf", 48, 0);
	smallFont = al_load_ttf_font("Silkscreen-Regular.ttf", 32, 0);

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60.0);

	al_install_keyboard();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	srand((unsigned int)time(NULL));
	al_start_timer(timer);

	InterfaceController* interfaceController = createInterfaceController();
	Map* map = createMap(19, 14, display);

	while (interfaceController->gameState != 4) {
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			interfaceController->gameState = 4;
		}
	
		if (event.type == ALLEGRO_EVENT_TIMER) {
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, al_get_display_width(display), al_get_display_height(display), 0);
			
			if (interfaceController->gameState == 0) {
				al_draw_bitmap(title, al_get_display_width(display) / 2.0 - al_get_bitmap_width(title) / 2.0, 150, 0);
				for (int i = 0; i < 3; i++) {
					if (interfaceController->menuCursor == i) 
						al_draw_textf(font, al_map_rgb(240, 240, 240), al_get_display_width(display) / 2.0, al_get_display_height(display) / 2.0 - 20 + 150 * i, ALLEGRO_ALIGN_CENTER, "> %s <", interfaceController->menu[interfaceController->menuMode][i]);
					else
						al_draw_textf(font, al_map_rgb(240, 240, 240), al_get_display_width(display) / 2.0, al_get_display_height(display) / 2.0 - 20 + 150 * i, ALLEGRO_ALIGN_CENTER, interfaceController->menu[interfaceController->menuMode][i]);
				}
			}

			else if (interfaceController->gameState == 1){
				al_draw_text(mediumFont, al_map_rgb(240, 240, 240), SCREEN_PADDING_SIDE, SCREEN_PADDING_TOP, ALLEGRO_ALIGN_LEFT, "Back");
				al_draw_text(smallFont, al_map_rgb(240, 240, 240), SCREEN_PADDING_SIDE, SCREEN_PADDING_TOP + 50, ALLEGRO_ALIGN_LEFT, "[ESC]");
				al_draw_text(mediumFont, al_map_rgb(240, 240, 240), al_get_display_width(display) / 2.0 - 500, al_get_display_height(display) / 2.0 - 150, ALLEGRO_ALIGN_LEFT, "Arrows / WASD");
				al_draw_text(mediumFont, al_map_rgb(240, 240, 240), al_get_display_width(display) / 2.0 + 500, al_get_display_height(display) / 2.0 - 150, ALLEGRO_ALIGN_RIGHT, "Movement");
				al_draw_text(mediumFont, al_map_rgb(240, 240, 240), al_get_display_width(display) / 2.0 - 500, al_get_display_height(display) / 2.0 - 50, ALLEGRO_ALIGN_LEFT, "ESC");
				al_draw_text(mediumFont, al_map_rgb(240, 240, 240), al_get_display_width(display) / 2.0 + 500, al_get_display_height(display) / 2.0 - 50, ALLEGRO_ALIGN_RIGHT, "Pause / Play");
				al_draw_text(mediumFont, al_map_rgb(240, 240, 240), al_get_display_width(display) / 2.0 - 500, al_get_display_height(display) / 2.0 + 50, ALLEGRO_ALIGN_LEFT, "R");
				al_draw_text(mediumFont, al_map_rgb(240, 240, 240), al_get_display_width(display) / 2.0 + 500, al_get_display_height(display) / 2.0 + 50, ALLEGRO_ALIGN_RIGHT, "Exit game (on pause)");
				al_draw_text(mediumFont, al_map_rgb(240, 240, 240), al_get_display_width(display) / 2.0 - 500, al_get_display_height(display) / 2.0 + 150, ALLEGRO_ALIGN_LEFT, "Enter");
				al_draw_text(mediumFont, al_map_rgb(240, 240, 240), al_get_display_width(display) / 2.0 + 500, al_get_display_height(display) / 2.0 + 150, ALLEGRO_ALIGN_RIGHT, "Accept");
			}
			
			else if (interfaceController->gameState == 2) {
				if (!interfaceController->isPaused) {
					al_get_keyboard_state(&keyState);
					if ((al_key_down(&keyState, ALLEGRO_KEY_LEFT) || al_key_down(&keyState, ALLEGRO_KEY_A)) && interfaceController->prevSnakeDirection != 1) {
						interfaceController->snakeDirection = 3;
					}
					else if ((al_key_down(&keyState, ALLEGRO_KEY_UP) || al_key_down(&keyState, ALLEGRO_KEY_W)) && interfaceController->prevSnakeDirection != 2) {
						interfaceController->snakeDirection = 0;
					}
					else if ((al_key_down(&keyState, ALLEGRO_KEY_RIGHT) || al_key_down(&keyState, ALLEGRO_KEY_D)) && interfaceController->prevSnakeDirection != 3) {
						interfaceController->snakeDirection = 1;
					}
					else if ((al_key_down(&keyState, ALLEGRO_KEY_DOWN) || al_key_down(&keyState, ALLEGRO_KEY_S)) && interfaceController->prevSnakeDirection != 0) {
						interfaceController->snakeDirection = 2;
					}
				}

				al_draw_text(mediumFont, al_map_rgb(240, 240, 240), SCREEN_PADDING_SIDE, SCREEN_PADDING_TOP, ALLEGRO_ALIGN_LEFT, (interfaceController->isPaused) ? "Play" : "Pause");
				al_draw_text(smallFont, al_map_rgb(240, 240, 240), SCREEN_PADDING_SIDE, SCREEN_PADDING_TOP + 50, ALLEGRO_ALIGN_LEFT, "[ESC]");
				if (interfaceController->isPaused){
					al_draw_text(mediumFont, al_map_rgb(240, 240, 240), al_get_display_width(display) - SCREEN_PADDING_SIDE, SCREEN_PADDING_TOP, ALLEGRO_ALIGN_RIGHT, "Exit game");
					al_draw_text(smallFont, al_map_rgb(240, 240, 240), al_get_display_width(display) - SCREEN_PADDING_SIDE, SCREEN_PADDING_TOP + 50, ALLEGRO_ALIGN_RIGHT, "[R]");
				}
				al_draw_textf(font, al_map_rgb(144, 144, 144), al_get_display_width(display) / 2.0, 100, ALLEGRO_ALIGN_CENTER, "Score: %d", interfaceController->snakeLength - 3);
				printMap(map, interfaceController->prevSnakeDirection);

				if (!interfaceController->isPaused) {
					interfaceController->timerCounter++;
					if (interfaceController->timerCounter > 20.0 / interfaceController->snakeSpeed) {
						int result = updateMap(map, interfaceController->snakeDirection);
						interfaceController->prevSnakeDirection = interfaceController->snakeDirection;
						if (result == -1) {
							interfaceController->gameState = 3;
							interfaceController->gameOverState = 0;
						}
						else if (result == 1) {
							interfaceController->snakeLength++;
							if (interfaceController->snakeLength >= map->width * map->height) {
								interfaceController->gameState = 3;
								interfaceController->gameOverState = 1;
							}
							if (interfaceController->snakeLength % 10 == 0)
								interfaceController->snakeSpeed += interfaceController->snakeStep;
						}
						interfaceController->timerCounter = 0;
					}
				}
			}
			
			else if (interfaceController->gameState == 3) {
				al_draw_text(mediumFont, al_map_rgb(240, 240, 240), SCREEN_PADDING_SIDE, SCREEN_PADDING_TOP, ALLEGRO_ALIGN_LEFT, "Menu");
				al_draw_text(smallFont, al_map_rgb(240, 240, 240), SCREEN_PADDING_SIDE, SCREEN_PADDING_TOP + 50, ALLEGRO_ALIGN_LEFT, "[ENTER]");
				al_draw_text(hugeFont, al_map_rgb(240, 240, 240), al_get_display_width(display) / 2.0, al_get_display_height(display) / 2.0 - 150, ALLEGRO_ALIGN_CENTER, interfaceController->gameOverState == 0 ? "You Lose!" : "You Win!");
				al_draw_textf(mediumFont, al_map_rgb(144, 144, 144), al_get_display_width(display) / 2.0, al_get_display_height(display) / 2.0 + 50, ALLEGRO_ALIGN_CENTER, "> Score: %d <", interfaceController->snakeLength - 3);
			}
		}

		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (interfaceController->gameState == 0) {
				switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
				case ALLEGRO_KEY_W:
					if (interfaceController->menuCursor > 0) interfaceController->menuCursor = interfaceController->menuCursor - 1;
					break;

				case ALLEGRO_KEY_DOWN:
				case ALLEGRO_KEY_S:
					if (interfaceController->menuCursor < 2) interfaceController->menuCursor = interfaceController->menuCursor + 1;
					break;

				case ALLEGRO_KEY_ENTER:
					switch (interfaceController->menuMode) {
					case 0:
						switch (interfaceController->menuCursor) {
						case 0:
							interfaceController->menuMode = 1;
							break;
						case 1:
							interfaceController->gameState = 1;
							break;
						case 2:
							interfaceController->gameState = 4;
							break;
						}
						break;

					case 1:
						interfaceController->snakeDirection = 0;
						interfaceController->prevSnakeDirection = 0;
						interfaceController->snakeLength = 3;
						interfaceController->timerCounter = 0;
						interfaceController->gameOverState = 0;
						interfaceController->isPaused = 0;
						resetSnake(map);

						switch (interfaceController->menuCursor) {
						case 0:
							interfaceController->snakeSpeed = 1.0;
							interfaceController->snakeStep = 0.1;
							interfaceController->gameState = 2;
							break;
						case 1:
							interfaceController->snakeSpeed = 2.0;
							interfaceController->snakeStep = 0.05;
							interfaceController->gameState = 2;
							break;
						case 2:
							break;
						}
						
						interfaceController->menuMode = 0;
						break;
					}

					interfaceController->menuCursor = 0;
					break;

				case ALLEGRO_KEY_ESCAPE:
					if (interfaceController->menuMode == 1) {
						interfaceController->menuCursor = 0;
						interfaceController->menuMode = 0;
					}
					break;
				}
			}
			
			else if (interfaceController->gameState == 1) {
				switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_ESCAPE:
					interfaceController->gameState = 0;
					break;
				}
			}
			
			else if (interfaceController->gameState == 2) {
				if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) interfaceController->isPaused = !interfaceController->isPaused;
				if(event.keyboard.keycode == ALLEGRO_KEY_R) interfaceController->gameState = 0;
			}
			
			else if (interfaceController->gameState == 3) {
				if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
					interfaceController->gameState = 0;
				}
			}
		}
	}
	
	destroyMap(map);
	destroyInterfaceController(interfaceController);
	al_destroy_bitmap(background);
	al_destroy_display(display);
	al_destroy_font(font);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_uninstall_keyboard();

	return 0;
}