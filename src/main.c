#include <stdio.h>
#include <stdbool.h>
#include "../include/rocket.h"
#include "../include/flight_data.h"

// SETTINGS
static const bool verbose_output = false;

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
    printf(
        "=== FLIGHT SUMMARY ===\n"
        "Max Alt: %f m\n"
        "Max Vel: %f m/s\n"
        "Max Acc: %f m/s2 (%.2f g's)\n"
        "Flight Time: %f sec\n"
        "======================\n", 
        flight_data.max_altitude, 
        flight_data.max_velocity, 
        flight_data.max_acceleration, 
        flight_data.max_acceleration / 9.81, 
        flight_data.flight_time
    );

    return 0;
}