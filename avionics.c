#include <stdio.h>
#include "rocket.h"

// MAIN
int main() {
    Rocket rocket;
    rocket_init(&rocket);

    rocket.thruster_level = 1;
    do {
        rocket_update(&rocket);
        printf("Alt: %f m | Vel: %f m/s | Acc: %f m/s2 | Fuel: %f\n", rocket.altitude, rocket.velocity, rocket.acceleration, rocket.fuel_mass);
    } while (rocket.altitude > 0);

    return 0;
}