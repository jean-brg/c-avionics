#include <stdio.h>
#include <math.h>
#include "../include/rocket.h"
#include "../include/environment.h"

#define DELTA_T 0.001

void rocket_init(Rocket *r) {
    r->body_mass = 10;
    r->fuel_mass = 8;
    r->max_fuel_flow_rate = 0.0012;
    r->max_thrust = 2950;
    r->drag_coefficient = 0.45;
    r->cross_section_area = 0.007854;
    r->thruster_level = 0;
    r->flight_time = 0;
    r->acceleration = 0;
    r->velocity = 0;
    r->altitude = 0;
}

float rocket_get_mass(Rocket *r) {
    return r->body_mass + r->fuel_mass;
}

void rocket_update(Rocket *r) {
    r->flight_time += 1;

    float f_thrust = 0;
    float required_fuel_mass = r->thruster_level * r->max_fuel_flow_rate;
    if (r->fuel_mass >= required_fuel_mass) {
        f_thrust = r->max_thrust * r->thruster_level;
        r->fuel_mass -= required_fuel_mass;
    } else {
        f_thrust = (r->max_thrust * r->thruster_level) * (r->fuel_mass / required_fuel_mass);
        r->fuel_mass = 0;
    }
    
    f_thrust -= 0.5 * environment_get_air_density_at_altitude(r->altitude) * (fabs(r->velocity) * r->velocity) * r->drag_coefficient * r->cross_section_area;

    r->acceleration = (f_thrust / rocket_get_mass(r)) - environment_get_earth_acceleration_at_altitude(r->altitude);
    r->velocity += r->acceleration * DELTA_T;
    r->altitude += r->velocity * DELTA_T + 0.5 * r->acceleration * pow(DELTA_T, 2);

    if (r->fuel_mass < 0) {
        r->fuel_mass = 0;
    }
}