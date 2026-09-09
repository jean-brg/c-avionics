#ifndef ROCKET_H
#define ROCKET_H

typedef struct {
    float body_mass; // In kg
    float fuel_mass; // In kg
    float max_fuel_flow_rate; // In kg/ms
    float max_thrust; // In N
    float drag_coefficient; // Coefficient
    float cross_section_area; // In m^2

    float thruster_level; // In decimal percentage

    float flight_time; // In ms
    float acceleration; // In m/s^2
    float velocity; // In m/s
    float altitude; // In m
} Rocket;

void rocket_init(Rocket *r);
float rocket_get_mass(Rocket *r);
void rocket_update(Rocket *r);

# endif