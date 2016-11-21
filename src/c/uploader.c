#include <pebble.h>
#include "uploader.h"
#include "src/c/storage.h"

static int current_measurement_id = 0;

void perform_upload() {
  if(get_measure(current_measurement_id, measurement_steps, false) != -1) {
    APP_LOG(APP_LOG_LEVEL_INFO, "Got a dataset with the id %d.", current_measurement_id);

    // receive all measurement data and delete them
    int steps = get_measure(current_measurement_id, measurement_steps, true);
    int current_time = get_measure(current_measurement_id, measurement_current_time, true);
    int min_bpm = get_measure(current_measurement_id, measurement_min_bpm, true);
    int max_bpm = get_measure(current_measurement_id, measurement_max_bpm, true);
    int avg_bpm = get_measure(current_measurement_id, measurement_avg_bpm, true);
    int avg_light_level = get_measure(current_measurement_id, measurement_avg_light_level, true);
    int activity = get_measure(current_measurement_id, measurement_activity, true);
    int sleep = get_measure(current_measurement_id, measurement_sleep, true);
    int acc_x = get_measure(current_measurement_id, measurement_acc_x, true);
    int acc_y = get_measure(current_measurement_id, measurement_acc_y, true);
    int acc_z = get_measure(current_measurement_id, measurement_acc_z, true);
    
    APP_LOG(APP_LOG_LEVEL_INFO, "Number of steps %d.", steps);
    APP_LOG(APP_LOG_LEVEL_INFO, "Light level %d.", avg_light_level);

    // Declare the dictionary's iterator
    DictionaryIterator *out_iter;

    // open the app message
    app_message_open(64, 256);

    // prepare the outbox buffer for this message
    AppMessageResult result = app_message_outbox_begin(&out_iter);
    if(result == APP_MSG_OK) {
      dict_write_int(out_iter, MESSAGE_KEY_steps, &steps, sizeof(int), true);
      dict_write_int(out_iter, MESSAGE_KEY_current_time, &current_time, sizeof(int), true);
      dict_write_int(out_iter, MESSAGE_KEY_min_bpm, &min_bpm, sizeof(int), true);
      dict_write_int(out_iter, MESSAGE_KEY_max_bpm, &max_bpm, sizeof(int), true);
      dict_write_int(out_iter, MESSAGE_KEY_avg_bpm, &avg_bpm, sizeof(int), true);
      dict_write_int(out_iter, MESSAGE_KEY_avg_light_level, &avg_light_level, sizeof(int), true);
      dict_write_int(out_iter, MESSAGE_KEY_activity, &activity, sizeof(int), true);
      dict_write_int(out_iter, MESSAGE_KEY_sleep, &sleep, sizeof(int), true);
      dict_write_int(out_iter, MESSAGE_KEY_acc_x, &acc_x, sizeof(int), true);
      dict_write_int(out_iter, MESSAGE_KEY_acc_y, &acc_y, sizeof(int), true);
      dict_write_int(out_iter, MESSAGE_KEY_acc_z, &acc_z, sizeof(int), true);

      // send this message
      result = app_message_outbox_send();
      if(result != APP_MSG_OK) {
        APP_LOG(APP_LOG_LEVEL_ERROR, "Error sending the outbox: %d", (int)result);
      }
    } else {
      // the outbox cannot be used right now
      APP_LOG(APP_LOG_LEVEL_ERROR, "Error preparing the outbox: %d", (int)result);
    }

    // go to next dataset
    current_measurement_id++;
  } else {
    APP_LOG(APP_LOG_LEVEL_INFO, "Finished processing all data (Last id was %d)", (current_measurement_id - 1));
  }
}

static void outbox_sent_handler(DictionaryIterator *iter, void *context) {
  perform_upload();
}

bool upload_iteration() {
  int lastId = get_last_measure_id();
  if(lastId == 0) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "There is no data in the storage to upload!!");
    return false;
  } else {
    APP_LOG(APP_LOG_LEVEL_INFO, "Last inserted id is %d.", lastId);
    current_measurement_id = 1;
    perform_upload();
    return true;
  }
}

void worker_message_handler(uint16_t type, AppWorkerMessage *message) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Got a message");
  if(type == SOURCE_BACKGROUND) {
    int action = message->data0;
    if(action == 4711) {
      APP_LOG(APP_LOG_LEVEL_INFO, "We have to upload the data saved on storage..");
      app_message_register_outbox_sent(outbox_sent_handler);
      upload_iteration();
    }
  }
}