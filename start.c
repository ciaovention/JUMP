#include "juma_sdk_api.h"
#include "model_contral.h"
#include "ssd1306.h"
#include "jump.h"

uint8_t system_start_process_var;

void system_open(void * args);


void system_start_process(void * args);
void system_start(void * args)
{
  system_start_process_var = 0;
  
  if(!gpio_read(BUTTON))
  {
    gfx_clear();
    gfx_draw_rect(10, 10, 110, 20, GFX_SET_BLACK);
    OLED_Refresh_all();
    run_after_delay(system_start_process, NULL, 10);
  }
}

void system_open(void * args);
void system_start_process(void * args)
{
  if(!gpio_read(BUTTON))
  {
    system_start_process_var += 10;
    gfx_fill_rect(10, 10, 10+system_start_process_var, 20, GFX_SET_BLACK);
    OLED_Refresh_all();
    if(system_start_process_var >= 100)
    {
      run_when_idle(system_open, NULL);
    }
    else 
    {
      run_after_delay(system_start_process, NULL, 10);
    }
  }
}

void on_sys_open();
void system_open(void * args)
{
  if(!gpio_read(BUTTON))
  {
    gpio_setup(POWER_PIN, GPIO_OUTPUT);
    gpio_write(POWER_PIN, 1);
    
    on_sys_open();
  }
}


void system_start_enter()
{

}

void system_start_exit()
{

}

