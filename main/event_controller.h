#ifndef EVENT_CONTROLLER_H
#define EVENT_CONTROLLER_H

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

#define ARMED_BIT         (1 << 0)
#define MOTION_BIT        (1 << 1)
#define DARK_BIT          (1 << 2)
#define EVENT_CHANGED_BIT (1 << 3)

void event_controller_start(void);

EventGroupHandle_t event_controller_get_event_group(void);

#endif