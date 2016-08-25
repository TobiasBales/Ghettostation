/*##################################### STRINGS STORED IN FLASH #############################################*/

#ifdef OLEDLCD

FLASH_STRING(string_load1,      "  Ghetto  ");
FLASH_STRING(string_load2,      " Station  ");
FLASH_STRING(string_load3,      "");

FLASH_STRING(string_shome1,     "Waiting");
FLASH_STRING(string_shome2,     "No GPS fix");
FLASH_STRING(string_shome3,     "Fix Alt:");
FLASH_STRING(string_shome4,     "Please Wait");
FLASH_STRING(string_shome5,     "");
FLASH_STRING(string_shome6,     "Save Home?");
FLASH_STRING(string_shome7,     "Heading:");
FLASH_STRING(string_shome8,     "Move 20m");
FLASH_STRING(string_shome9,     "ahead");
FLASH_STRING(string_shome10,    "Home set");
FLASH_STRING(string_shome11,    "Start");
FLASH_STRING(string_shome12,    "Menu Reset");
FLASH_STRING(string_servos1,    "Pan Servo");
FLASH_STRING(string_servos2,    "Tilt Servo");
FLASH_STRING(string_servos3,    "Testing");
FLASH_STRING(string_servos4,    "Setup");
FLASH_STRING(string_telemetry1, " Protocol ");
FLASH_STRING(string_telemetry2, " UAV Talk>");
FLASH_STRING(string_telemetry3, "<MultiWii>");
FLASH_STRING(string_telemetry4, "<     LTM>");
FLASH_STRING(string_telemetry5, "< MavLink>");
FLASH_STRING(string_telemetry6, "<    NMEA>");
FLASH_STRING(string_telemetry7, "<    Ublox");

FLASH_STRING(string_baudrate,   " Baudrate ");
FLASH_STRING(string_baudrate0,  "    1200 >");
FLASH_STRING(string_baudrate1,  "<   2400 >");
FLASH_STRING(string_baudrate2,  "<   4800 >");
FLASH_STRING(string_baudrate3,  "<   9600 >");
FLASH_STRING(string_baudrate4,  "<  19200 >");
FLASH_STRING(string_baudrate5,  "<  38400 >");
FLASH_STRING(string_baudrate6,  "<  57600 >");
FLASH_STRING(string_baudrate7,  "< 115200");
FLASH_STRING(string_bank,       "Load Profile");
FLASH_STRING(string_bank1,      BANK1);
FLASH_STRING(string_bank2,      BANK2);
FLASH_STRING(string_bank3,      BANK3);
FLASH_STRING(string_bank4,      BANK4);
FLASH_STRING(string_osd1,       "Enable OSD");
FLASH_STRING(string_osd2,       "   Yes   >");
FLASH_STRING(string_osd3,       "<   No");
FLASH_STRING(string_bearing0,       "Bearing");
FLASH_STRING(string_bearing1,       "20m away");
FLASH_STRING(string_bearing2,       "Manual");
FLASH_STRING(string_bearing3,       "FC Compass");
FLASH_STRING(string_bearing4,       "GS Compass");
FLASH_STRING(string_voltage0,       "Set voltage");

#else

FLASH_STRING(string_load1,      "  [GHETTOSTATION]   ");
FLASH_STRING(string_load2,      "                    ");
FLASH_STRING(string_load3,      "Rev 1.1.0-dev   ");
FLASH_STRING(string_shome1,     "  Waiting for Data  ");
FLASH_STRING(string_shome2,     "   No GPS 3D FIX    ");
FLASH_STRING(string_shome3,     "3D FIX! Alt:");
FLASH_STRING(string_shome4,     "    Please Wait.    ");
FLASH_STRING(string_shome5,     "(long press to quit)");
FLASH_STRING(string_shome6,     " Save Home pos now? ");
FLASH_STRING(string_shome7,     " Set Heading:       ");
FLASH_STRING(string_shome8,     " Move UAV 20m ahead ");
FLASH_STRING(string_shome9,     " & press enter      ");
FLASH_STRING(string_shome10,    "    HOME IS SET     ");
FLASH_STRING(string_shome11,    "Enter:Start Tracking");
FLASH_STRING(string_shome12,    "<< Menu     Reset >>");
FLASH_STRING(string_servos1,    "    [PAN SERVO]     ");
FLASH_STRING(string_servos2,    "    [TILT SERVO]    ");
FLASH_STRING(string_servos3,    "   TESTING SERVOS   ");
FLASH_STRING(string_servos4,    "   CONFIGURATION    ");
FLASH_STRING(string_telemetry1, "  SELECT PROTOCOL:  ");
FLASH_STRING(string_telemetry2, "      UAVTALK     >>");
FLASH_STRING(string_telemetry3, "<<    MULTIWII    >>");
FLASH_STRING(string_telemetry4, "<< LIGHTTELEMETRY >>");
FLASH_STRING(string_telemetry5, "<<     MAVLINK    >>");
FLASH_STRING(string_telemetry6, "<<      NMEA      >>");
FLASH_STRING(string_telemetry7, "<<      UBLOX       ");

FLASH_STRING(string_baudrate,   "  SELECT BAUDRATE:  ");
FLASH_STRING(string_baudrate0,  "        1200      >>");
FLASH_STRING(string_baudrate1,  "<<      2400      >>");
FLASH_STRING(string_baudrate2,  "<<      4800      >>");
FLASH_STRING(string_baudrate3,  "<<      9600      >>");
FLASH_STRING(string_baudrate4,  "<<     19200      >>");
FLASH_STRING(string_baudrate5,  "<<     38400      >>");
FLASH_STRING(string_baudrate6,  "<<     57600      >>");
FLASH_STRING(string_baudrate7,  "<<    115200        ");
FLASH_STRING(string_bank,       " LOAD SETTINGS BANK ");
FLASH_STRING(string_bank1,      BANK1);
FLASH_STRING(string_bank2,      BANK2);
FLASH_STRING(string_bank3,      BANK3);
FLASH_STRING(string_bank4,      BANK4);
FLASH_STRING(string_osd1,       "      ENABLE OSD    ");
FLASH_STRING(string_osd2,       "<<       YES      >>");
FLASH_STRING(string_osd3,       "<<       NO       >>");
FLASH_STRING(string_bearing0,       "   BEARING METHOD   ");
FLASH_STRING(string_bearing1,       "1: Put UAV 20m away ");
FLASH_STRING(string_bearing2,       "2: Manual           ");
FLASH_STRING(string_bearing3,       "3: FC Compass       ");
FLASH_STRING(string_bearing4,       "4: GS Compass       ");
FLASH_STRING(string_voltage0,       "ADJUST VOLTAGE RATIO");

#endif
