#ifndef GRANDPARENT_H
#define GRANDPARENT_H

struct PID 
{
    struct Param{
        double Kp;
        double Ki;
        double Kd;
        double frequency;
    }param;

    struct Data{
        int sum_error;
    }data;
};

class Motor
{
    private:
        // VARIABLE
        int side;                         // 0 = LEFT & 1 = RIGHT
        int pin_pwm;                      // pin to control pwm.
        int motor_direction_forward;      // pin to move forward.
        int motor_direction_backward;     // pin to move backward.
        int encoderA;                     // pin of encoder input A.
        int encoderB;                     // pin of encoder input B.

        int motor_direction_status = 0;   // 0 = NON DEFINE & 1 = FORWARD & -1 = BACKWARD
        double motor_speed;
        int tic_per_sample;
        int motor_sensor_tic = 0;

    
    public:
        // CONSTRUCTOR
        Motor(int side, int pwm, int motor_direction_forward, int motor_direction_backward, int encoderA, int encoderB);

        // FUNCTION
        void setup_encoder();
        void setup_motor();
        void set_command_simple(int direction, int pwm);
        void set_command_advance(int direction, double speed);
        void add_tic();
        void asservissement();

        // GET SET
        int get_encoderA();
        int get_tic();
        int get_tic_per_sample();

        // STATIC VARIABLE
        double tic_in_cm = 0.03458;
        double tic_per_rot = 1817;
        double cir_wheel = 62.8318;
        PID esclavagiste;

};
#endif