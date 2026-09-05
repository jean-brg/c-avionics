#include <stdio.h>
#include "rocket.h"

#define GRAVITY_ACCELERATION 9.81
#define DELTA_T 0.001

// ROCKET FUNCTIONS
void rocket_init(Rocket *r) {
    r->body_mass = 10;
    r->fuel_mass = 8;
    r->max_fuel_flow_rate = 0.0012;
    r->max_thrust = 2950;
    r->thruster_level = 0;
    r->flight_time = 0;
    r->acceleration = 0;
    r->velocity = 0;
    r->altitude = 0;
}

float rocket_get_mass(Rocket *r) {
    return r->body_mass + r->fuel_mass;
}

// ROCKET MAIN
void rocket_update(Rocket *r) {
    r->flight_time += 1;

    float f_thrust = 0;
    float required_fuel_mass = r->thruster_level * r->max_fuel_flow_rate;
    if (required_fuel_mass >= r->fuel_mass) {
        f_thrust = r->max_thrust * r->thruster_level;
        r->fuel_mass -= required_fuel_mass;
    } else {
        f_thrust = (r->max_thrust * r->thruster_level) * (r->fuel_mass / required_fuel_mass);
        r->fuel_mass = 0;
    }

    r->acceleration = (f_thrust / rocket_get_mass(r)) - GRAVITY_ACCELERATION;
    r->velocity += r->acceleration * DELTA_T;
    r->altitude += r->velocity * DELTA_T + 0.5 * r->acceleration * DELTA_T * DELTA_T;

    if (r->fuel_mass < 0) {
        r->fuel_mass = 0;
    }
}