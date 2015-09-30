/*##################################### STRINGS STORED IN FLASH #############################################*/

#ifdef OLEDLCD
FLASH_STRING(STRING_GHETTOSTATION,      "");
FLASH_STRING(STRING_EMPTY_STRING,      "");
FLASH_STRING(STRING_VERSION,      "");

FLASH_STRING(STRING_WAITING,     "Waiting");
FLASH_STRING(STRING_NO_GPS_FIX,     "No GPS fix");
FLASH_STRING(STRING_3D_FIX_ALT,     "Alt: %dm");
FLASH_STRING(STRING_PLEASE_WAIT,     "Please wait");
FLASH_STRING(STRING_LONG_PRESS_TO_QUIT,     "LP to quit");
FLASH_STRING(STRING_SAVE_HOME_NOW,     "Save Home?");
FLASH_STRING(STRING_SETHEADING,     "Heading:");
FLASH_STRING(STRING_MOVE_UAV,     "Move 20m");
FLASH_STRING(STRING_PRESS_ENTER,     "ahead");
FLASH_STRING(STRING_HOME_IS_SET,    "Home set");
FLASH_STRING(STRING_START_TRACKING,    "Start");
FLASH_STRING(STRING_MENU_RESET,    "Menu Reset");
FLASH_STRING(STRING_PAN_SERVO,    "Pan Servo");
FLASH_STRING(STRING_TILT_SERVO,    "Tilt Servo");
FLASH_STRING(STRING_TESTING_SERVOS,    "Testing");
FLASH_STRING(STRING_SERVOS_CONFIGURATION,    "Setup");
#ifdef PROTOCOLS
FLASH_STRING(STRING_SELECT_PROTOCOL, " Protocol ");
FLASH_STRING(STRING_UAVTALK, " UAV Talk>");
FLASH_STRING(STRING_MULTIWII, "<MultiWii>");
FLASH_STRING(STRING_LIGHTTELEMETRY, "<     LTM>");
FLASH_STRING(STRING_MAVLINK, "< MavLink>");
FLASH_STRING(STRING_NMEA, "<    NMEA>");
FLASH_STRING(STRING_UBLOX, "<    Ublox");
#endif
#ifdef BAUDRATES
FLASH_STRING(string_baudrate,   " Baudrate ");
FLASH_STRING(string_baudrate0,  "    1200 >");
FLASH_STRING(string_baudrate1,  "<   2400 >");
FLASH_STRING(string_baudrate2,  "<   4800 >");
FLASH_STRING(string_baudrate3,  "<   9600 >");
FLASH_STRING(string_baudrate4,  "<  19200 >");
FLASH_STRING(string_baudrate5,  "<  38400 >");
FLASH_STRING(string_baudrate6,  "<  57600 >");
FLASH_STRING(string_baudrate7,  "< 115200");
#endif
#ifdef PROFILES
FLASH_STRING(string_bank,       "Load Profile");
FLASH_STRING(string_bank1,      BANK1);
FLASH_STRING(string_bank2,      BANK2);
FLASH_STRING(string_bank3,      BANK3);
FLASH_STRING(string_bank4,      BANK4);
#endif
#ifdef OSD_OUTPUT
FLASH_STRING(STRING_ENABLE_OSD,       "Enable OSD");
FLASH_STRING(STRING_OSD_YES,       "   Yes   >");
FLASH_STRING(STRING_OSD_NO,       "<   No");
#endif
#ifdef BEARING_METHODS
FLASH_STRING(STRING_BEARING_METHOD,       "Bearing");
FLASH_STRING(STRING_BEARING_20M,       "20m away");
FLASH_STRING(STRING_BEARING_MANUAL,       "Manual");
#endif
#ifdef COMPASS
FLASH_STRING(STRING_BEARING_FC_COMPASS,       "FC Compass");
FLASH_STRING(STRING_BEARING_GS_COMPASS,       "GS Compass");
#endif
FLASH_STRING(STRING_SET_VOLTAGE,       "Set voltage");

#else

FLASH_STRING(STRING_GHETTOSTATION,      "  [GHETTOSTATION]   ");
FLASH_STRING(STRING_EMPTY_STRING,      "                    ");
FLASH_STRING(STRING_VERSION,      "Rev 1.1.0-dev   ");
FLASH_STRING(STRING_WAITING,     "  Waiting for Data  ");
FLASH_STRING(STRING_NO_GPS_FIX,     "   No GPS 3D FIX    ");
FLASH_STRING(STRING_3D_FIX_ALT,     "3D FIX! Alt: %dm");
FLASH_STRING(STRING_PLEASE_WAIT,     "    Please Wait.    ");
FLASH_STRING(STRING_LONG_PRESS_TO_QUIT,     "(long press to quit)");
FLASH_STRING(STRING_SAVE_HOME_NOW,     " Save Home pos now? ");
FLASH_STRING(STRING_SETHEADING,     " Set Heading:       ");
FLASH_STRING(STRING_MOVE_UAV,     " Move UAV 20m ahead ");
FLASH_STRING(STRING_PRESS_ENTER,     " & press enter      ");
FLASH_STRING(STRING_HOME_IS_SET,    "    HOME IS SET     ");
FLASH_STRING(STRING_START_TRACKING,    "Enter:Start Tracking");
FLASH_STRING(STRING_MENU_RESET,    "<< Menu     Reset >>");
FLASH_STRING(STRING_PAN_SERVO,    "    [PAN SERVO]     ");
FLASH_STRING(STRING_TILT_SERVO,    "    [TILT SERVO]    ");
FLASH_STRING(STRING_TESTING_SERVOS,    "   TESTING SERVOS   ");
FLASH_STRING(STRING_SERVOS_CONFIGURATION,    "   CONFIGURATION    ");
#ifdef PROTOCOLS
FLASH_STRING(STRING_SELECT_PROTOCOL, "  SELECT PROTOCOL:  ");
FLASH_STRING(STRING_UAVTALK, "      UAVTALK     >>");
FLASH_STRING(STRING_MULTIWII, "<<    MULTIWII    >>");
FLASH_STRING(STRING_LIGHTTELEMETRY, "<< LIGHTTELEMETRY >>");
FLASH_STRING(STRING_MAVLINK, "<<     MAVLINK    >>");
FLASH_STRING(STRING_NMEA, "<<      NMEA      >>");
FLASH_STRING(STRING_UBLOX, "<<      UBLOX       ");
#endif
#ifdef BAUDRATES
FLASH_STRING(string_baudrate,   "  SELECT BAUDRATE:  ");
FLASH_STRING(string_baudrate0,  "        1200      >>");
FLASH_STRING(string_baudrate1,  "<<      2400      >>");
FLASH_STRING(string_baudrate2,  "<<      4800      >>");
FLASH_STRING(string_baudrate3,  "<<      9600      >>");
FLASH_STRING(string_baudrate4,  "<<     19200      >>");
FLASH_STRING(string_baudrate5,  "<<     38400      >>");
FLASH_STRING(string_baudrate6,  "<<     57600      >>");
FLASH_STRING(string_baudrate7,  "<<    115200        ");
#endif
#ifdef PROFILES
FLASH_STRING(string_bank,       " LOAD SETTINGS BANK ");
FLASH_STRING(string_bank1,      BANK1);
FLASH_STRING(string_bank2,      BANK2);
FLASH_STRING(string_bank3,      BANK3);
FLASH_STRING(string_bank4,      BANK4);
#endif
#ifdef OSD_OUTPUT
FLASH_STRING(STRING_ENABLE_OSD,       "      ENABLE OSD    ");
FLASH_STRING(STRING_OSD_YES,       "<<       YES      >>");
FLASH_STRING(STRING_OSD_NO,       "<<       NO       >>");
#endif
#ifdef BEARING_METHODS
FLASH_STRING(STRING_BEARING_METHOD,       "   BEARING METHOD   ");
FLASH_STRING(STRING_BEARING_20M,       "1: Put UAV 20m away ");
FLASH_STRING(STRING_BEARING_MANUAL,       "2: Manual           ");
#endif
#ifdef COMPASS
FLASH_STRING(STRING_BEARING_FC_COMPASS,       "3: FC Compass       ");
FLASH_STRING(STRING_BEARING_GS_COMPASS,       "4: GS Compass       ");
#endif
FLASH_STRING(STRING_SET_VOLTAGE,       "ADJUST VOLTAGE RATIO");

#endif
