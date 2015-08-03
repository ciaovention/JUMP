#include "juma_sdk_api.h"
#include "model_contral.h"
#include "ssd1306.h"
#include "jump.h"
#include "stdio.h"

uint32_t normal_jump_value;

uint8_t color[4];

static void refresh_screen()
{
  char buff[125];
  
  if(screen_is_on)
  {
    gfx_clear();
    sprintf(buff, "NO. %05d", normal_jump_value);
    gfx_set_font(&Helvetica_16);
    gfx_draw_string(10, 10, buff, GFX_SET_BLACK);
    OLED_Refresh_all();
  }
}

static void two_click()
{
  uint8_t color[]={255, 0, 0};
  light_set_color(color);
  light_on();
}

static void hall_change()
{

  normal_jump_value++;
refresh_screen();
}

static void on_timer()
{//100ms 
  
  color[0] += 255;
  color[1] += 200;
  color[2] += 100;
  
  light_set_color(color);
  light_on();
}

void normal_model_enter()
{
  char buff[125];
  
  color[0] = 255;
  color[1] = 0;
  color[2] = 0;
  
  two_click_function_point = two_click;
  gpio_change_point = hall_change;
  normal_jump_value = 0;
  timer_point       = on_timer;
  
  timer_init(9);
  timer_start(3125);
  
  refresh_screen();
}

void normal_model_exit()
{
  two_click_function_point = NULL;
  
  gfx_clear();
  OLED_Clear();
  OLED_Refresh_all();
}

