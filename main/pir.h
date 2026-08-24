#ifndef PIR_H
#define PIR_H

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

void pir_start(EventGroupHandle_t event_group);

#endif
