#include <pebble.h>
#include "tree_window.h"
#include "whoyouwith_window.h"
#include "exit_window.h"
#include "sportquestion_window.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;

  
static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
}

static void destroy_ui(void) {
  window_destroy(s_window);
}
// END AUTO-GENERATED UI CODE

Window *treeWindow;
GBitmap *treeImage;
GBitmap *treeImage1;
GBitmap *treeImage2;
GBitmap *treeImage3;
GBitmap *treeImage4;
BitmapLayer *treeImageLayer;
TextLayer *treeImageTitle;
uint32_t key;
uint32_t counter;

/*void exit_up_single_click_handler(ClickRecognizerRef recognizer, void *context){
  window_stack_pop_all(true);
}*/





void tree_window_load(Window *window){
  Layer *window_layer = window_get_root_layer(window);
 /* if(persist_read_int(counter)==null){
    counter=1;
  }*/
APP_LOG(APP_LOG_LEVEL_INFO,"%ld",persist_read_int(counter));
  APP_LOG(APP_LOG_LEVEL_INFO,"%d",444);
  //else 
    //counter = counter +1;
  //persist_wirte_int(key,counter);
  
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  

  if(!persist_exists(key)){
    key = 0;
    counter=1;
    persist_write_int(key,counter);
    //treeImage = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TREE1);
  }
  else{
    counter = persist_read_int(key);
    counter = counter % 4;
  }


  switch (counter){
    case 1:
        treeImage = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TREE1);
        counter = counter + 1;
        persist_write_int(key,counter);
      break;
    
     case 2:
        treeImage = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TREE2);
        counter = counter + 1;
        persist_write_int(key,counter);
      break;
    
     case 3:
        treeImage = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TREE3);
        counter = counter + 1;
        persist_write_int(key,counter);
      break;
    
     case 0:
        treeImage = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TREE4);
        counter = counter + 1;
        persist_write_int(key,counter);
      break;
  }
  
//void exit_click_config_provider(void *context) {
//  window_single_click_subscribe(BUTTON_ID_UP,(ClickHandler)disappear);
  //window_single_click_subscribe(BUTTON_ID_DOWN, (ClickHandler) exit_up_single_click_handler);
//}
  
  // Loads a png Image from ressources
  //treeImage = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TREE1);
  treeImageLayer = bitmap_layer_create(GRect(0,0,144,168));
  bitmap_layer_set_bitmap(treeImageLayer, treeImage);
  bitmap_layer_set_compositing_mode(treeImageLayer, GCompOpSet);
  layer_add_child(window_layer, bitmap_layer_get_layer(treeImageLayer));
  
  // Displays a text message
   /*treeImageTitle = text_layer_create(GRect(0,120,144,50));
   text_layer_set_text(treeImageTitle, "You are the best! Gavin.");
   text_layer_set_text_alignment(treeImageTitle, GTextAlignmentCenter);
   layer_add_child(window_layer, text_layer_get_layer(treeImageTitle));
  */
}

void tree_window_unload(Window *window){
  gbitmap_destroy(treeImage);
  bitmap_layer_destroy(treeImageLayer);
  //text_layer_destroy(treeImageTitle);
  
}

void tree_window_create(){
  treeWindow = window_create();
  window_set_window_handlers(treeWindow, (WindowHandlers)
                             
    {
       .load = tree_window_load,
       .unload = tree_window_unload
    }
  );
}
// window_set_fullscreen(s_window, true);

void tree_window_destroy(){
  window_destroy(treeWindow);
}

Window *tree_window_get_window(){
  return treeWindow;
}