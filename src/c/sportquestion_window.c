#include <pebble.h>
#include "sportquestion_window.h"
#include "whoyouwith_window.h"
#include "exit_window.h"

Window *sportquestionWindow;
MenuLayer *sportquestionMenuLayer;
static TextLayer *s_label_layer;
static BitmapLayer *s_icon_layer;
static ActionBarLayer *s_action_bar_layer;


static GBitmap *s_icon_bitmap, *s_tick_bitmap, *s_cross_bitmap;

void up_single_click_handler(ClickRecognizerRef recognizer, void *context){
 window_stack_push(whoyouwith_window_get_window(), true);
}

void down_single_click_handler(ClickRecognizerRef recognizer, void *context){
 window_stack_push(whoyouwith_window_get_window(), true);
}

void back_single_click_handler(ClickRecognizerRef recognizer, void *context){
  window_stack_push(exit_window_get_window(), true);
}

void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, (ClickHandler)up_single_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, (ClickHandler) down_single_click_handler);
  window_single_click_subscribe(BUTTON_ID_BACK, (ClickHandler) back_single_click_handler);

}

void sportquestion_window_load(Window *window){
  
 Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
   s_icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CONFIRM);
  
  const GEdgeInsets icon_insets = {.top = 0, .right = 28, .bottom = 90, .left = 14};
  s_icon_layer = bitmap_layer_create(grect_inset(bounds, icon_insets));
  bitmap_layer_set_bitmap(s_icon_layer, s_icon_bitmap);
  bitmap_layer_set_compositing_mode(s_icon_layer, GCompOpSet);
layer_add_child(window_layer, bitmap_layer_get_layer(s_icon_layer));

  const GEdgeInsets label_insets = {.top = 60, .right = ACTION_BAR_WIDTH+ACTION_BAR_WIDTH / 2, .left = ACTION_BAR_WIDTH / 2};
  s_label_layer = text_layer_create(grect_inset(bounds, label_insets));
  text_layer_set_text(s_label_layer, SPORTQUESTION_WINDOW_MESSAGE);
  text_layer_set_background_color(s_label_layer, GColorClear);
  text_layer_set_text_alignment(s_label_layer, GTextAlignmentCenter);
  text_layer_set_font(s_label_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  layer_add_child(window_layer, text_layer_get_layer(s_label_layer));

  s_tick_bitmap = gbitmap_create_with_resource(RESOURCE_ID_TICK);
  s_cross_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CROSS);

  s_action_bar_layer = action_bar_layer_create();
  action_bar_layer_set_icon(s_action_bar_layer, BUTTON_ID_UP, s_tick_bitmap);
  action_bar_layer_set_icon(s_action_bar_layer, BUTTON_ID_DOWN, s_cross_bitmap);
  action_bar_layer_add_to_window(s_action_bar_layer, window);
  
  // Set the click config provider:
  action_bar_layer_set_click_config_provider(s_action_bar_layer, click_config_provider);
}



void sportquestion_window_unload(Window *window){
  text_layer_destroy(s_label_layer);
  action_bar_layer_destroy(s_action_bar_layer);
  bitmap_layer_destroy(s_icon_layer);

  gbitmap_destroy(s_icon_bitmap);
  gbitmap_destroy(s_tick_bitmap);
  gbitmap_destroy(s_cross_bitmap);

  window_destroy(window);
sportquestionWindow = NULL;
}

void sportquestion_window_create() {
  if(!sportquestionWindow) {
   sportquestionWindow = window_create();
    window_set_background_color(sportquestionWindow, PBL_IF_COLOR_ELSE (GColorWhite, GColorWhite));
    window_set_window_handlers(sportquestionWindow, (WindowHandlers) {
        .load = sportquestion_window_load,
        .unload =sportquestion_window_unload,
    });
  }
  window_stack_push(sportquestionWindow, true);
}


void sportquestion_window_destroy(){
  window_destroy(sportquestionWindow);
}

Window *sportquestion_window_get_window(){
  return sportquestionWindow;
}