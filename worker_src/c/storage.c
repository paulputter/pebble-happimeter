#include <pebble_worker.h>
#include "worker_src/c/storage.h"
#include "worker_src/c/data_collection_worker.h"

enum StatusCode save_measure(enum MeasureType type, int value, int id) {
  // set the unique key
  // format: ID Type
  uint32_t data_key = id * 100 + (int) type;
  enum StatusCode code = persist_write_int(data_key, value);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Wrote %d bytes in the storage...", persist_get_size(data_key));
  return code;
}

int get_last_measure_id() {
  bool found = true;
  int id = 1;
  while(found) {
    found = persist_exists(id*100 + 10);
    if(found) {
      id++;
    }
  }
  
  return id - 1;
}