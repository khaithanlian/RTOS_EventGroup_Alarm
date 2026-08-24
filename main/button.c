#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include <stdbool.h>
#include <stdio.h>

#include "board.h"
#include "button.h"
#include "event_controller.h"

#define BUTTON_POLL_MS 20

static EventGroupHandle_t system_events;

static void button_task(void *pvParameters)
{
    bool was_pressed = false;

    while (1)
    {
        bool pressed =
            (gpio_get_level(BOARD_BUTTON_GPIO) == 0);

        if (pressed && !was_pressed)
        {
            EventBits_t bits =
                xEventGroupGetBits(system_events);

            if (bits & ARMED_BIT)
            {
                xEventGroupClearBits(
                    system_events,
                    ARMED_BIT
                );

                printf("Button: SYSTEM DISARMED\n");
            }
            else
            {
                xEventGroupSetBits(
                    system_events,
                    ARMED_BIT
                );

                printf("Button: SYSTEM ARMED\n");
            }

            xEventGroupSetBits(
                system_events,
                EVENT_CHANGED_BIT
            );
        }

        was_pressed = pressed;

        vTaskDelay(
            pdMS_TO_TICKS(BUTTON_POLL_MS)
        );
    }
}

void button_start(EventGroupHandle_t event_group)
{
    system_events = event_group;

    xTaskCreate(
        button_task,
        "ButtonTask",
        2048,
        NULL,
        5,
        NULL
    );
}