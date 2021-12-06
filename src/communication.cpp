#include <Arduino.h>
#include <communication.h>


void setup_led()
{
    pinMode(DR, OUTPUT);
    pinMode(DG, OUTPUT);
    pinMode(DB, OUTPUT);
    digitalWrite(DR, true);
    digitalWrite(DG, true);
    digitalWrite(DB, true);
}

void ping_reception()
{
    DG_status = !DG_status;
    digitalWrite(DG, DG_status);
}

void warning_led_ON()
{
    DR_status = false;
    digitalWrite(DR, DR_status);
    DG_status = true;
    digitalWrite(DG, DG_status);
}

void warning_led_OFF()
{
    DR_status = true;
    digitalWrite(DR, DR_status);
}