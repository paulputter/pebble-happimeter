#include <pebble.h>
#include "splash_window.h"
#include "main_window.h"
#include "sportquestion_window.h"
#include "whoyouwith_window.h"

// Timer to see how long you can see the main window
void launch_main_window (){
  window_stack_push(main_window_get_window(), true);
}


int main (){

  splash_window_create();
  sportquestion_window_create();
  main_window_create();
  whoyouwith_window_create();
 
  
  window_stack_push(splash_window_get_window(), true);
  app_timer_register(1000, launch_main_window, NULL); 
   
  
  app_event_loop();
  sportquestion_window_destroy();
  whoyouwith_window_create();
  splash_window_destroy();
}