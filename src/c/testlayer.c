#include <pebble.h>
#include "splash_window.h"

Window *testhWindow;



void test_window_load(Window *window){
  Layer *window_layer = window_get_root_layer(window);
  

}

void test_window_unload(Window *window){

}

void test_window_create(){
  testhWindow = window_create();
  window_set_window_handlers(testhWindow, (WindowHandlers)
                             
    {
       .load = test_window_load,
       .unload = test_window_unload
    }
  );
}

void test_window_destroy(){
  window_destroy(testhWindow);
}

Window *test_window_get_window(){
  return testhWindow;
}