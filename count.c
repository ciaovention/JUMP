#include "juma_sdk_api.h"
#include "model_contral.h"
#include "ssd1306.h"
#include "jump.h"


static void two_click(void)
{

}

void count_model_enter()
{
  gfx_set_font(&Helvetica_16);
  gfx_draw_string(10, 10, "Count", GFX_SET_BLACK);
  OLED_Refresh_all();
}

void count_model_exit()
{
  gfx_clear();
  OLED_Clear();
  OLED_Refresh_all();
}
