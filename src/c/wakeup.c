#include <pebble.h>
#include "wakeup.h"
#include "main_window.h"
#include "splash_window.h"

Window *s_main_window;
//TextLayer *s_text_layer;
//static GBitmap *ticktick;
static ActionBarLayer *s_action_layer;

void launch_main_window (){
  window_stack_push (main_window_get_window(), true);
}

static void wakeup_handler(WakeupId id, int32_t reason) { 
  window_stack_push(s_main_window , true);
  vibes_double_pulse();
}

void select_single_click_handler(ClickRecognizerRef recognizer, void *context)
{
 window_stack_push(splash_window_get_window(), true);
 app_timer_register(3000, launch_main_window, NULL);
}

void tick_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, (ClickHandler)select_single_click_handler);
}

static void wakeup(){
  
   // Next occuring (day/hour/minutes)
  printf("wir sind in der wakeupfunktion");

  time_t timestamp_1 = clock_to_timestamp(TODAY, 15, 42);
  //time_t timestamp_2 = clock_to_timestamp(TODAY, 13, 00);
  //time_t timestamp_3 = clock_to_timestamp(TODAY, 17, 00);
  //time_t timestamp_4 = clock_to_timestamp(TODAY, 21, 00);

  // Choose a 'cookie' value representing the reason for the wakeup
  const int cookie = 0;

  // If true, the user will be notified if they missed the wakeup 
  // (i.e. their watch was off)
  const bool notify_if_missed = true;

  // Schedule wakeup event
  WakeupId id_1 = wakeup_schedule(timestamp_1, cookie, notify_if_missed);
  //WakeupId id_2 = wakeup_schedule(timestamp_2, cookie, notify_if_missed);
  //WakeupId id_3 = wakeup_schedule(timestamp_3, cookie, notify_if_missed);
  //WakeupId id_4 = wakeup_schedule(timestamp_4, cookie, notify_if_missed);
  printf("scheduled!");
  // Check the scheduling was successful
   if(id_1 >= 0){
     // Persist the ID so that a future launch can query it
     const int wakeup_id_key = 43;
     persist_write_int(wakeup_id_key, id_1);
   }
  
  // Is the wakeup still scheduled?
if(wakeup_query(id_1, &timestamp_1)==0) {
  // Get the time remaining
  int seconds_remaining = timestamp_1 - time(NULL);
  printf("still scheduled?\n");
  APP_LOG(APP_LOG_LEVEL_INFO, "%d seconds until wakeup", seconds_remaining);
}
}

static void main_window_load(Window *window) {
  s_action_layer = action_bar_layer_create();
  action_bar_layer_add_to_window(s_action_layer, window);

  
  // Set the click config provider:
  action_bar_layer_set_click_config_provider(s_action_layer, tick_config_provider);

}

static void main_window_unload(Window *window) {

}

void wakeup_window_create() {
   
  //If the app is launched due to a previously scheduled wakeup event
  if(launch_reason() == APP_LAUNCH_WAKEUP) {
    // The app was started by a wakeup event.
    WakeupId id = 0;
    int32_t reason = 0;

    // Get details and handle the event appropriately
    wakeup_get_launch_event(&id, &reason);
  }
  
  wakeup();
    // Subscribe to wakeup service
  
  wakeup_service_subscribe(wakeup_handler);
  
  //Layer *window_layer = window_get_root_layer(s_main_window);
  
  s_main_window = window_create();
    window_set_window_handlers(s_main_window, (WindowHandlers) {
        .load = main_window_load,
        .unload =main_window_unload,
    });
  //s_text_layer = text_layer_create(layer_get_bounds(window_layer));
  
  window_stack_push(s_main_window , true);
  
}

void wakeup_window_destroy() {
  window_destroy(s_main_window);
  //text_layer_destroy(s_text_layer);
  action_bar_layer_destroy(s_action_layer);
}

Window *wakeup_window_get_window(){
  return s_main_window;
}

