#include <pebble.h>
#include "sportquestion_window.h"
#include "whoyouwith_window.h"
#include "exit_window.h"
#include "main.h"

Window *sportquestionWindow;
MenuLayer *sportquestionMenuLayer;
static TextLayer *s_label_layer;
// static TextLayer *s_frame_layer;
static BitmapLayer *s_icon_layer;

static ActionBarLayer *s_action_bar_layer;


static GBitmap *s_icon_bitmap, *s_tick_bitmap, *s_cross_bitmap;


// detect user input and save answers
void up_single_click_handler(ClickRecognizerRef recognizer, void *context){
  // save the given answer: question 2, answer 1 (=yes)
  setAnswer(2,1);
  window_stack_push(whoyouwith_window_get_window(), true);
}

void down_single_click_handler(ClickRecognizerRef recognizer, void *context){
   // save the given answer: question 3, answer 0 (=no)
  setAnswer(2,0);
  window_stack_push(whoyouwith_window_get_window(), true);
}

// overwrite default setting for back button
void back_single_click_handler(ClickRecognizerRef recognizer, void *context){
  setNumberOfWindow(2);
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
  
  // IF ELSE

  #if defined(PBL_PLATFORM_EMERY)
    s_icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_DidYouDoSports_Emery);
   #else
    s_icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_DidYouDoSports_Time);
   #endif 
  

  // Background picture
  const GEdgeInsets icon_insets = {.top = 0, .right = 30, .bottom = 0, .left = 0};
  s_icon_layer = bitmap_layer_create(grect_inset(bounds, icon_insets));
  bitmap_layer_set_bitmap(s_icon_layer, s_icon_bitmap);
  bitmap_layer_set_compositing_mode(s_icon_layer, GCompOpSet);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_icon_layer));
  
  // Second background picture (the same picture but with changed position)
  //const GEdgeInsets icon2_insets = {.top = 0, .right = 0, .bottom = 0, .left = 99};
  //s_icon2_layer = bitmap_layer_create(grect_inset(bounds, icon2_insets));
  //bitmap_layer_set_bitmap(s_icon2_layer, s_icon_bitmap);
  //bitmap_layer_set_compositing_mode(s_icon2_layer, GCompOpSet);
  //layer_add_child(window_layer, bitmap_layer_get_layer(s_icon2_layer));
  
  //const GEdgeInsets frame_insets = {.top = 40, .right = ACTION_BAR_WIDTH, .bottom = 40, .left = 0 };
  //s_frame_layer = text_layer_create(grect_inset(bounds, frame_insets));
  // text_layer_set_text(s_frame_layer, "n");
  //text_layer_set_background_color(s_frame_layer, GColorBlack);
  //layer_add_child(window_layer, text_layer_get_layer(s_frame_layer));

  // The box for the text
  //const GEdgeInsets label_insets = {.top = 45, .right = ACTION_BAR_WIDTH, .bottom = 42, .left = 2 };
  //s_label_layer = text_layer_create(grect_inset(bounds, label_insets));
  //text_layer_set_text(s_label_layer, SPORTQUESTION_WINDOW_MESSAGE);
  //text_layer_set_background_color(s_label_layer, GColorGreen);
  //text_layer_set_text_alignment(s_label_layer, GTextAlignmentCenter);
  //text_layer_set_font(s_label_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  //layer_add_child(window_layer, text_layer_get_layer(s_label_layer));

  s_tick_bitmap = gbitmap_create_with_resource(RESOURCE_ID_TICK);
  s_cross_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CROSS);

  s_action_bar_layer = action_bar_layer_create();
  action_bar_layer_set_background_color(s_action_bar_layer, GColorBlack);
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