#include <pebble.h>
#include "splash_window.h"
#include "main_window.h"
#include "sportquestion_window.h"
#include "whoyouwith_window.h"
#include "wakeup.h"
#include "exit_window.h"
#include "src/c/uploader.h"

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


static void init() {
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
  
 window_stack_push(wakeup_window_get_window(), true);

}

static void deinit() {
  sportquestion_window_destroy();
  whoyouwith_window_destroy();
  splash_window_destroy();
  main_window_destroy();
   exit_window_destroy();
    wakeup_window_destroy();

}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
  



