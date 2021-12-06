#include <Arduino.h>
#include <pcb_test_function.h>

bool DR_status = true;
bool DG_status = true;
bool DB_status = true;

void update_led_status()
{
    // TODO: put this in setup.
    // pinMode(DR, OUTPUT);
    // pinMode(DG, OUTPUT);
    // pinMode(DB, OUTPUT);

    DR_status = !DR_status;
    DG_status = !DG_status;
    DB_status = !DB_status;

    digitalWrite(DR, DR_status);
    digitalWrite(DG, DG_status);
    digitalWrite(DB, DB_status);
}

void setup_pin()
{
    pinMode(DR, OUTPUT);
    pinMode(DG, OUTPUT);
    pinMode(DB, OUTPUT);

    pinMode(MT1A, INPUT_PULLDOWN);
    pinMode(MT2A, INPUT_PULLDOWN);
    pinMode(MT3A, INPUT_PULLDOWN);
    pinMode(MT4A, INPUT_PULLDOWN);
    pinMode(MT5A, INPUT_PULLDOWN);
    pinMode(MT6A, INPUT_PULLDOWN);
    pinMode(MT1B, INPUT_PULLDOWN);
    pinMode(MT2B, INPUT_PULLDOWN);
    pinMode(MT3B, INPUT_PULLDOWN);
    pinMode(MT4B, INPUT_PULLDOWN);
    pinMode(MT5B, INPUT_PULLDOWN);
    pinMode(MT6B, INPUT_PULLDOWN);

    pinMode(PWM1, OUTPUT);
    pinMode(PWM2, OUTPUT);
    pinMode(PWM3, OUTPUT);
    pinMode(PWM4, OUTPUT);
    pinMode(PWM5, OUTPUT);
    pinMode(PWM6, OUTPUT);

    pinMode(MDLF, OUTPUT);
    pinMode(MDLB, OUTPUT);
    pinMode(MDRF, OUTPUT);
    pinMode(MDRB, OUTPUT);

    analogReadResolution(10);
}