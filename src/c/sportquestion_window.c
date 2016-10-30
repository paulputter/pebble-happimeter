#include <pebble.h>
#include "sportquestion_window.h"

Window *sportquestionWindow;
MenuLayer *sportquestionMenuLayer;
static TextLayer *s_time_layer;





void sportquestion_window_load(Window *window){
 Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Create the TextLayer with specific bounds
  s_time_layer = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(58, 52), bounds.size.w, 50));

  // Improve the layout to be more like a watchface
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  text_layer_set_text(s_time_layer, "00:00");
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
}

void sportquestion_window_unload(Window *window){
}

void sportquestion_window_create(){
  sportquestionWindow = window_create();
  window_set_window_handlers(sportquestionWindow, (WindowHandlers)
                             
    {
       .load = sportquestion_window_load,
       .unload = sportquestion_window_unload
    }
  );
}

void sportquestion_window_destroy(){
  window_destroy(sportquestionWindow);
}

Window *sportquestion_window_get_window(){
  return sportquestionWindow;
}