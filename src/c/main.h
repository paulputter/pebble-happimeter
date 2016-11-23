#include <pebble.h>
#pragma once
Window *main_get_window();
void setAnswer(int questionNumber, int answer);
void force_back_button(Window *window, MenuLayer *menu_layer);

// Define our user configuration struct
 typedef struct UserConfiguration {
  char *username;
  char *email;
  unsigned int weight;
  unsigned int sportiness;
} UserConfiguration;

//create array for saving the answers
int userAnswers[3];