#include <stdio.h>
#include <math.h>
#include "rocket.h"

#define GRAVITY_ACCELERATION 9.81
#define DELTA_T 0.001

// ROCKET FUNCTIONS
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

double rocket_get_air_density_at_altitude(float altitude) {
    // Source: https://www.grc.nasa.gov/www/k-12/airplane/atmosmet.html
    float temperature_c;
    float pressure_kpa;
    if (altitude > 25000) {
        temperature_c = -131.21 + 0.00299 * altitude;
        pressure_kpa = 2.488 * pow((temperature_c + 273.1) / 216.6, -11.388);
    } else if (11000 < altitude && altitude <= 25000)
    {
        temperature_c = -56.46;
        pressure_kpa = 22.65 * exp(1.73 - 0.000157 * altitude);
    } else if (0 <= altitude && altitude <= 11000) {
        temperature_c = 15.04 - 0.00649 * altitude;
        pressure_kpa = 101.29 * pow((temperature_c + 273.1) / 288.08, 5.256);
    } else {
        perror("rocket_get_air_density_at_altitude: provided altitude is negative");
    }
    return pressure_kpa / (0.2869 * (temperature_c + 273.1));
}

// ROCKET MAIN
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
    
    f_thrust -= 0.5 * rocket_get_air_density_at_altitude(r->altitude) * pow(r->velocity, 2) * r->drag_coefficient * r->cross_section_area;

    r->acceleration = (f_thrust / rocket_get_mass(r)) - GRAVITY_ACCELERATION;
    r->velocity += r->acceleration * DELTA_T;
    r->altitude += r->velocity * DELTA_T + 0.5 * r->acceleration * pow(DELTA_T, 2);

    if (r->fuel_mass < 0) {
        r->fuel_mass = 0;
    }
}