/*
  Copyright 2014-2015 juma.io

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
       http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "juma_sdk_api.h"
#include "model_contral.h"
#include "ssd1306.h"
#include "jump.h"

void (* gpio_change_point) (void);
void (* timer_point)        (void);
void (* on_message)         (uint8_t type, uint16_t length, uint8_t* value);

void sys_driver_init()
{
  //open screen
  gpio_setup(SCREES_DC, GPIO_OUTPUT);
  gpio_write(SCREES_DC, 0);
  //screen reset
  gpio_setup(SCREES_RES, GPIO_OUTPUT);
  gpio_write(SCREES_RES, 1);
  
  //rgb led
  uint8_t led_pin[] = {28, 29, 30};
  light_setup(led_pin, 0);
  

  //init screen
  SSD1306_Init_Struct init_struct;
  init_struct.SCL = 9;
  init_struct.SDA = 8;

  ssd1306_config(&init_struct);
  
  OLED_Init();    
  OLED_Clear();
  
  gfx_init_screen((uint8_t *)&screen, 128, 32, 1);
  gfx_clear();
  OLED_Refresh_all();
  
  //hall task
  gpio_change_point = NULL;
  gpio_watch(HALL, GPIO_FALLING);
  
  //button
  gpio_setup(BUTTON, GPIO_INPUT_PULLUP);
}

void system_start(void * args);
void on_ready()
{
  sys_driver_init();
 
  run_after_delay(system_start, NULL, 20);
}

void on_sys_open()
{
  model_contral_init();
  
  ble_device_set_name("JUMP");
  ble_device_start_advertising();
}

void ble_device_on_connect(void)
{

}

void ble_device_on_disconnect(uint8_t reason)
{
  ble_device_start_advertising();
}

void ble_device_on_message(uint8_t type, uint16_t length, uint8_t* value)
{
  if(on_message) on_message(type, length, value);
}

void gpio_on_change(uint32_t pins_state)
{
  hall_change_for_contral();
  if(gpio_change_point) gpio_change_point();
}

void timer_on_fired(void)
{
  if(timer_point) timer_point();
}

