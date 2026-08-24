#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

void light_sensor_start(EventGroupHandle_t event_group);

#endif
