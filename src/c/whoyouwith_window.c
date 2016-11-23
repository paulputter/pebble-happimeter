#include <pebble.h>
#include "whoyouwith_window.h"
#include "exit_window.h"
#include "main.h"
#include "src/c/tree_window.h"

Window *whoyouwithWindow;
MenuLayer *whoyouwithMenuLayer;
static GBitmap *Nobody,*Pet, *Friend, *Colleague, *Family, *Significant_Other, *Other;


uint16_t select_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  return 1;
}

uint16_t select_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
   switch(section_index){
      case 0:
          return 7;
      default:
          return 0;
    }
}

int16_t select_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
    return MENU_CELL_BASIC_HEADER_HEIGHT;
}



void select_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  menu_cell_basic_header_draw(ctx, cell_layer, "Who are you with");
}

void select_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  switch (cell_index->section){
      case 0:
        switch (cell_index->row){
          case 0:
              menu_cell_basic_draw(ctx, cell_layer, "", NULL, Nobody);
            break;
           case 1:
              menu_cell_basic_draw(ctx, cell_layer, "", NULL, Pet);
            break;
           case 2:
              menu_cell_basic_draw(ctx, cell_layer, "", NULL, Friend);
            break;
           case 3:
              menu_cell_basic_draw(ctx, cell_layer, "", NULL, Colleague);
            break;
           case 4:
              menu_cell_basic_draw(ctx, cell_layer, "", NULL, Family);
            break;
             case 5:
              menu_cell_basic_draw(ctx, cell_layer, "", NULL, Significant_Other);
            break;
           case 6:
              menu_cell_basic_draw(ctx, cell_layer, "", NULL, Other);
            break;
        }
    
       break;
      
    }
}

void select_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
       // save the given answer: question 1, answer 'cell_index'
    // PROBLEM: no proof, if it functions correctly
  setAnswer(3,(int) cell_index->row);
  window_stack_push(tree_window_get_window(), true);
   //window_stack_pop_all(true);
}

void select_menu_layer(Window *window) {
  
	Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

    whoyouwithMenuLayer = menu_layer_create(bounds);
     menu_layer_set_normal_colors(whoyouwithMenuLayer,  GColorWhite, GColorWhite);
  menu_layer_set_highlight_colors(whoyouwithMenuLayer, GColorLightGray, GColorBlack);
    menu_layer_set_callbacks(whoyouwithMenuLayer, NULL, (MenuLayerCallbacks){
        .get_num_sections = select_get_num_sections_callback,
        .get_num_rows = select_get_num_rows_callback,
        .get_header_height = select_get_header_height_callback,
        .draw_header = select_draw_header_callback,
        .draw_row = select_draw_row_callback,
        .select_click = select_select_callback
    });

    menu_layer_set_click_config_onto_window(whoyouwithMenuLayer, window);
     // overwrite back button
  force_back_button(window, whoyouwithMenuLayer);
    layer_add_child(window_layer, menu_layer_get_layer(whoyouwithMenuLayer));
}


void whoyouwith_window_load(Window *window){
  select_menu_layer(window);
  Nobody = gbitmap_create_with_resource(RESOURCE_ID_Nobody);
  Pet = gbitmap_create_with_resource(RESOURCE_ID_Pet);
  Friend = gbitmap_create_with_resource(RESOURCE_ID_Friend);
  Colleague = gbitmap_create_with_resource(RESOURCE_ID_Colleauge);
  Family = gbitmap_create_with_resource(RESOURCE_ID_Family);
  Significant_Other = gbitmap_create_with_resource(RESOURCE_ID_SignificantOther);
  Other = gbitmap_create_with_resource(RESOURCE_ID_Other);
 
}



void whoyouwith_window_unload(Window *window){
  menu_layer_destroy(whoyouwithMenuLayer);
  
  gbitmap_destroy(Nobody);
  gbitmap_destroy(Pet);
  gbitmap_destroy(Friend);
  gbitmap_destroy(Colleague);
  gbitmap_destroy(Family);
  gbitmap_destroy(Significant_Other);
  gbitmap_destroy(Other);

}

// to remember where we were, should we fetch the exit_window
void whoyouwith_window_appear(Window *window){
   setNumberOfWindow(3);
}

void whoyouwith_window_create(){
  whoyouwithWindow = window_create();
  window_set_window_handlers(whoyouwithWindow, (WindowHandlers) {
        .load = whoyouwith_window_load,
        .unload =whoyouwith_window_unload,
      .appear = whoyouwith_window_appear
    });
  window_stack_push(whoyouwithWindow, true);
}

void whoyouwith_window_destroy(){
  window_destroy(whoyouwithWindow);
  
}

Window *whoyouwith_window_get_window(){
  return whoyouwithWindow;
}