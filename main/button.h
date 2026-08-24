#ifndef BUTTON_H
#define BUTTON_H

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

void button_start(EventGroupHandle_t event_group);

#endif
