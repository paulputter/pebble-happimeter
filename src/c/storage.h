#pragma once

enum MeasureType {
  measurement_steps           = 10,
  measurement_avg_bpm         = 11,
  measurement_min_bpm         = 12,
  measurement_max_bpm         = 13,
  measurement_avg_light_level = 14,
  measurement_activity        = 15,
  measurement_sleep           = 16,
  measurement_current_time    = 17,
  measurement_acc_x           = 18,
  measurement_acc_y           = 19,
  measurement_acc_z           = 20,
};

int get_last_measure_id();
int get_measure(int id, enum MeasureType type, bool removeAfterRead);