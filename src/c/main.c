#include <pebble.h>
#define SOURCE_FOREGROUND 0
#define SOURCE_BACKGROUND 1

static Window *s_window;
static TextLayer *s_text_layer;

static void worker_message_handler(uint16_t type, AppWorkerMessage *message) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Got a message");
  if(type == SOURCE_BACKGROUND) {
    
    // Get the data, only if it was sent from the background
    int hour = message->data0;
    int data_type = message->data1;
    int data_value = message->data2;
    
    APP_LOG(APP_LOG_LEVEL_INFO, "Got hour from the worker: %d", hour);
  }
}

static void init(void) {
  // Read the integer value
  int lastSensorSent = persist_read_int(12);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Last value was %d", lastSensorSent);
  AppWorkerResult app_worker_result = app_worker_launch();
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App worker launched with result %d", app_worker_result);
  
  // IMPORTANT: Code after this line is not relevant for data collection
  
	// Create a window and get information about the window
	s_window = window_create();
  Layer *window_layer = window_get_root_layer(s_window);
  GRect bounds = layer_get_bounds(window_layer);
	
  // Create a text layer and set the text
	s_text_layer = text_layer_create(bounds);
	text_layer_set_text(s_text_layer, "Hi! This is the Happimeter data collector..");
  
  // Set the font and text alignment
	text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);

	// Add the text layer to the window
	layer_add_child(window_get_root_layer(s_window), text_layer_get_layer(s_text_layer));
  
  // Enable text flow and paging on the text layer, with a slight inset of 10, for round screens
  text_layer_enable_screen_text_flow_and_paging(s_text_layer, 10);

	// Push the window, setting the window animation to 'true'
	window_stack_push(s_window, true);
  
  app_worker_message_subscribe(worker_message_handler);
}

static void deinit(void) {
	// Destroy the text layer
	text_layer_destroy(s_text_layer);
	
	// Destroy the window
	window_destroy(s_window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
