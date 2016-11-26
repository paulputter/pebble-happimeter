#include <pebble.h>
#include "exit_window.h"
#include "whoyouwith_window.h"
#include "sportquestion_window.h"
#include "main_window.h"
#include "whoyouwith_window.h"

Window *exitWindow;
MenuLayer *exitMenuLayer;
static TextLayer *s_label_layer;
static BitmapLayer *s_icon_layer;
static ActionBarLayer *s_action_bar_layer;
int number = 0;


static GBitmap *s_icon_bitmap, *s_tick_bitmap, *s_cross_bitmap, *exit_Window;

void exit_up_single_click_handler(ClickRecognizerRef recognizer, void *context){
  window_stack_pop_all(true);
}

// going back to the window, where we clicked on the back button
void exit_down_single_click_handler(ClickRecognizerRef recognizer, void *context){
  if(number==1){
   window_stack_push(main_window_get_window(), true);
  } 
  if(number ==2){
    window_stack_push(sportquestion_window_get_window(), true);
  }
    if(number ==3){
    window_stack_push(whoyouwith_window_get_window(), true);
  }
  if (number <1 || number >3){
    window_stack_pop_all(true);
  }
}

void exit_back_single_click_handler(ClickRecognizerRef recognizer, void *context){
   if(number==1){
   window_stack_push(main_window_get_window(), true);
  } 
  if(number ==2){
    window_stack_push(sportquestion_window_get_window(), true);
  }
    if(number ==3){
    window_stack_push(whoyouwith_window_get_window(), true);
  }
  if (number <1 || number >3){
    window_stack_pop_all(true);
  }
}

void exit_click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, (ClickHandler)exit_up_single_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, (ClickHandler) exit_down_single_click_handler);
  window_single_click_subscribe(BUTTON_ID_BACK, (ClickHandler) exit_back_single_click_handler);
}

void setNumberOfWindow(int n){
  number = n;
}

void exit_window_load(Window *window){
  
  
  
 Layer *window_layer = window_get_root_layer(window);
 // GRect bounds = layer_get_bounds(window_layer);
  #if defined(PBL_PLATFORM_EMERY)
    exit_Window = gbitmap_create_with_resource(RESOURCE_ID_Exit_Window_Emery);
   #else
     exit_Window = gbitmap_create_with_resource(RESOURCE_ID_Exit_Window_Time);
   #endif
 
  #if defined(PBL_PLATFORM_EMERY)
  s_icon_layer = bitmap_layer_create(GRect(0,0,200,228));
  #else 
  s_icon_layer = bitmap_layer_create(GRect(0,0,144,168));
  #endif
  
  bitmap_layer_set_bitmap(s_icon_layer, exit_Window);
  bitmap_layer_set_compositing_mode(s_icon_layer, GCompOpSet);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_icon_layer));
  


 // const GEdgeInsets label_insets = {.top = 10, .right = ACTION_BAR_WIDTH+ACTION_BAR_WIDTH / 2, .left = ACTION_BAR_WIDTH / 2};
 // s_label_layer = text_layer_create(grect_inset(bounds, label_insets));
 // text_layer_set_text(s_label_layer, EXIT_WINDOW_MESSAGE);
 // text_layer_set_background_color(s_label_layer, GColorClear);
 // text_layer_set_text_alignment(s_label_layer, GTextAlignmentCenter);
 // text_layer_set_font(s_label_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
 // layer_add_child(window_layer, text_layer_get_layer(s_label_layer));

  s_tick_bitmap = gbitmap_create_with_resource(RESOURCE_ID_TICK);
  s_cross_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CROSS);

  s_action_bar_layer = action_bar_layer_create();
  action_bar_layer_set_icon(s_action_bar_layer, BUTTON_ID_UP, s_tick_bitmap);
  action_bar_layer_set_icon(s_action_bar_layer, BUTTON_ID_DOWN, s_cross_bitmap);
  action_bar_layer_add_to_window(s_action_bar_layer, window);
  
  // Set the click config provider:
  action_bar_layer_set_click_config_provider(s_action_bar_layer, exit_click_config_provider);
}



void exit_window_unload(Window *window){
  text_layer_destroy(s_label_layer);
  action_bar_layer_destroy(s_action_bar_layer);
  bitmap_layer_destroy(s_icon_layer);

  gbitmap_destroy(s_icon_bitmap);
  gbitmap_destroy(s_tick_bitmap);
  gbitmap_destroy(s_cross_bitmap);
  gbitmap_destroy(exit_Window);

  window_destroy(window);
exitWindow = NULL;
}


void exit_window_create() {
  if(!exitWindow) {
   exitWindow = window_create();
    window_set_background_color(exitWindow, PBL_IF_COLOR_ELSE (GColorWhite, GColorWhite));
    window_set_window_handlers(exitWindow, (WindowHandlers) {
        .load = exit_window_load,
        .unload =exit_window_unload,
    });
  }
  window_stack_push(exitWindow, true);
}


void exit_window_destroy(){
  window_destroy(exitWindow);
}

Window *exit_window_get_window(){
  return exitWindow;
}