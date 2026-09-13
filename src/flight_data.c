#include "../include/flight_data.h"
#include "../include/rocket.h"

void flight_data_record(FlightData *data, Rocket *r) {
    if (r->acceleration > data->max_acceleration) {data->max_acceleration = r->acceleration;}
    if (r->velocity > data->max_velocity) {data->max_velocity = r->velocity;}
    if (r->altitude > data->max_altitude) {data->max_altitude = r->altitude;}
    data->flight_time += 0.001;
}