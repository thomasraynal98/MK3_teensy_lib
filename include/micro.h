#include <vector>
#include <motor_control.h>

class Micro
{
    private:
        // VARIABLE
        String ID;
        std::vector<double> vect_command_motor;
        std::vector<Motor*> vect_motor;
        int security_timer = 700000; // 700 ms
        elapsedMillis sincePrint = 0;

        bool mother_board_detect = false;

        int encoder_timer = 100000; // 100ms & 10 Hz
    
    public:
        // CONSTRUCTOR
        Micro(String _ID);

        // FUNCTION
        double get_message_type(String message);
        void parse_message_motor(String message);
        void set_new_command();
        void security_stop_command();
        bool security_checking();
        void send_odometry_value();

        // GET SET
        void add_motor(Motor* new_motor);
        String get_ID();
        int get_security_timer();
        void reset_security_timer();
        int get_encoder_timer();

        // STATIC VARIABLE

};