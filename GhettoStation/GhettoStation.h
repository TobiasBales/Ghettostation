#include "Menu.h"
#include "Strings.h"

/* ########################################  DEFINES ######################################################*/
/* #define PROTOCOL_UAVTALK                        // OpenPilot / Taulabs protocol */
/* #define PROTOCOL_MSP                            // MSP from Multiwii */
#define PROTOCOL_LIGHTTELEMETRY                 // Ghettostation internal protocol.
/* #define PROTOCOL_MAVLINK                        // Mavlink for Ardupilot / Autoquad / PixHawk / Taulabs (UAVOmavlinkBridge) */
/* #define PROTOCOL_NMEA                           //GPS NMEA ASCII protocol */
/* #define PROTOCOL_UBLOX                          //GPS UBLOX binary protocol */
/* #define COMPASS */
/* ######################################## HAL ####################################################*/

#ifdef TEENSYPLUS2
// This line defines a "Uart" object to access the serial port
HardwareSerial SerialPort1 = HardwareSerial();
HardwareSerial SerialDebug = HardwareSerial();
#ifdef OSD_OUTPUT
SoftwareSerial SerialPort2(SOFTSERIAL_RX,SOFTSERIAL_TX);
#endif
#endif

#ifdef MEGA
HardwareSerial SerialPort1(Serial1);
#ifdef OSD_OUTPUT
HardwareSerial SerialPort2(Serial2);
#endif
HardwareSerial SerialDebug(Serial);
#endif

#ifdef PROMINI
HardwareSerial SerialPort1(Serial);
#ifdef DEBUG
HardwareSerial SerialDebug(Serial);
#endif
#endif

int softserial_delay = (int)round(10000000.0f/(OSD_BAUD)); // time to wait between each byte sent.

//pan/tilt servos
PWMServo pan_servo;
PWMServo tilt_servo;

/* ########################################  VARIABLES #####################################################*/

float        voltage_ratio;              // voltage divider ratio for gs battery reading
float        voltage_actual = 0.0;           // gs battery voltage in mv
uint8_t      buzzer_status = 0;
//Telemetry variables
int32_t      uav_lat = 0;                    // latitude
int32_t      uav_lon = 0;                    // longitude
float        lonScaleDown=0.0;               // longitude scaling
uint8_t      uav_satellites_visible = 0;     // number of satellites
uint8_t      uav_fix_type = 0;               // GPS lock 0-1=no fix, 2=2D, 3=3D
int32_t      uav_alt = 0;                    // altitude (dm)
int32_t      rel_alt = 0;                    // relative altitude to home
uint16_t     uav_groundspeed = 0;            // ground speed in km/h
uint8_t      uav_groundspeedms = 0;          // ground speed in m/s
int16_t      uav_pitch = 0;                  // attitude pitch
int16_t      uav_roll = 0;                   // attitude roll
int16_t      uav_heading = 0;                // attitude heading
int16_t      uav_gpsheading=0;               // gps heading
uint16_t     uav_bat = 0;                    // battery voltage (mv)
uint16_t     uav_amp = 0;                    // consumed mah.
uint16_t     uav_current = 0;                // actual current
uint8_t      uav_rssi = 0;                   // radio RSSI (%)
uint8_t      uav_linkquality = 0;            // radio link quality
uint8_t      uav_airspeed = 0;               // Airspeed sensor (m/s)
uint8_t      ltm_armfsmode = 0;
uint8_t      uav_arm = 0;                    // 0: disarmed, 1: armed
uint8_t      uav_failsafe = 0;               // 0: normal,   1: failsafe
uint8_t      uav_flightmode = 19;            // Flight mode(0-19): 0: Manual, 1: Rate, 2: Attitude/Angle, 3: Horizon, 4: Acro, 5: Stabilized1, 6: Stabilized2, 7: Stabilized3,
// 8: Altitude Hold, 9: Loiter/GPS Hold, 10: Auto/Waypoints, 11: Heading Hold / headFree, 12: Circle, 13: RTH, 14: FollowMe, 15: LAND,
// 16:FlybyWireA, 17: FlybywireB, 18: Cruise, 19: Unknown
//int16_t      uav_chan5_raw;
//int16_t      uav_chan6_raw;
//int16_t      uav_chan7_raw;
//int16_t      uav_chan8_raw;

char* protocol = "";
long lastpacketreceived;
static boolean      enable_frame_request = 0;


//home
int32_t home_lon;
int32_t home_lat;
int32_t home_alt;
int16_t home_bearing = 0;
uint32_t home_dist;
uint8_t home_sent = 0;

//tracking
int Bearing;
int Elevation;
int servoBearing=0;
int servoElevation=0;

//lcd
char lcd_line1[21];
char lcd_line2[21];
char lcd_line3[21];
char lcd_line4[21];


//status
int current_activity = 0; // Activity status 0: Menu , 1: Track, 2: SET_HOME, 3: PAN_MINPWM, 4: PAN_MINANGLE, 5: PAN_MAXPWM,
// 6: PAN_MAXANGLE, 7: TILT_MINPWM, 8: TILT_MINANGLE, 9: TILT_MAXPWM, 10: TILT_MAXANGLE, 11: TEST_SERVO, 12: SET_RATE
boolean gps_fix      = false;
boolean btholdstate  = false;
boolean telemetry_ok = false;
boolean home_pos     = false;
boolean home_bear    = false;

//servo temp configuration before saving
int servoconf_tmp[4];
int servoconfprev_tmp[4];
uint8_t test_servo_step = 1;
uint16_t test_servo_cnt = 360;
long baudrates[8]= {1200, 2400, 4800, 9600, 19200, 38400, BAUDRATE56K, 115200};

/*##################################### COMMON FUNCTIONS #############################################*/

boolean getBit(byte Reg, byte whichBit) {
    boolean State;
    State = Reg & (1 << whichBit);
    return State;
}

byte setBit(byte &Reg, byte whichBit, boolean stat) {
    if (stat) {
        Reg = Reg | (1 << whichBit);
    }
    else {
        Reg = Reg & ~(1 << whichBit);
    }
    return Reg;
}

float toRad(float angle) {
    angle = angle*0.01745329; // (angle/180)*pi
    return angle;
}

float toDeg(float angle) {
    angle = angle*57.29577951;   // (angle*180)/pi
    return angle;
}

void attach_servo(PWMServo &s, int p, int min, int max) {
    if (!s.attached()) {
        s.attach(p,min,max);
    }
}

void detach_servo(PWMServo &s) {
    if (s.attached()) {
        s.detach();
    }
}


int config_bank[]= {1, 101, 201,301}; // 50 bytes reserved per bank.
uint8_t current_bank;

template <class T> int EEPROM_write(int ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    cli();
    for (i = 0; i < sizeof(value); i++)
        EEPROM.write(ee++, *p++);
    sei();
    return i;
}

template <class T> int EEPROM_read(int ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    cli();
    for (i = 0; i < sizeof(value); i++)
        *p++ = EEPROM.read(ee++);
    sei();
    return i;
}


//Configuration stored in EEprom
struct config_t // 28 bytes
{
    int config_crc;
    int pan_minpwm;
    int pan_minangle;
    int pan_maxpwm;
    int pan_maxangle;
    int tilt_minpwm;
    int tilt_minangle;
    int tilt_maxpwm;
    int tilt_maxangle;
    int baudrate;
    int telemetry;
    int bearing;
    uint8_t osd_enabled;
    uint8_t bearing_method;
    uint16_t voltage_ratio;
} configuration;



void clear_eeprom() {
    // clearing eeprom
    cli();
    for (int i = 0; i < 1025; i++)
        EEPROM.write(i, 0);
    // eeprom is clear  we can write default config
    //writing 4 setting banks.
    for (int j = 0; j < 4; j++) {
        configuration.config_crc = CONFIG_VERSION;  // config version check
        configuration.pan_minpwm = PAN_MINPWM;
        configuration.pan_minangle = PAN_MINANGLE;
        configuration.pan_maxpwm = PAN_MAXPWM;
        configuration.pan_maxangle = PAN_MAXANGLE;
        configuration.tilt_minpwm = TILT_MINPWM;
        configuration.tilt_minangle = TILT_MINANGLE;
        configuration.tilt_maxpwm = TILT_MAXPWM;
        configuration.tilt_maxangle = TILT_MAXANGLE;
        configuration.baudrate = 6;
        configuration.telemetry = 0;
        configuration.bearing = 0;
        configuration.osd_enabled = 0;
        configuration.bearing_method = 1;
        configuration.voltage_ratio = VOLTAGE_RATIO;  // ratio*10
        EEPROM_write(config_bank[j], configuration);
    }
    sei();
}

