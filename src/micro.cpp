#include <Arduino.h>
#include <micro.h>
#include <vector>
#include <communication.h>


Micro::Micro(String _ID)
{
    ID = _ID;
}

double Micro::get_message_type(String message)
{
    int index = message.indexOf('/', 0);             //finds location of first separator,
    return message.substring(0, index).toInt();
}

void Micro::parse_message_motor(String message)
{
    int information = 12;
    int index = 1;
    int indexB;
    String data;

    vect_command_motor.clear();
    
    for(int i = 0; i < information; i++)
    {
        indexB            = message.indexOf('/', index+1 );            //finds location of first ,
        data              = message.substring(index+1, indexB);        //captures first data String
        index             = indexB;
        vect_command_motor.push_back(data.toFloat());
    }
}

bool Micro::security_checking()
{
    /*
        DESCRIPTION: this function is call every security_timer nano secondes.
        if no ping has been detect since security_timer, stop the motor.
    */

    if(sincePrint > security_timer/1000)
    {
        // Serial.println("NO MOTHERBOARD DETECTED");
        security_stop_command();
        mother_board_detect = false;
        return true;
    }
    return false;
}

void Micro::security_stop_command()
{
    for(int i = 0; i < 6; i++)
    {
        vect_motor[i]->set_command_advance(0, 0);
    }
}

void Micro::set_new_command()
{
    String return_message = "1/";

    for(int i = 0; i < 6; i++)
    {
        vect_motor[i]->set_command_advance(vect_command_motor[i*2], vect_command_motor[i*2+1]);
        return_message = return_message + String(vect_command_motor[i*2],1) + "/" + String(vect_command_motor[i*2+1],1) + "/";
    }

    Serial.print(return_message + "\n");
}

void Micro::add_motor(Motor* new_motor)
{
    vect_motor.push_back(new_motor);
}

void Micro::send_odometry_value()
{
    String return_message = "2/";                                           // 2 type represent the odometry message.

    for(int i = 0; i < 6; i++)
    {
        return_message = return_message + String(vect_motor[i]->get_general_tic()) + "/";
        vect_motor[i]->reset_general_tic();
    }

    Serial.print(return_message + "\n");
}

// GET SET FUNCTION

String Micro::get_ID()
{
    return ID;
}

int Micro::get_security_timer()
{
    return security_timer;
}

void Micro::reset_security_timer()
{
    sincePrint = 0;
}

int Micro::get_encoder_timer()
{
    return encoder_timer;
}

bool Micro::get_mother_board_detect()
{
    return mother_board_detect;
}

void Micro::set_mother_board_detect(bool value)
{
    mother_board_detect = value;
}