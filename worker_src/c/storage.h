#pragma once
#include "src/c/storage.h"

enum StatusCode save_measure(enum MeasureType type, int value, int id);
int get_last_measure_id();