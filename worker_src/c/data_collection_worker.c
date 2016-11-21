#include <pebble_worker.h>
#include "worker_src/c/data_collection_worker.h"
#include "worker_src/c/measure.h"

// Called every minute and collects measurement data und calls the upload routine
static void updates_tick_handler (struct tm *tick_time, TimeUnits changed) {
  time_t current_time = time(NULL);
  struct tm *local_time = localtime(&current_time);
  
  if((local_time->tm_min + 1) % UPDATE_INTERVAL_IN_MINUTES == 0) {
    measure_iteration(current_time);
  }
  
  if((local_time->tm_min + 1) % UPLOAD_INTERVAL_IN_MINUTES == 0) {
    APP_LOG(APP_LOG_LEVEL_INFO, "#1 Upload the data...");
    // Start the main app in order to upload the data
    worker_launch_app();
    AppWorkerMessage message = { 
      .data0 = 4711, // this is the code that says --> upload the latest data
    };
    app_worker_send_message(SOURCE_BACKGROUND, &message);
  }
}

// Initialize the worker
static void init() {
  // Get updates every minute
  tick_timer_service_subscribe(MINUTE_UNIT, updates_tick_handler);
}

// Deinitialize the worker
static void deinit() {
  // Destroy ticker
  tick_timer_service_unsubscribe();
}

// Main Method
int main(void) {
  init();
  worker_event_loop();
  deinit();
}