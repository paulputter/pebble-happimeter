#pragma once

typedef struct {
    int Steps;
    int SleepSeconds;
    int CurrentActivity;
    int AverageLightLevel;
    int MaxHeartRate;
    int MinHeartRate;
    int AverageHeartRate;
    int AccX;
    int AccY;
    int AccZ;
    time_t Time;
} HealthMeasure;

void measure_iteration(time_t current_time);