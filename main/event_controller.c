#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include <stdio.h>

#include "board.h"
#include "button.h"
#include "pir.h"
#include "light_sensor.h"
#include "alarm.h"
#include "event_controller.h"

static EventGroupHandle_t system_events;

static void controller_task(void *pvParameters)
{
    EventBits_t bits;

    while (1)
    {
        xEventGroupWaitBits(
            system_events,
            EVENT_CHANGED_BIT,
            pdTRUE,
            pdFALSE,
            portMAX_DELAY
        );

        bits = xEventGroupGetBits(system_events);

        printf(
            "Controller: ARMED=%d MOTION=%d DARK=%d\n",
            (bits & ARMED_BIT) != 0,
            (bits & MOTION_BIT) != 0,
            (bits & DARK_BIT) != 0
        );

        if ((bits & (ARMED_BIT | MOTION_BIT | DARK_BIT)) ==
            (ARMED_BIT | MOTION_BIT | DARK_BIT))
        {
            printf("Controller: ALL CONDITIONS TRUE - ALARM ON\n");
            alarm_set(true);
        }
        else
        {
            printf("Controller: conditions incomplete - ALARM OFF\n");
            alarm_set(false);
        }
    }
}

void event_controller_start(void)
{
    board_init();

    system_events = xEventGroupCreate();

    if (system_events == NULL)
    {
        printf("ERROR: Event Group creation failed\n");
        return;
    }

    alarm_init();

    xTaskCreate(
        controller_task,
        "ControllerTask",
        4096,
        NULL,
        5,
        NULL
    );

    button_start(system_events);
    pir_start(system_events);
    light_sensor_start(system_events);

    printf("Event Group Alarm system started\n");
}

EventGroupHandle_t event_controller_get_event_group(void)
{
    return system_events;
}