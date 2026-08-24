#include "board.h"

static adc_oneshot_unit_handle_t adc_handle;

void board_init(void)
{
    gpio_config_t button_config = {
        .pin_bit_mask = (1ULL << BOARD_BUTTON_GPIO),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&button_config);

    gpio_config_t pir_config = {
        .pin_bit_mask = (1ULL << BOARD_PIR_GPIO),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&pir_config);

    gpio_config_t output_config = {
        .pin_bit_mask =
            (1ULL << BOARD_LED_GPIO) |
            (1ULL << BOARD_BUZZER_GPIO),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&output_config);

    gpio_set_level(BOARD_LED_GPIO, 0);
    gpio_set_level(BOARD_BUZZER_GPIO, 0);

    adc_oneshot_unit_init_cfg_t adc_config = {
        .unit_id = ADC_UNIT_1
    };

    adc_oneshot_new_unit(
        &adc_config,
        &adc_handle
    );

    adc_oneshot_chan_cfg_t channel_config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12
    };

    adc_oneshot_config_channel(
        adc_handle,
        BOARD_LIGHT_ADC_CHANNEL,
        &channel_config
    );
}

adc_oneshot_unit_handle_t board_get_adc_handle(void)
{
    return adc_handle;
}