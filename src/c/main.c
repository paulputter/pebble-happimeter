#include <pebble.h>
#include "splash_window.h"
#include "main_window.h"
#include "sportquestion_window.h"
#include "whoyouwith_window.h"
#include "wakeup.h"

// Timer to see how long you can see the main window
void launch_main_window (){
  window_stack_push(main_window_get_window(), true);
}

static void init() {
  wakeup_window_create();
  splash_window_create();
  whoyouwith_window_create();
  sportquestion_window_create();
  main_window_create();
  
 window_stack_push(wakeup_window_get_window(), true);
  
    window_stack_push(splash_window_get_window(), true);
 app_timer_register(2000, launch_main_window, NULL);

}

static void deinit() {
  sportquestion_window_destroy();
  whoyouwith_window_destroy();
  splash_window_destroy();
  main_window_destroy();
    wakeup_window_destroy();

}



//////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////

int main(void) {
  init();
  app_event_loop();
  deinit();
}
  



