#include <stdio.h>
#include <math.h>
#include "../include/environment.h"

double environment_get_air_density_at_altitude(float altitude) {
    // Source: https://www.grc.nasa.gov/www/k-12/airplane/atmosmet.html
    float temperature_c;
    float pressure_kpa;
    if (altitude > 25000) {
        temperature_c = -131.21 + 0.00299 * altitude;
        pressure_kpa = 2.488 * pow((temperature_c + 273.1) / 216.6, -11.388);
    } else if (11000 < altitude && altitude <= 25000) {
        temperature_c = -56.46;
        pressure_kpa = 22.65 * exp(1.73 - 0.000157 * altitude);
    } else if (0 <= altitude && altitude <= 11000) {
        temperature_c = 15.04 - 0.00649 * altitude;
        pressure_kpa = 101.29 * pow((temperature_c + 273.1) / 288.08, 5.256);
    } else {
        perror("environment_get_air_density_at_altitude: provided altitude is negative");
    }
    
    return pressure_kpa / (0.2869 * (temperature_c + 273.1));
}

double environment_get_earth_acceleration_at_altitude(float altitude) {
    return (6.674e-11 * 5.972e24) / pow(6371000 + altitude, 2);
}