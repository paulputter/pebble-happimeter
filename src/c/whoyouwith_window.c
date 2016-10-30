#include <pebble.h>
#include "whoyouwith_window.h"

Window *whoyouwithWindow;
MenuLayer *whoyouwithMenuLayer;


uint16_t select_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
return 0;
}

uint16_t select_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return 0;
}

int16_t select_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
    return MENU_CELL_BASIC_HEADER_HEIGHT;
}

void select_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
}

void select_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
}

// Detect when somebody hits the select button
void select_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
}

void select_menu_layer(Window *window) {
	Layer *window_layer = window_get_root_layer(window);

    whoyouwithMenuLayer = menu_layer_create(GRect(0, 0, 144, 168));
    menu_layer_set_callbacks(whoyouwithMenuLayer, NULL, (MenuLayerCallbacks){
        .get_num_sections = select_get_num_sections_callback,
        .get_num_rows = select_get_num_rows_callback,
        .get_header_height = select_get_header_height_callback,
        .draw_header = select_draw_header_callback,
        .draw_row = select_draw_row_callback,
        .select_click = select_select_callback
    });

    menu_layer_set_click_config_onto_window(whoyouwithMenuLayer, window);

    layer_add_child(window_layer, menu_layer_get_layer(whoyouwithMenuLayer));
}

void whoyouwith_window_load(Window *window){
}

void whoyouwith_window_unload(Window *window){

}

void whoyouwith_window_create(){
  whoyouwithWindow = window_create();
  window_set_window_handlers(whoyouwithWindow, (WindowHandlers) {
        .load = whoyouwith_window_load,
        .unload =whoyouwith_window_unload,
    });
  window_stack_push(whoyouwithWindow, true);
}

void whoyouwith_window_destroy(){
  window_destroy(whoyouwithWindow);
}

Window *whoyouwith_window_get_window(){
  return whoyouwithWindow;
}