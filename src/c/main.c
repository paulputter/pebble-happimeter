#include <pebble.h>
#include "splash_window.h"
#include "main_window.h"
#include "src/c/main.h"
#include "sportquestion_window.h"
#include "whoyouwith_window.h"
#include "wakeup.h"
#include "exit_window.h"
#include "src/c/uploader.h"
#include "src/c/tree_window.h"
// Persistent storage key
#define SETTINGS_KEY 1

// An instance of the struct
static UserConfiguration config;

// Initialize the default settings
static void prv_default_settings() {
  config.username = "unknown";
  config.email = "invalid@email.com";
  config.weight = 0;
  config.sportiness = 0;
  // TODO: ADD birthdate
}

// Read settings from persistent storage
static void prv_load_settings() {
  // Load the default settings
  prv_default_settings();
  // Read settings from persistent storage, if they exist
  persist_read_data(SETTINGS_KEY, &config, sizeof(config));
}

static void prv_save_settings() {
  // Save the settings to persistent storage
  persist_write_data(SETTINGS_KEY, &config, sizeof(config));
  
  /* TODO: Upload user data to Server! ----------------------------------- END OF TODO */
}

// Read the user's app configuration
static void prv_inbox_received_handler(DictionaryIterator *iter, void *context) {
  
  // Read username
  Tuple *username_t = dict_find(iter, MESSAGE_KEY_userinfo_name);
  if(username_t) {
    config.username = username_t->value->cstring;
    APP_LOG(APP_LOG_LEVEL_INFO, "Configured username is %s", config.username);
  }
  else{
    APP_LOG(APP_LOG_LEVEL_ERROR, "No username was configured");
  }
  
  // Read emailaddress
  Tuple *email_t = dict_find(iter, MESSAGE_KEY_userinfo_email);
  if(email_t) {
    config.email = email_t->value->cstring;
    APP_LOG(APP_LOG_LEVEL_INFO, "Configured email is %s", config.email);
  }
  else{
    APP_LOG(APP_LOG_LEVEL_ERROR, "No email was configured");
  }
  
  // Read weight
  Tuple *weight_t = dict_find(iter, MESSAGE_KEY_userinfo_weight);
  if(weight_t) {
    config.weight = weight_t->value->int32;
    APP_LOG(APP_LOG_LEVEL_INFO, "Configured weight is %i", config.weight);
  }
  else{
    APP_LOG(APP_LOG_LEVEL_ERROR, "No weight was configured");
  }
  
  // Read sportiness
    Tuple *sportiness_t = dict_find(iter, MESSAGE_KEY_userinfo_sportiness);
  if(sportiness_t) {
    config.sportiness = sportiness_t->value->int32;
    APP_LOG(APP_LOG_LEVEL_INFO, "Configured sportiness is %i", config.sportiness);
  }
  else{
    APP_LOG(APP_LOG_LEVEL_ERROR, "No sportiness was configured");
  }
  
  // Save the settings to persistent storage and upload it on server
  prv_save_settings();
}

// Define what you want to do when the back button is pressed
void back_button_handler(ClickRecognizerRef recognizer, void *context) {
  window_stack_push(exit_window_get_window(), true);
}

// We need to save a reference to the ClickConfigProvider originally set by the menu layer
ClickConfigProvider previous_ccp;

// This is the new ClickConfigProvider we will set, it just calls the old one and then subscribe
// for back button events.
void new_ccp(void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "calling the new ccp");
  previous_ccp(context);
  window_single_click_subscribe(BUTTON_ID_BACK, back_button_handler);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "done in the new ccp");
}

// Call this from your init function to do the hack
void force_back_button(Window *window, MenuLayer *menu_layer) {
  previous_ccp = window_get_click_config_provider(window);
  window_set_click_config_provider_with_context(window, new_ccp, menu_layer);
}

// Save the answer given by the user
void setAnswer(int questionNumber, int answer){
  userAnswers[questionNumber - 1] = answer;
}

void launch_main_window3 (){
  window_stack_push(main_window_get_window(), true);
}


static void init() {
  // Read settings from persistent storage
  prv_load_settings();
  // Start reading user_configuration by opening AppMessage connection
  app_message_register_inbox_received(prv_inbox_received_handler);
  app_message_open(128, 128);
  
  // start the background worker
  AppWorkerResult app_worker_result = app_worker_launch();
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App worker launched with result %d", app_worker_result);
  
  // subscribe to background worker messages
  app_worker_message_subscribe(worker_message_handler);
  
  // init UI stuff
  wakeup_window_create();
  exit_window_create();
  splash_window_create();
  whoyouwith_window_create();
  sportquestion_window_create();
  main_window_create();
  tree_window_create();

    if(launch_reason() == APP_LAUNCH_WAKEUP) {
    //Vibration
    vibes_double_pulse();
    window_stack_push(wakeup_window_get_window(), true);
    
    //else the normal main window pops up
  } else {
          window_stack_push(splash_window_get_window(), true);
   app_timer_register(0000, launch_main_window3, NULL);
  
  }

}



static void deinit() {
  sportquestion_window_destroy();
  whoyouwith_window_destroy();
  splash_window_destroy();
  main_window_destroy();
   exit_window_destroy();
    wakeup_window_destroy();
  tree_window_destroy();

}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
  



