#include "./rocket.h"

#ifndef FLIGHT_DATA_H
#define FLIGHT_DATA_H

typedef struct {
    float max_acceleration;
    float max_velocity;
    float max_altitude;
    float flight_time;
} FlightData;

void flight_data_record(FlightData *data, Rocket *r);

# endif