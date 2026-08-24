#include "esp_adc/adc_oneshot.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include <stdbool.h>
#include <stdio.h>

#include "board.h"
#include "light_sensor.h"
#include "event_controller.h"

#define LIGHT_SENSOR_POLL_MS 500
#define DARK_THRESHOLD 2995

static EventGroupHandle_t system_events;
static adc_oneshot_unit_handle_t adc_handle;

static void light_sensor_task(void *pvParameters)
{
    int adc_value;
    bool previous_dark = false;

    while (1)
    {
        if (adc_oneshot_read(
                adc_handle,
                BOARD_LIGHT_ADC_CHANNEL,
                &adc_value
            ) == ESP_OK)
        {
            printf("Light Sensor: ADC=%d\n", adc_value);
            bool dark = (adc_value > DARK_THRESHOLD);

            if (dark != previous_dark)
            {
                if (dark)
                {
                    xEventGroupSetBits(
                        system_events,
                        DARK_BIT
                    );

                    printf(
                        "Light Sensor: DARK, ADC=%d\n",
                        adc_value
                    );
                }
                else
                {
                    xEventGroupClearBits(
                        system_events,
                        DARK_BIT
                    );

                    printf(
                        "Light Sensor: BRIGHT, ADC=%d\n",
                        adc_value
                    );
                }

                xEventGroupSetBits(
                    system_events,
                    EVENT_CHANGED_BIT
                );

                previous_dark = dark;
            }
        }

        vTaskDelay(
            pdMS_TO_TICKS(LIGHT_SENSOR_POLL_MS)
        );
    }
}

void light_sensor_start(
    EventGroupHandle_t event_group
)
{
    system_events = event_group;

    adc_handle = board_get_adc_handle();

    xTaskCreate(
        light_sensor_task,
        "LightSensorTask",
        4096,
        NULL,
        5,
        NULL
    );
}