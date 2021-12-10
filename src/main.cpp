#include <Arduino.h>
#include <communication.h>
#include <motor_control.h>
#include <micro.h>
#include <vector>

IntervalTimer myTimer;
IntervalTimer myTimer_security;
IntervalTimer myTimer_encoder;

Micro teensy = Micro("A");
Motor M1 = Motor(0, PWM1, MDLF, MDLB, MT1A, MT1B);
Motor M2 = Motor(0, PWM2, MDLF, MDLB, MT2A, MT2B);
Motor M3 = Motor(0, PWM3, MDLF, MDLB, MT3A, MT3B);
Motor M4 = Motor(1, PWM4, MDRF, MDRB, MT4A, MT4B);
Motor M5 = Motor(1, PWM5, MDRF, MDRB, MT5A, MT5B);
Motor M6 = Motor(1, PWM6, MDRF, MDRB, MT6A, MT6B);

void call1(){ M1.add_tic(); }
void call2(){ M2.add_tic(); }
void call3(){ M3.add_tic(); }
void call4(){ M4.add_tic(); }
void call5(){ M5.add_tic(); }
void call6(){ M6.add_tic(); }

void callA(){
  M1.asservissement();
  M2.asservissement();
  M3.asservissement();
  M4.asservissement();
  M5.asservissement();
  M6.asservissement();
}

void call_security()
{
  if(teensy.security_checking())
  {
    warning_led_ON();
    myTimer_encoder.end();
  }
  else{warning_led_OFF();}
}

void call_encoder()
{
    teensy.send_odometry_value();
}

void setup()
{
  teensy.add_motor(&M1);
  teensy.add_motor(&M2);
  teensy.add_motor(&M3);
  teensy.add_motor(&M4);
  teensy.add_motor(&M5);
  teensy.add_motor(&M6);

  analogWriteResolution(10);
  setup_led();

  attachInterrupt(digitalPinToInterrupt(M1.get_encoderA()), call1, RISING);
  attachInterrupt(digitalPinToInterrupt(M2.get_encoderA()), call2, RISING);
  attachInterrupt(digitalPinToInterrupt(M3.get_encoderA()), call3, RISING);
  attachInterrupt(digitalPinToInterrupt(M4.get_encoderA()), call4, RISING);
  attachInterrupt(digitalPinToInterrupt(M5.get_encoderA()), call5, RISING);
  attachInterrupt(digitalPinToInterrupt(M6.get_encoderA()), call6, RISING);

  // myTimer_encoder.begin(call_encoder, teensy.get_encoder_timer());
  myTimer_security.begin(call_security, teensy.get_security_timer());
  myTimer.begin(callA, 1000000/M1.esclavagiste.param.frequency);
  M1.set_command_advance(0, 0.0);
  M2.set_command_advance(0, 0.0);
  M3.set_command_advance(0, 0.0);
  M4.set_command_advance(0, 0.0);
  M5.set_command_advance(0, 0.0);
  M6.set_command_advance(0, 0.0);

//   M1.set_command_simple(1,1023);
//   M2.set_command_simple(1,1023);
//   M3.set_command_simple(1,1023);
//   M4.set_command_simple(1,1023);
//   M5.set_command_simple(1,1023);
//   M6.set_command_simple(1,1023);

  Serial.begin(115200);
  Serial.setTimeout(10); 
}

String x_str, message_retour;
int type_message;

void loop()
{
  if(Serial.available() > 0) 
  { 
    // READ THE INCOMING DATA:
    x_str             = Serial.readString();

    // PARSE.
    type_message      = teensy.get_message_type(x_str);

    // PING.
    if(type_message == 0)
    {
      message_retour = "0/" + teensy.get_ID() + "\n";
      Serial.print(message_retour); 

      ping_reception();
      teensy.reset_security_timer();
      if(DR_status == false){ warning_led_OFF();}

      if(teensy.get_mother_board_detect() == false)
      {
        myTimer_encoder.begin(call_encoder, teensy.get_encoder_timer());
      }
      teensy.set_mother_board_detect(true);
    }

    // NEW MOTOR COMMAND.
    if(type_message == 1)
    {
      teensy.parse_message_motor(x_str);
      teensy.set_new_command();
    }

    Serial.flush();
  } 
}