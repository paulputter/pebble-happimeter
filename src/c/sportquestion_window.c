#include <pebble.h>
#include "sportquestion_window.h"

Window *sportquestionWindow;
MenuLayer *sportquestionMenuLayer;
static TextLayer *s_label_layer;
static BitmapLayer *s_icon_layer;
static ActionBarLayer *s_action_bar_layer;

static GBitmap *s_tick_bitmap, *s_cross_bitmap;



void sportquestion_window_load(Window *window){
 Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  
  

  const GEdgeInsets label_insets = {.top = 10, .right = ACTION_BAR_WIDTH+ACTION_BAR_WIDTH / 2, .left = ACTION_BAR_WIDTH / 2};
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
}


void sportquestion_window_unload(Window *window){
  text_layer_destroy(s_label_layer);
  action_bar_layer_destroy(s_action_bar_layer);
  bitmap_layer_destroy(s_icon_layer);


  gbitmap_destroy(s_tick_bitmap);
  gbitmap_destroy(s_cross_bitmap);

  window_destroy(window);
sportquestionWindow = NULL;
}

void sportquestion_window_create() {
  if(!sportquestionWindow) {
   sportquestionWindow = window_create();
    window_set_background_color(sportquestionWindow, PBL_IF_COLOR_ELSE(GColorJaegerGreen, GColorWhite));
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