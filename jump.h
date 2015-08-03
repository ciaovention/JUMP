#ifndef _JUMP_H_
#define _JUMP_H_

extern const uint8_t Helvetica_16_Table[];
extern const gfx_font_t Helvetica_16 ;
extern uint8_t screen_is_on;

#define SCREES_RES    5
#define SCREES_DC     11
#define BUTTON        4
#define HALL          16
#define POWER_PIN     3

extern void (* two_click_function_point) (void);
extern void (* gpio_change_point)         (void);
extern void (* timer_point)               (void);
extern void hall_change_for_contral(void);


//normal model
void normal_model_enter(void);
void normal_model_exit(void);

//timer
void timer_model_enter(void);
void timer_model_exit(void);

//train1
void train1_model_enter(void);
void train1_model_exit(void);

//train2
void train2_model_enter(void);
void train2_model_exit(void);

//train3
void train3_model_enter(void);
void train3_model_exit(void);

//train4
void train4_model_enter(void);
void train4_model_exit(void);

//count
void count_model_enter(void);
void count_model_exit(void);



#endif //_JUMP_H_
