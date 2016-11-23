#include <pebble.h>
#include "main_window.h"
#include "sportquestion_window.h"
#include "exit_window.h"
#include "main.h"

Window *mainWindow;
MenuLayer *mainMenuLayer;
TextLayer *text_layer;
static GBitmap *Very_Happy, *Happy, *Normal, *Unhappy, *Very_Unhappy, *HowAreYouFeeling;
static int16_t menu_header_height(struct MenuLayer *menu, uint16_t section_index, void *callback_context);
static void menu_draw_header(GContext* ctx, const Layer* cell_layer, uint16_t section_index, void* callback_context);




  

uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
return 1;
}

uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
    switch(section_index){
      case 0:
          return 5;
      default:
          return 0;
    }
}



static void menu_draw_header(GContext* ctx, const Layer* cell_layer, uint16_t section_index, void* callback_context) {
   GRect bounds = layer_get_bounds(cell_layer);
  //menu_cell_basic_draw(ctx, cell_layer, "", NULL, HowAreYouFeeling);
   graphics_context_set_fill_color(ctx, GColorWhite);
   //graphics_context_set_text_color(ctx, GColorBlack);
   // draw the box; 3rd and 4th variables: rounding the corners of the box
  // the watch has a displey of 200 p width
   graphics_fill_rect(ctx,GRect((bounds.size.w-144)/2,4,144,40),8,GCornersAll);
  graphics_draw_bitmap_in_rect(ctx, HowAreYouFeeling, bounds);
   // text in the box
   //graphics_draw_text(ctx, ("How are you feeling?"),fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD),GRect(0, 0, bounds.size.w, 80), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
}

// Size of the header box
int16_t menu_header_height(struct MenuLayer *menu, uint16_t section_index, void *callback_context) {
  return 40;
}

//void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  //  switch(section_index){
    //  case 0:
      //  menu_cell_basic_header_draw(ctx, cell_layer, "Moods");
      //break;
    //}
//}

//int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  //  return MENU_CELL_BASIC_HEADER_HEIGHT;
//}

void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
    switch (cell_index->section){
      case 0:
        switch (cell_index->row){
          case 0:
          // NULL = Smily icon to input
              menu_cell_basic_draw(ctx, cell_layer, "", NULL, Very_Happy);
            break;
           case 1:
          // NULL = Smily icon to input
              menu_cell_basic_draw(ctx, cell_layer, "", NULL, Happy);
            break;
           case 2:
          // NULL = Smily icon to input
              menu_cell_basic_draw(ctx, cell_layer, "", NULL, Normal);
            break;
           case 3:
          // NULL = Smily icon to input
              menu_cell_basic_draw(ctx, cell_layer, "", NULL, Unhappy);
            break;
           case 4:
          // NULL = Smily icon to input
              menu_cell_basic_draw(ctx, cell_layer, "", NULL, Very_Unhappy);
            break;
        }
    
        break;
      
    }
}

// Detect when somebody hits the select button and save the user input
void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
     // save the given answer: question 1, answer 'cell_index'
    // PROBLEM: no proof, if it functions correctly
  setAnswer(1,(int) cell_index->row);
  window_stack_push(sportquestion_window_get_window(), true);
}

void setup_menu_layer(Window *window) {
	Layer *window_layer = window_get_root_layer(window);

  GRect bounds = layer_get_bounds(window_layer);

    mainMenuLayer = menu_layer_create(bounds);
    menu_layer_set_normal_colors(mainMenuLayer,  GColorWhite, GColorWhite);
  menu_layer_set_highlight_colors(mainMenuLayer, GColorLightGray, GColorBlack);
  
    menu_layer_set_callbacks(mainMenuLayer, NULL, (MenuLayerCallbacks){
        .get_num_sections = menu_get_num_sections_callback,
        .get_num_rows = menu_get_num_rows_callback,
        .get_header_height = menu_header_height,
        .draw_header = menu_draw_header,
        .draw_row = menu_draw_row_callback,
        .select_click = menu_select_callback
    });

    menu_layer_set_click_config_onto_window(mainMenuLayer, window);
  
  //menu_layer_set_center_focused(mainMenuLayer, true);
  
    // overwrite default setting for back button
    force_back_button(window, mainMenuLayer);

    layer_add_child(window_layer, menu_layer_get_layer(mainMenuLayer));
}

// Load the used images
void main_window_load(Window *window){
 setup_menu_layer(window);
  Very_Happy = gbitmap_create_with_resource(RESOURCE_ID_Very_Happy_Smiley);
  Happy = gbitmap_create_with_resource(RESOURCE_ID_Happy_Smiley);
  Normal = gbitmap_create_with_resource(RESOURCE_ID_Normal_Smiley);
  Unhappy = gbitmap_create_with_resource(RESOURCE_ID_Unhappy_Smiley);
  Very_Unhappy = gbitmap_create_with_resource(RESOURCE_ID_Very_Unhappy_Smiley);
  HowAreYouFeeling = gbitmap_create_with_resource(RESOURCE_ID_HowAreYouFeelingBolt);

}

void main_window_unload(Window *window){
  menu_layer_destroy(mainMenuLayer);
  gbitmap_destroy(Very_Happy);
  gbitmap_destroy(Happy);
  gbitmap_destroy(Normal);
  gbitmap_destroy(Unhappy);
  gbitmap_destroy(Very_Unhappy);

}

// to remember where we were, should we fetch the exit_window
void main_window_appear(Window *window){
  setNumberOfWindow(1);
}

void main_window_create(){
  mainWindow = window_create();
  window_set_window_handlers(mainWindow, (WindowHandlers)
                             
    {
       .load = main_window_load,
       .unload = main_window_unload,
      .appear = main_window_appear
    }
  );
}

void main_window_destroy(){
  window_destroy(mainWindow);
}

Window *main_window_get_window(){
  return mainWindow;
}