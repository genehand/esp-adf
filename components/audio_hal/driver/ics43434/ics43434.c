/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2019 <ESPRESSIF SYSTEMS (SHANGHAI) CO., LTD>
 *
 * Permission is hereby granted for use on all ESPRESSIF SYSTEMS products, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <string.h>
#include "ics43434.h"
#include "i2c_bus.h"
#include "board.h"
#include "esp_log.h"

#define ES_ASSERT(a, format, b, ...) \
    if ((a) != 0) { \
        ESP_LOGE(TAG, format, ##__VA_ARGS__); \
        return b;\
    }

static char *TAG = "DRV43434";
static i2c_bus_handle_t i2c_handle;
static int ics43434_addr = 0x26;

audio_hal_func_t AUDIO_CODEC_ICS43434_DEFAULT_HANDLE = {
    .audio_codec_initialize = ics43434_adc_init,
    .audio_codec_deinitialize = ics43434_adc_deinit,
    .audio_codec_ctrl = ics43434_adc_ctrl_state,
    .audio_codec_config_iface = ics43434_adc_config_i2s,
    .audio_codec_set_mute = NULL,
    .audio_codec_set_volume = ics43434_adc_set_voice_volume,
    .audio_codec_get_volume = ics43434_adc_get_voice_volume,
    .audio_hal_lock = NULL,
    .handle = NULL,
};

// static esp_err_t ics43434_write_reg(uint8_t reg_add, uint8_t data)
// {
//     return i2c_bus_write_bytes(i2c_handle, ics43434_addr, &reg_add, sizeof(reg_add), &data, sizeof(data));
// }

static int i2c_init()
{
    int res = 0;
    i2c_config_t es_i2c_cfg = {
        .mode = I2C_MODE_MASTER,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000,
    };
    res = get_i2c_pins(I2C_NUM_0, &es_i2c_cfg);
    ES_ASSERT(res, "getting i2c pins error", -1);
    i2c_handle = i2c_bus_create(I2C_NUM_0, &es_i2c_cfg);
    return res;
}

esp_err_t ics43434_adc_set_addr(int addr)
{
    ics43434_addr = addr;
    return ESP_OK;
}

esp_err_t ics43434_adc_init(audio_hal_codec_config_t *codec_cfg)
{
    i2c_init();
    return ESP_OK;
}

esp_err_t ics43434_adc_deinit(void)
{
    return ESP_OK;
}

esp_err_t ics43434_adc_ctrl_state(audio_hal_codec_mode_t mode, audio_hal_ctrl_t ctrl_state)
{
    return ESP_OK;
}

esp_err_t ics43434_adc_config_i2s(audio_hal_codec_mode_t mode, audio_hal_codec_i2s_iface_t *iface)
{
    return ESP_OK;
}


esp_err_t ics43434_adc_set_voice_volume(int volume)
{
    return ESP_OK;
}

esp_err_t ics43434_adc_get_voice_volume(int *volume)
{
    return ESP_OK;
}
