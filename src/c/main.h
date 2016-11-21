#include <pebble.h>
#pragma once
Window *main_get_window();
void setAnswer(int questionNumber, int answer);
void force_back_button(Window *window, MenuLayer *menu_layer);