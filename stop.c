#include "juma_sdk_api.h"
#include "model_contral.h"
#include "ssd1306.h"
#include "jump.h"


void system_off()
{
  gfx_clear();
  OLED_Refresh_all();
  gfx_set_font(&Helvetica_16);
  gfx_draw_string(10, 10, "Bye Bye ...", GFX_SET_BLACK);
  OLED_Refresh_all();
  
  gpio_setup(POWER_PIN, GPIO_OUTPUT);
  gpio_write(POWER_PIN, 0);
}
