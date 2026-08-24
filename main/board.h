#ifndef BOARD_H
#define BOARD_H

#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"

#define BOARD_BUTTON_GPIO       GPIO_NUM_12
#define BOARD_PIR_GPIO          GPIO_NUM_15
#define BOARD_LIGHT_ADC_CHANNEL ADC_CHANNEL_6
#define BOARD_LED_GPIO          GPIO_NUM_2
#define BOARD_BUZZER_GPIO       GPIO_NUM_25

void board_init(void);

adc_oneshot_unit_handle_t board_get_adc_handle(void);

#endif