#include <pebble.h>
#include "storage.h"
#include "worker_src/c/storage.h"


// finds the last measure id
// returns 0 if there is none
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

int get_measure(int id, enum MeasureType type, bool removeAfterRead) {
  int key = id * 100 + (int)type;
  
  // check whether key exists in storage
  if(persist_exists(key)) {
    
    // read the value
    int value = persist_read_int(key);
    
    // check whether the key should be removed
    if(removeAfterRead) {
      persist_delete (key);
    }
    
    return value;
  }
  
  return -1;
}