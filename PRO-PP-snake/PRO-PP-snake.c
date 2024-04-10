#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "Map.h"
#include "InterfaceController.h"

int main() {

	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_FONT* font = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;

	al_init();
	al_init_font_addon();
	al_init_ttf_addon();

	display = al_create_display(1200, 800);
	font = al_load_ttf_font("PixelifySans.ttf", 32, 0);
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 30.0);

	al_install_keyboard();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	InterfaceController* interfaceController = createInterfaceController();
	Map* map = createMap(25, 25);

	while (interfaceController->gameState != 4) {
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			interfaceController->gameState = 4;
		}
	
		if (event.type == ALLEGRO_EVENT_TIMER) {
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			if (interfaceController->gameState == 0)
				al_draw_text(font, al_map_rgb(255, 255, 255), 600, 400, ALLEGRO_ALIGN_CENTER, interfaceController->menu[interfaceController->menuSelection]);
			if (interfaceController->gameState == 1){
				al_draw_text(font, al_map_rgb(255, 255, 255), 600, 400, ALLEGRO_ALIGN_CENTER, "Sterowanie");
				al_draw_text(font, al_map_rgb(255, 255, 255), 600, 500, ALLEGRO_ALIGN_CENTER, "[Enter]");
			}
			if (interfaceController->gameState == 2) {
				al_draw_textf(font, al_map_rgb(255, 255, 255), 50, 50, 0, "%d", interfaceController->snakeLength);
				printMap(map, font);
				if (interfaceController->isPaused) {
					al_draw_text(font, al_map_rgb(255, 255, 255), 600, 400, ALLEGRO_ALIGN_CENTER, "Pauza");
				}
				else {
					interfaceController->timerCounter++;
					if (interfaceController->timerCounter > 20.0 / interfaceController->snakeSpeed) {
						int result = updateMap(map, interfaceController->snakeDirection);
						interfaceController->isSnakeDirectionChanged = 0;
						if (result == -1) {
							interfaceController->gameState = 3;
							interfaceController->gameOverState = 0;
						}
						else if (result == 1) {
							interfaceController->snakeLength++;
							if (interfaceController->snakeLength == map->width * map->height) {
								interfaceController->gameState = 3;
								interfaceController->gameOverState = 1;
							}
							if (interfaceController->snakeLength % 5 == 0)
								interfaceController->snakeSpeed += 0.2;
						}
						interfaceController->timerCounter = 0;
					}
				}
			}
			if (interfaceController->gameState == 3) {
				if (interfaceController->gameOverState == 0)
					al_draw_text(font, al_map_rgb(255, 255, 255), 600, 400, ALLEGRO_ALIGN_CENTER, "Koniec gry: przegrana");
				else if (interfaceController->gameOverState == 1)
					al_draw_text(font, al_map_rgb(255, 255, 255), 600, 400, ALLEGRO_ALIGN_CENTER, "Koniec gry: wygrana");
			}
		}

		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (interfaceController->gameState == 0) {
				switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_LEFT:
					if (interfaceController->menuSelection > 0)
						interfaceController->menuSelection = interfaceController->menuSelection - 1;
					break;
				case ALLEGRO_KEY_RIGHT:
					if (interfaceController->menuSelection < 2)
						interfaceController->menuSelection = interfaceController->menuSelection + 1;
					break;
				case ALLEGRO_KEY_ENTER:
					if (interfaceController->menuSelection == 0) {
						interfaceController->gameState = 2;
					}
					else if (interfaceController->menuSelection == 1) {
						interfaceController->gameState = 1;
					}
					else if (interfaceController->menuSelection == 2) {
						interfaceController->gameState = 4;
					}
					break;
				}
			}
			else if (interfaceController->gameState == 1) {
				switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_ENTER:
					interfaceController->gameState = 0;
					break;
				}
			}
			else if (interfaceController->gameState == 2) {
				switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					if (interfaceController->snakeDirection != 2 && !interfaceController->isSnakeDirectionChanged && !interfaceController->isPaused) {
						interfaceController->snakeDirection = 0;
						interfaceController->isSnakeDirectionChanged = 1;
					}
					break;
				case ALLEGRO_KEY_RIGHT:
					if (interfaceController->snakeDirection != 3 && !interfaceController->isSnakeDirectionChanged && !interfaceController->isPaused) {
						interfaceController->snakeDirection = 1;
						interfaceController->isSnakeDirectionChanged = 1;
					}
					break;
				case ALLEGRO_KEY_DOWN:
					if (interfaceController->snakeDirection != 0 && !interfaceController->isSnakeDirectionChanged && !interfaceController->isPaused) {
						interfaceController->snakeDirection = 2;
						interfaceController->isSnakeDirectionChanged = 1;
					}
					break;
				case ALLEGRO_KEY_LEFT:
					if (interfaceController->snakeDirection != 1 && !interfaceController->isSnakeDirectionChanged && !interfaceController->isPaused) {
						interfaceController->snakeDirection = 3;
						interfaceController->isSnakeDirectionChanged = 1;
					}
					break;
				case ALLEGRO_KEY_ESCAPE:
					interfaceController->isPaused = !interfaceController->isPaused;
					break;
				}
			}
			else if (interfaceController->gameState == 3) {
				switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_ENTER:
					interfaceController->snakeDirection = 0;
					interfaceController->snakeSpeed = 1.0;
					interfaceController->snakeLength = 1;
					interfaceController->timerCounter = 0;
					interfaceController->gameOverState = 0;
					interfaceController->isPaused = 0;
					interfaceController->gameState = 0;
					resetSnake(map);
					break;
				}
			}
		}
	}
	
	destroyInterfaceController(interfaceController);
	al_destroy_display(display);
	al_destroy_font(font);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_uninstall_keyboard();

	return 0;
}