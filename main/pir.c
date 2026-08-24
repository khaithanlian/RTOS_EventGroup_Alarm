#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include <stdbool.h>
#include <stdio.h>

#include "board.h"
#include "pir.h"
#include "event_controller.h"

#define PIR_POLL_MS 100

static EventGroupHandle_t system_events;

static void pir_task(void *pvParameters)
{
    bool previous_motion = false;

    while (1)
    {
        bool motion =
            (gpio_get_level(BOARD_PIR_GPIO) == 1);

        if (motion != previous_motion)
        {
            if (motion)
            {
                xEventGroupSetBits(
                    system_events,
                    MOTION_BIT
                );

                printf("PIR: MOTION DETECTED\n");
            }
            else
            {
                xEventGroupClearBits(
                    system_events,
                    MOTION_BIT
                );

                printf("PIR: NO MOTION\n");
            }

            xEventGroupSetBits(
                system_events,
                EVENT_CHANGED_BIT
            );

            previous_motion = motion;
        }

        vTaskDelay(
            pdMS_TO_TICKS(PIR_POLL_MS)
        );
    }
}

void pir_start(EventGroupHandle_t event_group)
{
    system_events = event_group;

    xTaskCreate(
        pir_task,
        "PIRTask",
        2048,
        NULL,
        5,
        NULL
    );
}