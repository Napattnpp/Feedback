class Motor {
  private:
    int stcp_pin, shcp_pin, ds_pin;
    int motor_a_speed, motor_b_speed;

    void shiftRWrite(unsigned int bin);
    void setMotorSpeed(unsigned int speed_1, unsigned int speed_2);

  public:
    Motor (const int _stcp_pin, const int _shcp_pin, const int _ds_pin, const int _motor_a_speed, const int _motor_b_speed) {
      stcp_pin = _stcp_pin;
      shcp_pin = _shcp_pin;
      ds_pin = _ds_pin;

      motor_a_speed = _motor_a_speed;
      motor_b_speed = _motor_b_speed;
    };

    void init();
    void forward(unsigned int speed_1, unsigned int speed_2);
    void backward(unsigned int speed_1, unsigned int speed_2);

    void turn_left_w(unsigned int speed);
    void turn_right_w(unsigned int speed);
    void turn_left_b(unsigned int speed);
    void turn_right_b(unsigned int speed);

    void spin_left(unsigned int speed_1, unsigned int speed_2);
    void spin_right(unsigned int speed_1, unsigned int speed_2);

    void stop();
};

void Motor::shiftRWrite(unsigned int bin) {
  digitalWrite(stcp_pin, 0);
  shiftOut(ds_pin, shcp_pin, LSBFIRST, bin);
  digitalWrite(stcp_pin, 1);
}

void Motor::init() {
  pinMode(stcp_pin, OUTPUT);
  pinMode(shcp_pin, OUTPUT);
  pinMode(ds_pin, OUTPUT);

  pinMode(motor_a_speed, OUTPUT);
  pinMode(motor_b_speed, OUTPUT);
}

void Motor::setMotorSpeed(unsigned int speed_1, unsigned int speed_2) {
  digitalWrite(motor_a_speed, speed_1);
  digitalWrite(motor_b_speed, speed_2);
}

void Motor::forward(unsigned int speed_1, unsigned int speed_2)  { shiftRWrite(FORWARD);  setMotorSpeed(speed_1, speed_2); }
void Motor::backward(unsigned int speed_1, unsigned int speed_2) { shiftRWrite(BACKWARD); setMotorSpeed(speed_1, speed_2); }

void Motor::turn_left_w(unsigned int speed)  { shiftRWrite(TURN_LEFT_W);  setMotorSpeed(speed, 0); }
void Motor::turn_right_w(unsigned int speed) { shiftRWrite(TURN_RIGHT_W); setMotorSpeed(0, speed); }
void Motor::turn_left_b(unsigned int speed)  { shiftRWrite(TURN_LEFT_B);  setMotorSpeed(speed, 0); }
void Motor::turn_right_b(unsigned int speed) { shiftRWrite(TURN_RIGHT_B); setMotorSpeed(0, speed); }

void Motor::spin_left(unsigned int speed_1, unsigned int speed_2)  { shiftRWrite(SPIN_LEFT);  setMotorSpeed(speed_1, speed_2); }
void Motor::spin_right(unsigned int speed_1, unsigned int speed_2) { shiftRWrite(SPIN_RIGHT); setMotorSpeed(speed_1, speed_2); }

void Motor::stop() { shiftRWrite(STOP); setMotorSpeed(0, 0); }
