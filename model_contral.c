#include "juma_sdk_api.h"
#include "model_contral.h"
#include "jump.h"

uint8_t model;
#define MODEL_MAX 5

uint8_t button_state1;
uint8_t button_state2;
uint8_t button_count;
uint8_t button_off_count;
uint8_t screen_is_on;

void (* two_click_function_point) (void);

#define NORMAL_MODEL  0
#define TIME_MODEL    1
#define TRAIN1_MODEL  2
#define TRAIN2_MODEL  3
#define TRAIN3_MODEL  4
#define TRAIN4_MODEL  5
#define COUNT_MODEL   6


void model_change()
{
  switch(model)
  {
    case NORMAL_MODEL:  normal_model_exit();  break;
    case TIME_MODEL:    timer_model_exit();   break;
    case TRAIN1_MODEL:  train1_model_exit();  break;
    case TRAIN2_MODEL:  train2_model_exit();  break;
    case TRAIN3_MODEL:  train3_model_exit();  break;
    case TRAIN4_MODEL:  train4_model_exit();  break;
    case COUNT_MODEL:   count_model_exit();   break;
  }
  
  model ++;
  if(model > COUNT_MODEL)
  {
    model = NORMAL_MODEL;
  }
  
  switch(model)
  {
    case NORMAL_MODEL: normal_model_enter();    break;
    case TIME_MODEL:   timer_model_enter();     break;
    case TRAIN1_MODEL: train1_model_enter();    break;
    case TRAIN2_MODEL: train2_model_enter();    break;
    case TRAIN3_MODEL: train3_model_enter();    break;
    case TRAIN4_MODEL: train4_model_enter();    break;
    case COUNT_MODEL:  count_model_enter();     break;
  }
}

void system_off(void);
static void button_one_click()
{
  model_change();
}

static void button_two_click()
{
  if(two_click_function_point) two_click_function_point();
}

static void button_long_push()
{
  if(system_off) system_off();
}

void hall_change_for_contral(void)
{

}

void button_scan(void * args);
void button_init()
{
  button_state1 = 1;
  button_state2 = 1;
  
  button_count = 0;
  button_off_count = 0;

  gpio_setup(BUTTON, GPIO_INPUT_PULLUP);  
  run_after_delay(button_scan, NULL, 2000);
}

void button_is_long_push(void * args)
{
  if((!gpio_read(BUTTON)) && (button_count == 1))
  {//
    button_long_push();
  }
  
  button_count = 0;
}  

void button_event_one_two(void * args)
{
  if(button_count >= 2)
  {//two click
    button_two_click();
    button_count = 0;
  }
  else 
  {
    if(gpio_read(BUTTON))
    {//one click
      
      button_one_click();
      button_count = 0;
    }
    else 
    {
      run_after_delay(button_is_long_push, NULL, 2000);
    }
  }
}

void button_scan(void * args)
{
  if(gpio_read(BUTTON))
  {
    button_state2 = 1;
  }
  else
  {
    button_state2 = 0;
  }
   
  if((button_state1 == 1) && (button_state2 == 0))
  {//fall
    if(button_count == 0)
    {
      button_count ++;
      run_after_delay(button_event_one_two, NULL, 500);
    }
    else 
    {
      button_count ++;
    }
  }

  button_state1 = button_state2; 
  run_after_delay(button_scan, NULL, 50);
}

void screen_on()
{
  screen_is_on = 1;
}

void screen_off()
{
  screen_is_on = 0;
}

void model_contral_init(void)
{
  button_init();
  screen_is_on = 1;
  model = COUNT_MODEL;
  two_click_function_point = NULL;
  
  model_change();
}
