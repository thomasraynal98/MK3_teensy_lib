// to sink current.
#define DR 15
#define DG 14
#define DB 13

extern bool DR_status;
extern bool DG_status;
extern bool DB_status;

// encoder sensor input.
#define MT1A 18
#define MT2A 19
#define MT3A 20
#define MT4A 2
#define MT5A 1
#define MT6A 0

#define MT1B 5
#define MT2B 4
#define MT3B 3
#define MT4B 21
#define MT5B 22
#define MT6B 23

// pwm motor control.
#define PWM1 12
#define PWM2 11
#define PWM3 10
#define PWM4 9
#define PWM5 8
#define PWM6 7

// direction motor. Motor Direction (LEFT/RIGHT) (FRONT/BACK)
#define MDLF 26
#define MDLB 27
#define MDRF 24
#define MDRB 25

// FUNCTION

void setup_pin();
void update_led_status();
