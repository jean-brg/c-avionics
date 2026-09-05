#include <stdio.h>
#include <stdbool.h>
#include "rocket.h"

// SETTINGS
static const bool verbose_output = false;

// TELEMETRY
typedef struct {
    float max_acceleration;
    float max_velocity;
    float max_altitude;
    float flight_time;
} FlightData;

void flight_data_record(FlightData *data, Rocket *r) {
    if (r->acceleration > data->max_acceleration) {data->max_acceleration = r->acceleration;}
    if (r->velocity > data->max_velocity) {data->max_velocity = r->velocity;}
    if (r->altitude > data->max_altitude) {data->max_altitude = r->altitude;}
    data->flight_time += 0.001;
}

// MAIN
int main() {
    Rocket rocket;
    rocket_init(&rocket);

    FlightData flight_data = {0, 0, 0, 0};

    rocket.thruster_level = 1;
    do {
        rocket_update(&rocket);
        if (verbose_output) {
            printf("Alt: %f m | Vel: %f m/s | Acc: %f m/s2 | Fuel: %f\n", rocket.altitude, rocket.velocity, rocket.altitude, rocket.fuel_mass);
        }
        flight_data_record(&flight_data, &rocket);
    } while (rocket.altitude > 0);
    printf("Max Alt: %f m | Max Vel: %f m/s | Max Acc: %f m/s2 | Flight Time: %f sec\n", flight_data.max_altitude, flight_data.max_velocity, flight_data.max_acceleration, flight_data.flight_time);

    return 0;
}