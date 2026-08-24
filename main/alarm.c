#include "board.h"
#include "alarm.h"

void alarm_init(void)
{
    gpio_set_level(BOARD_LED_GPIO, 0);

    gpio_set_level(BOARD_BUZZER_GPIO, 0);
}

void alarm_set(bool active)
{
    gpio_set_level(BOARD_LED_GPIO, active ? 1 : 0);

    gpio_set_level(BOARD_BUZZER_GPIO,active ? 1 : 0);
}