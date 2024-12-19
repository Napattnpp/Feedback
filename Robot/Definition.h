// WiFi
#define WIFI_NAME           "ESP32"
#define PASSWORD            ""
#define UDP_PORT            63395

// IR-Sensors
#define L3                  0
#define L2                  0
#define L1                  0
#define C                   0
#define R1                  0
#define R2                  0
#define R3                  0

// Motor
#define FORWARD             0b10100000
#define BACKWARD            FORWARD>>1

#define TURN_LEFT_W         0b10000000
#define TURN_RIGHT_W        TURN_LEFT_W>>2

#define TURN_LEFT_B         0b01000000
#define TURN_RIGHT_B        TURN_LEFT_B>>2

#define SPIN_LEFT          0b10010000
#define SPIN_RIGHT          0b01100000

#define STOP                0b00000000