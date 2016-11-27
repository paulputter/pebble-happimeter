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
  unsigned int age;
} UserConfiguration;

// Define default userinfo values
static char *default_username = "unknown";
static char *default_email = "invalid@email.com";
static const int default_weight = 0;
static const int default_sportiness = 0;
static const int default_age = 0;

//create array for saving the answers
int userAnswers[3];