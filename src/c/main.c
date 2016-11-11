#include <pebble.h>
#include "splash_window.h"
#include "main_window.h"
#include "sportquestion_window.h"
#include "whoyouwith_window.h"
#include "wakeup.h"

static void init() {
  wakeup_window_create();
  splash_window_create();
  whoyouwith_window_create();
  sportquestion_window_create();
  main_window_create();
  
 window_stack_push(wakeup_window_get_window(), true);

}

static void deinit() {
  sportquestion_window_destroy();
  whoyouwith_window_destroy();
  splash_window_destroy();
  main_window_destroy();
    wakeup_window_destroy();

}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
  



