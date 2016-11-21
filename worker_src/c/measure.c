#include <pebble_worker.h>
#include "measure.h"
#include "worker_src/c/data_collection_worker.h"
#include "worker_src/c/storage.h"
#include "src/c/storage.h"

// returns the available health minute history records to calculate average BPM and ambient light level 
static uint32_t get_available_records(HealthMinuteData *array, time_t query_start, time_t query_end, uint32_t max_records) {
  time_t next_start = query_start;
  time_t next_end = query_end;
  uint32_t num_records_found = 0;

  // Find more records until no more are returned
  while (num_records_found < max_records) {
    int ask_num_records = max_records - num_records_found;
    uint32_t ret_val = health_service_get_minute_history(&array[num_records_found], ask_num_records, &next_start, &next_end);
  
    if (ret_val == 0) {
      // a 0 return value means no more data is available
      return num_records_found;
    }
    
    num_records_found += ret_val;
    next_start = next_end;
    next_end = query_end;
  } 

  return num_records_found;
}

// calculates the average heart rate and ambient light level 
static void calculate_heart_rate_statistics_and_ambient_light(HealthMeasure* measure, time_t query_start, time_t query_end) {
  // Prepare values
  measure->AverageLightLevel = 0;
  measure->MaxHeartRate = 0;
  measure->MinHeartRate = 0;
  measure->AverageHeartRate = 0;
  int validRecords = 0;
  
  uint32_t max_records = (query_end - query_start) / SECONDS_PER_MINUTE;
  APP_LOG(APP_LOG_LEVEL_INFO, "#1 MAX RECORDS %d", (int) max_records);
  HealthMinuteData *data = (HealthMinuteData*)malloc(max_records * sizeof(HealthMinuteData));

  // Populate the array
  max_records = get_available_records(data, query_start, query_end, max_records);

  APP_LOG(APP_LOG_LEVEL_INFO, "#2 MAX RECORDS %d", (int) max_records);
  // Calculate the measures
  for(uint32_t i = 0; i < max_records; i++) {
    if(!data[i].is_invalid) {
      validRecords++;
      APP_LOG(APP_LOG_LEVEL_INFO, "AVG LIGHT %d", (int) data[i].light);
      measure->AverageLightLevel = measure->AverageLightLevel + (int) data[i].light;
      measure->AverageHeartRate += (int)data[i].heart_rate_bpm;

      if(measure->MinHeartRate == 0 || measure->MinHeartRate > (int)data[i].heart_rate_bpm) {
        measure->MinHeartRate = (int)data[i].heart_rate_bpm;
      }

      if(measure->MaxHeartRate == 0 || measure->MaxHeartRate < (int)data[i].heart_rate_bpm) {
        measure->MaxHeartRate = (int)data[i].heart_rate_bpm;
      }
    } else {
      APP_LOG(APP_LOG_LEVEL_INFO, "Record %d was not valid.", (int)i);
    }
  }

  query_end = query_start;
  free(data);
  
  measure->AverageLightLevel = measure->AverageLightLevel / validRecords;
  measure->AverageHeartRate = measure->AverageHeartRate / validRecords;
}

// calculates all health metrics and store them in the global variables
HealthMeasure receive_health_metrics(time_t time) {
  time_t end_time = time - SECONDS_PER_MINUTE * 15; // skip the last 15 Minutes, since there is no guarantee for available data
  time_t start_time = end_time - SECONDS_PER_MINUTE * UPDATE_INTERVAL_IN_MINUTES;
  struct tm *tick_time = localtime(&end_time);
  
  APP_LOG(APP_LOG_LEVEL_INFO, "Looking for datasets.. %d:%d", tick_time->tm_hour, tick_time->tm_min);
  
  HealthMeasure measure;
  measure.Time = time;
  measure.Steps = health_service_sum(HealthMetricStepCount, start_time , end_time);
  measure.SleepSeconds = health_service_sum(HealthMetricSleepSeconds, start_time, end_time);
  measure.CurrentActivity = health_service_peek_current_activities();
  calculate_heart_rate_statistics_and_ambient_light(&measure, start_time, end_time);
  
  AccelData accel = (AccelData) { .x = 0, .y = 0, .z = 0 };
  accel_service_peek(&accel);
  measure.AccX = accel.x;
  measure.AccY = accel.y;
  measure.AccZ = accel.z;
  
  // exemplary output some of the measures
  APP_LOG(APP_LOG_LEVEL_INFO, "Number of steps: %d", measure.Steps);
  APP_LOG(APP_LOG_LEVEL_INFO, "Average Heart Rate is: %d", measure.AverageHeartRate);
  APP_LOG(APP_LOG_LEVEL_INFO, "Activity is: %d", measure.CurrentActivity);
  APP_LOG(APP_LOG_LEVEL_INFO, "Average Ambient Light is: %d", measure.AverageLightLevel);  
  APP_LOG(APP_LOG_LEVEL_INFO, "Acc X: %d", measure.AccX);  
  APP_LOG(APP_LOG_LEVEL_INFO, "Acc Y: %d", measure.AccY);  
  APP_LOG(APP_LOG_LEVEL_INFO, "Acc Z: %d", measure.AccZ);  
  return measure;
}

void measure_iteration(time_t current_time) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Its time for a scheduled measurement update.");

  // get the measures for the current iteration
  HealthMeasure measure = receive_health_metrics(current_time);

  // store data in the storage
  int id = get_last_measure_id() + 1;
  save_measure(measurement_steps, measure.Steps, id);
  save_measure(measurement_avg_bpm, measure.AverageHeartRate, id);
  save_measure(measurement_min_bpm, measure.MinHeartRate, id);
  save_measure(measurement_max_bpm, measure.MaxHeartRate, id);
  save_measure(measurement_avg_light_level, measure.AverageLightLevel, id);
  save_measure(measurement_activity, measure.CurrentActivity, id);
  save_measure(measurement_sleep, measure.SleepSeconds, id);
  save_measure(measurement_current_time, measure.Time, id);
  save_measure(measurement_acc_x, measure.AccX, id);
  save_measure(measurement_acc_y, measure.AccY, id);
  save_measure(measurement_acc_z, measure.AccZ, id);
}