#include <Arduino.h>
#include <motor_control.h>

Motor::Motor(int side1, int pin_pwm1, int motor_direction_forward1, int motor_direction_backward1, int encoderA1, int encoderB1)
{
    side = side1;
    pin_pwm = pin_pwm1;
    motor_direction_forward = motor_direction_forward1;
    motor_direction_backward = motor_direction_backward1;
    encoderA = encoderA1;
    encoderB = encoderB1;

    setup_motor();
    setup_encoder();

    analogWriteFrequency(pin_pwm,25000);

    esclavagiste.param.Kp = 150;
    esclavagiste.param.Ki = 80;

    esclavagiste.param.frequency = 200;
}

void Motor::setup_encoder()
{
    pinMode(encoderA, INPUT_PULLDOWN);
    pinMode(encoderB, INPUT_PULLDOWN);
}

void Motor::setup_motor()
{
    pinMode(pin_pwm, OUTPUT);
    pinMode(motor_direction_forward, OUTPUT);
    pinMode(motor_direction_backward, OUTPUT);
}

void Motor::set_command_simple(int direction, int pwm)
{
    motor_direction_status = direction;
    
    if(motor_direction_status == 0)
    {
        // STOP
        analogWrite(pin_pwm, 0);
        digitalWrite(motor_direction_forward, false);
        digitalWrite(motor_direction_backward, false);
    }
    if(motor_direction_status == 1)
    {
        // FORWARD
        if(side == 0)
        {
            analogWrite(pin_pwm, pwm);
            digitalWrite(motor_direction_forward, true);
            digitalWrite(motor_direction_backward, false);            
        }
        if(side == 1)
        {
            analogWrite(pin_pwm, pwm);
            digitalWrite(motor_direction_forward, false);
            digitalWrite(motor_direction_backward, true);
        }
    }
    if(motor_direction_status == -1)
    {
        // BACKWARD
        if(side == 0)
        {
            analogWrite(pin_pwm, pwm);
            digitalWrite(motor_direction_forward, false);
            digitalWrite(motor_direction_backward, true);
        }
        if(side == 1)
        {
            analogWrite(pin_pwm, pwm);
            digitalWrite(motor_direction_forward, true);
            digitalWrite(motor_direction_backward, false);
        }
    }
}

void Motor::set_command_advance(int direction, double speed)
{
    motor_direction_status = direction;
    motor_speed = speed;

    if(motor_direction_status == 0)
    {
        // STOP
        digitalWrite(motor_direction_forward, false);
        digitalWrite(motor_direction_backward, false);
    }
    if(motor_direction_status == 1)
    {
        // FORWARD
        if(side == 0)
        {
            digitalWrite(motor_direction_forward, true);
            digitalWrite(motor_direction_backward, false);
        }
        if(side == 1)
        {
            digitalWrite(motor_direction_forward, false);
            digitalWrite(motor_direction_backward, true);
        }
    }
    if(motor_direction_status == -1)
    {
        // BACKWARD
        if(side == 0)
        {
            digitalWrite(motor_direction_forward, false);
            digitalWrite(motor_direction_backward, true);
        }
        if(side == 1)
        {
            digitalWrite(motor_direction_forward, true);
            digitalWrite(motor_direction_backward, false);
        }
    }

    tic_per_sample = motor_speed * 100 * tic_per_rot / cir_wheel / esclavagiste.param.frequency;
}

void Motor::asservissement()
{   
    if(motor_direction_status == -1) { motor_sensor_tic = -1*motor_sensor_tic; }

    int error = tic_per_sample - motor_sensor_tic;
    esclavagiste.data.sum_error += error;
    motor_sensor_tic = 0;

    if(esclavagiste.data.sum_error > 13) esclavagiste.data.sum_error = 13;
    if(esclavagiste.data.sum_error < -13) esclavagiste.data.sum_error = -13;

    int command = esclavagiste.param.Kp * error + esclavagiste.param.Ki * esclavagiste.data.sum_error;
    if(command < 0) command = 0 ;
    else if(command > 1023) command = 1023;
    analogWrite(pin_pwm, command);

}

void Motor::add_tic()
{
    if(digitalReadFast(encoderB))
    {
        motor_sensor_tic++;
        general_sensor_tic++;
    }
    else
    {
        motor_sensor_tic--;
        general_sensor_tic--;
    }
}

int Motor::get_encoderA()
{
    return encoderA;
}

int Motor::get_tic()
{
    return motor_sensor_tic;
}

int Motor::get_tic_per_sample()
{
    return tic_per_sample;
}

int Motor::get_general_tic()
{
    return general_sensor_tic;
}

void Motor::reset_general_tic()
{
    general_sensor_tic = 0;
}