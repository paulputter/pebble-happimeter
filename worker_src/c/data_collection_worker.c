#include <pebble_worker.h>
#define SOURCE_FOREGROUND 0
#define SOURCE_BACKGROUND 1

// Constants
const TimeUnits UPDATE_INTERVAL = MINUTE_UNIT; // Set to Hour_Unit

// Health Measure struct
struct HealthMeasure
{
    int StepsPerDay;
    int RestingKCalories;
    int SleepSeconds;
    int SleepRestfulSeconds;
    int ActiveSeconds;
    int ActiveKCalories;
    int WalkedDistanceMeters;
    int CurrentActivity;
    int AverageLightLevel;
    int MaxHeartRate;
    int MinHeartRate;
    int AverageHeartRate;
};

// Data of the day for every hour
struct HealthMeasure fetchedData[24];

// Returns the available health minute history records to calculate average BPM and ambient light level 
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

// Calculates the average heart rate and ambient light level 
static void calculateHeartRateStatisticsAndAmbientlight(int hour) {
  // Prepare values
  fetchedData[hour].AverageLightLevel = 0;
  fetchedData[hour].MaxHeartRate = 0;
  fetchedData[hour].MinHeartRate = 0;
  fetchedData[hour].AverageHeartRate = 0;
  int validRecords = 0;
  
  // Query for the last hour, max 60 minute-level records
  time_t query_end = time(NULL); // now
  time_t query_start = 0;
  int minute_counter = 0;
  query_start = query_end - SECONDS_PER_MINUTE * 60; // one hour ago
  uint32_t max_records = (query_end - query_start) / SECONDS_PER_MINUTE;
  HealthMinuteData *data = (HealthMinuteData*)malloc(max_records * sizeof(HealthMinuteData));

  // Populate the array
  max_records = get_available_records(data, query_start, query_end, max_records);

  // Calculate the measures
  for(uint32_t i = 0; i < max_records; i++) {
    if(!data[i].is_invalid) {
      validRecords++;
      fetchedData[hour].AverageLightLevel = fetchedData[hour].AverageLightLevel + (int) data[i].light;
      fetchedData[hour].AverageHeartRate += (int)data[i].heart_rate_bpm;

      if(fetchedData[hour].MinHeartRate == 0 || fetchedData[hour].MinHeartRate > (int)data[i].heart_rate_bpm) {
        fetchedData[hour].MinHeartRate = (int)data[i].heart_rate_bpm;
      }

      if(fetchedData[hour].MaxHeartRate == 0 || fetchedData[hour].MaxHeartRate < (int)data[i].heart_rate_bpm) {
        fetchedData[hour].MaxHeartRate = (int)data[i].heart_rate_bpm;
      }
    } else {
      APP_LOG(APP_LOG_LEVEL_INFO, "Record %d was not valid.", (int)i);
    }
  }

  query_end = query_start;
  free(data);
  
  fetchedData[hour].AverageLightLevel = fetchedData[hour].AverageLightLevel / validRecords;
  fetchedData[hour].AverageHeartRate = fetchedData[hour].AverageHeartRate / validRecords;
}

// Calculates all health metrics and store them in the global variables
static void receiveHealthMetrics() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  int hour = tick_time->tm_hour;
  
  APP_LOG(APP_LOG_LEVEL_INFO, "Current hour: %d", hour);
  
  fetchedData[hour].StepsPerDay = health_service_sum(HealthMetricStepCount, hour - 1, hour);
  fetchedData[hour].RestingKCalories = health_service_sum(HealthMetricRestingKCalories, hour - 1, hour);
  fetchedData[hour].SleepSeconds = health_service_sum(HealthMetricSleepSeconds, hour - 1, hour);
  fetchedData[hour].SleepRestfulSeconds = health_service_sum(HealthMetricSleepRestfulSeconds, hour - 1, hour);
  fetchedData[hour].ActiveSeconds = health_service_sum(HealthMetricActiveSeconds, hour - 1, hour);
  fetchedData[hour].ActiveKCalories = health_service_sum(HealthMetricActiveKCalories, hour - 1, hour);
  fetchedData[hour].WalkedDistanceMeters = health_service_sum(HealthMetricWalkedDistanceMeters, hour - 1, hour);
  fetchedData[hour].CurrentActivity = health_service_peek_current_activities();
  calculateHeartRateStatisticsAndAmbientlight(hour);
  
  // Exemplary output of some measures
  APP_LOG(APP_LOG_LEVEL_INFO, "Number of steps: %d", fetchedData[hour].StepsPerDay);
  APP_LOG(APP_LOG_LEVEL_INFO, "Active seconds is: %d", fetchedData[hour].ActiveSeconds);
  APP_LOG(APP_LOG_LEVEL_INFO, "Average Heart Rate is: %d", fetchedData[hour].AverageHeartRate);
  APP_LOG(APP_LOG_LEVEL_INFO, "Activity is: %d", fetchedData[hour].CurrentActivity);
  APP_LOG(APP_LOG_LEVEL_INFO, "Average Ambient Light is: %d", fetchedData[hour].AverageLightLevel);  
  
  // Before we send the data lets open the app
  worker_launch_app();
  
  // Send the data synchroniously to the foreground app
  AppWorkerMessage message = { 
    .data0 = hour,
    .data1 = 0,
    .data2 = fetchedData[hour].StepsPerDay
  };
  app_worker_send_message(SOURCE_BACKGROUND, &message);
  
  AppWorkerMessage message2 = {
    .data0 = hour,
    .data1 = 1,
    .data2 = fetchedData[hour].RestingKCalories
  };
  app_worker_send_message(SOURCE_BACKGROUND, &message);
  
  AppWorkerMessage message3 = {
    .data0 = hour,
    .data1 = 2,
    .data2 = fetchedData[hour].SleepSeconds
  };
  app_worker_send_message(SOURCE_BACKGROUND, &message);
  
  AppWorkerMessage message4 = { 
    .data0 = hour, 
    .data1 = 3, 
    .data2 = fetchedData[hour].SleepRestfulSeconds
  };
  app_worker_send_message(SOURCE_BACKGROUND, &message);
  
  AppWorkerMessage message5 = { 
    .data0 = hour, 
    .data1 = 4, 
    .data2 = fetchedData[hour].ActiveSeconds 
  };
  app_worker_send_message(SOURCE_BACKGROUND, &message);
  
  AppWorkerMessage message6 = { 
    .data0 = hour, 
    .data1 = 5, 
    .data2 = fetchedData[hour].ActiveKCalories 
  };
  app_worker_send_message(SOURCE_BACKGROUND, &message);
  
  AppWorkerMessage message7 = { 
    .data0 = hour,
    .data1 = 6, 
    .data2 = fetchedData[hour].WalkedDistanceMeters
  };
  app_worker_send_message(SOURCE_BACKGROUND, &message);
  
  AppWorkerMessage message8 = {
    .data0 = hour,
    .data1 = 7,
    .data2 = fetchedData[hour].CurrentActivity
  };
  app_worker_send_message(SOURCE_BACKGROUND, &message);
  
  AppWorkerMessage message9 = { 
    .data0 = hour, 
    .data1 = 8, 
    .data2 = fetchedData[hour].WalkedDistanceMeters 
  };
  app_worker_send_message(SOURCE_BACKGROUND, &message);
  
  AppWorkerMessage message10 = { 
    .data0 = hour, 
    .data1 = 9, 
    .data2 = fetchedData[hour].AverageLightLevel 
  };
  app_worker_send_message(SOURCE_BACKGROUND, &message);
  
  AppWorkerMessage message11 = { 
    .data0 = hour, 
    .data1 = 10, 
    .data2 = fetchedData[hour].MaxHeartRate 
  };
  app_worker_send_message(SOURCE_BACKGROUND, &message);
  
  AppWorkerMessage message12 = { 
    .data0 = hour, 
    .data1 = 11, 
    .data2 = fetchedData[hour].MinHeartRate 
  };
  app_worker_send_message(SOURCE_BACKGROUND, &message);
  
  AppWorkerMessage message13 = { 
    .data0 = hour, 
    .data1 = 12, 
    .data2 = fetchedData[hour].AverageHeartRate
  };
  app_worker_send_message(SOURCE_BACKGROUND, &message);
}

// Called every UPDATE_INTERVAL and receives and stores the sensor updates
// that are going to be send to the server once per day
static void updates_tick_handler (struct tm *tick_time, TimeUnits changed) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Its time to receive some sensor updates..");
  receiveHealthMetrics();
}

// Initialize the worker
static void init() {
  // Get first values for faster debugging purposes
  receiveHealthMetrics();
  
  // Get updates every UPDATE_INTERVAL
  tick_timer_service_subscribe(UPDATE_INTERVAL, updates_tick_handler);
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