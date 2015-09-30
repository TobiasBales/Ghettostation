//LCD

#ifdef OLEDLCD
#define DISPLAY_WIDTH 10
#else
#define DISPLAY_WIDTH 20
#endif

char currentline[DISPLAY_WIDTH + 1] = "";
char extract[DISPLAY_WIDTH + 1] = "";

void init_lcdscreen() {
#ifdef DEBUG
    Serial.println("starting lcd");
#endif

    read_voltage();

#ifdef OLEDLCD
    display.setTextSize(2);
    display.setTextColor(WHITE);
#endif

#ifdef GLCDEnable
    GLCD.Init(NON_INVERTED);
    GLCD.SelectFont(System5x7);
    LCD.begin(20,4); // No idea why this is still needed for GLCD, but it breaks without
    GLCD.CursorTo(0,0);
    GLCD.println(STRING_GHETTOSTATION.copy(extract));
    GLCD.println(STRING_EMPTY_STRING.copy(extract));
    GLCD.println(STRING_VERSION.copy(extract));
    char voltage[6];
    dtostrf(voltage_actual, 4, 2, voltage);
    sprintf(currentline,"Battery: %s V", voltage);
    GLCD.println(currentline);
    delay(1500); //delay to init lcd in time.
#endif

#if defined(LCDLCM1602) || defined(LCDGYLCD) || defined(LCD03I2C)
    LCD.begin(20,4);
    delay(20);
    LCD.backlight();
    delay(250);
    LCD.noBacklight();
    delay(250);
    LCD.backlight();
    delay(250);
    LCD.setCursor(0,0);
    LCD.print(STRING_GHETTOSTATION.copy(extract));
    LCD.setCursor(0,1);
    LCD.print(STRING_EMPTY_STRING.copy(extract));
    LCD.setCursor(0,2);
    LCD.print(STRING_VERSION.copy(extract));
    LCD.setCursor(0,3);
    char voltage[6];
    dtostrf(voltage_actual, 4, 2, voltage);
    sprintf(currentline,"Battery: %s V", voltage);
    LCD.print(currentline);
    delay(1500); //delay to init lcd in time.
#endif
}

void store_lcdline(int i, char sbuffer[20]) {
    for (int l = strlen(sbuffer); l<DISPLAY_WIDTH; l++) {
        strcat(sbuffer, " ");
    }

    switch (i) {
        case 1:
            strcpy(lcd_line1, sbuffer);
            break;
        case 2:
            strcpy(lcd_line2, sbuffer);
            break;
        case 3:
            strcpy(lcd_line3, sbuffer);
            break;
        case 4:
            strcpy(lcd_line4, sbuffer);
            break;
        default:
            break;
    }

}

void refresh_lcd() {
#ifdef OLEDLCD
    display.clearDisplay();
    display.setCursor(0,0);
    display.println(lcd_line1);
    display.setCursor(0, 17);
    display.println(lcd_line2);
    display.setCursor(0, 33);
    display.println(lcd_line3);
    display.setCursor(0, 49);
    display.println(lcd_line4);
    display.display();
#endif

#ifdef GLCDEnable
    GLCD.CursorTo(0,0);
    GLCD.println(lcd_line1);
    GLCD.println(lcd_line2);
    GLCD.println(lcd_line3);
    GLCD.println(lcd_line4);
#endif

#if defined(LCDLCM1602) || defined(LCDGYLCD) || defined(LCD03I2C)
    LCD.setCursor(0,0);
    LCD.print(lcd_line1);
    LCD.setCursor(0,1);
    LCD.print(lcd_line2);
    LCD.setCursor(0,2);
    LCD.print(lcd_line3);
    LCD.setCursor(0,3);
    LCD.print(lcd_line4);
#endif
}

void lcddisp_menu() {
    Menu const* displaymenu_current = displaymenu.get_current_menu();
    MenuComponent const* displaymenu_sel = displaymenu_current->get_selected();

    uint8_t selected_item;
    uint8_t menu_components_number;
    uint8_t m;
    selected_item = displaymenu_current->get_cur_menu_component_num();
    menu_components_number = displaymenu_current->get_num_menu_components();
    for (int n = 1; n < 5 ; n++)  {
        if ( menu_components_number >= n ) {
            if (menu_components_number <= 4)
                m = n;
            else if (selected_item < (menu_components_number - selected_item - 1))
                m =  selected_item + n ;
            else
                m =  menu_components_number - (menu_components_number - n - 1);
            MenuComponent const* displaymenu_comp = displaymenu_current->get_menu_component(m - 1);
            sprintf(currentline, displaymenu_comp->get_name());
            for (int l = strlen(currentline); l < (DISPLAY_WIDTH - 1); l++) {
                strcat(currentline," ");
            }
            if (displaymenu_sel == displaymenu_comp)
                strcat(currentline,"<");
            else
                strcat(currentline," ");
        }
        else {
            STRING_EMPTY_STRING.copy(currentline);
        }
        store_lcdline(n, currentline);
    }
}


// SET_HOME SCREEN
void lcddisp_sethome() {
    show_telemetry_status();

    if (!telemetry_ok) {
        store_lcdline(2, STRING_WAITING.copy(currentline));
        return;
    }

    if (!gps_fix) {
        store_lcdline(2, STRING_NO_GPS_FIX.copy(currentline));
        store_lcdline(3, STRING_PLEASE_WAIT.copy(currentline));
        store_lcdline(4, STRING_LONG_PRESS_TO_QUIT.copy(currentline));
        return;
    }

    STRING_3D_FIX_ALT.copy(extract);
    sprintf(currentline, extract, (int)round(uav_alt / 100.0f));
    store_lcdline(2, currentline);

    char lat[10];
    char lon[10];
    dtostrf(uav_lat / 10000000.0, 5, 5, lat);
    dtostrf(uav_lon / 10000000.0, 5, 5, lon);
    sprintf(currentline,"%s %s", lat, lon);
    store_lcdline(3, currentline);

    store_lcdline(4, STRING_SAVE_HOME_NOW.copy(currentline));
}

void lcddisp_setbearing() {
    switch (configuration.bearing_method) {
        case 2:
            if (right_button.holdTime() >= 700 && right_button.isPressed() ) {
                home_bearing+=10;
                if (home_bearing > 359)
                    home_bearing = 0;
                delay(500);
            }
            else if ( left_button.holdTime() >= 700 && left_button.isPressed() ) {
                home_bearing-=10;
                if (home_bearing < 0)
                    home_bearing = 359;
                delay(500);
            }
            break;
        case 3:
            home_bearing = uav_heading;  // use compass data from the uav.
            break;
        #ifdef COMPASS
        case 4:
            retrieve_mag();
            break;
        #endif
        default:
            break;
    }

    show_telemetry_status();

    #ifdef FORCE_BEARING_METHOD
    if (FORCE_BEARING_METHOD == 1)
    #else
    if (configuration.bearing_method == 1)
    #endif
    {
        STRING_EMPTY_STRING.copy(currentline);
        STRING_MOVE_UAV.copy(currentline);
    }
    #ifdef FORCE_BEARING_METHOD
    else if (FORCE_BEARING_METHOD == 2)
    #else
    else if (configuration.bearing_method == 2)
    #endif
    {
        store_lcdline(2,STRING_SETHEADING.copy(currentline));
        sprintf(currentline, "     << %3d >>", home_bearing);
        store_lcdline(3, currentline);
    } else {
        sprintf(currentline, "        %3d   ", home_bearing);
        store_lcdline(2, currentline);
    }


    store_lcdline(4, STRING_PRESS_ENTER.copy(currentline));
}

void lcddisp_homeok() {
    show_telemetry_status();
    store_lcdline(2, STRING_HOME_IS_SET.copy(currentline));
    store_lcdline(3, STRING_START_TRACKING.copy(currentline));
    store_lcdline(4, STRING_MENU_RESET.copy(currentline));
}

void lcddisp_tracking(){
    show_telemetry_status();

    sprintf(currentline, "Alt:%dm Spd:%d", (int)round(rel_alt/100.0f), uav_groundspeed);
    store_lcdline(2, currentline);

    sprintf(currentline, "Dist:%dm Hdg:%d", (int)round(home_dist/100.0f), uav_heading);
    store_lcdline(3, currentline);

    char lat[10];
    char lon[10];
    dtostrf(uav_lat / 10000000.0, 5, 5, lat);
    dtostrf(uav_lon / 10000000.0, 5, 5, lon);
    sprintf(currentline,"%s %s", lat, lon);
    store_lcdline(4, currentline);
}

#ifdef PROTOCOLS
void lcddisp_telemetry() {
    store_lcdline(1, STRING_SELECT_PROTOCOL.copy(currentline));
    store_lcdline(2, STRING_EMPTY_STRING.copy(currentline));
    switch (configuration.telemetry) {
        case 0:
            store_lcdline(3, STRING_UAVTALK.copy(currentline)); break;
        case 1:
            STRING_MULTIWII.copy(currentline); break;
        case 2:
            STRING_LIGHTTELEMETRY.copy(currentline); break;
        case 3:
            STRING_MAVLINK.copy(currentline); break;
        case 4:
            STRING_NMEA.copy(currentline); break;
        case 5:
            STRING_UBLOX.copy(currentline); break;
    }
    store_lcdline(3, currentline);
    store_lcdline(4, STRING_LONG_PRESS_TO_QUIT.copy(currentline);)
}
#endif

#ifdef BAUDRATES
void lcddisp_baudrate() {
    store_lcdline(1, string_baudrate.copy(currentline));
    store_lcdline(2, STRING_EMPTY_STRING.copy(currentline));
    switch (configuration.baudrate) {
        case 0:
            string_baudrate0.copy(currentline);  break;
        case 1:
            string_baudrate1.copy(currentline);  break;
        case 2:
            string_baudrate2.copy(currentline); break;
        case 3:
            string_baudrate3.copy(currentline);  break;
        case 4:
            string_baudrate4.copy(currentline);  break;
        case 5:
            string_baudrate5.copy(currentline);  break;
        case 6:
            string_baudrate6.copy(currentline);  break;
        case 7:
            string_baudrate7.copy(currentline);  break;
    }
    store_lcdline(3, currentline);
    store_lcdline(4, STRING_LONG_PRESS_TO_QUIT.copy(currentline));
}
#endif

#ifdef PROFILES
void lcddisp_bank() {
    store_lcdline(1, string_bank.copy(currentline));
    store_lcdline(2, STRING_EMPTY_STRING.copy(currentline));
    switch (current_bank+1) {
        case 1: sprintf(currentline,"> %s", string_bank1.copy(extract));break;
        case 2: sprintf(currentline,"> %s", string_bank2.copy(extract));break;
        case 3: sprintf(currentline,"> %s", string_bank3.copy(extract));break;
        case 4: sprintf(currentline,"> %s", string_bank4.copy(extract));break;
    }
    store_lcdline(3, currentline);
    store_lcdline(4, STRING_LONG_PRESS_TO_QUIT);
}
#endif

#ifdef OSD_OUTPUT
void lcddisp_osd() {
    store_lcdline(1, STRING_ENABLE_OSD.copy(currentline));
    store_lcdline(2, STRING_EMPTY_STRING.copy(currentline));
    switch (configuration.osd_enabled) {
        case 0:
            STRING_OSD_NO.copy(currentline);  break;
        case 1:
            STRING_OSD_YES.copy(currentline);  break;
    }
    store_lcdline(3, currentline);
    store_lcdline(4, STRING_LONG_PRESS_TO_QUIT);
}
#endif

#ifdef BEARING_METHODS
void lcddisp_bearing_method() {
    store_lcdline(1, STRING_BEARING_METHOD.copy(currentline));
    store_lcdline(2, STRING_EMPTY_STRING.copy(currentline));
    switch (configuration.bearing_method) {
        case 1:
            STRING_BEARING_20M.copy(currentline); break;
        case 2:
            STRING_BEARING_MANUAL.copy(currentline); break;
        #ifdef COMPASS
        case 3:
            STRING_BEARING_FC_COMPASS.copy(currentline); break;
        case 4:
            STRING_BEARING_GS_COMPASS.copy(currentline); break;
        #endif
    }
    store_lcdline(3, currentline);
    store_lcdline(4, STRING_LONG_PRESS_TO_QUIT);
}
#endif


void lcddisp_voltage_ratio() {
    read_voltage();
    if (right_button.holdTime() >= 700 && right_button.isPressed() ) {
        voltage_ratio += 0.1;
        delay(500);
    }
    else if ( left_button.holdTime() >= 700 && left_button.isPressed() ) {
        voltage_ratio -= 0.1;
        delay(500);
    }

    store_lcdline(1, STRING_SET_VOLTAGE.copy(currentline));

    char voltage[6];
    dtostrf(voltage_actual, 4, 2, voltage);
    sprintf(currentline,"Voltage: %s V", voltage);
    store_lcdline(2, currentline);

    dtostrf(voltage_ratio, 3, 2, voltage);
    sprintf(currentline,"Ratio:  %s", voltage);
    store_lcdline(3, currentline);

    store_lcdline(4, STRING_LONG_PRESS_TO_QUIT.copy(currentline));
}

void lcddisp_testservo() {
    store_lcdline(1, STRING_TESTING_SERVOS.copy(currentline));
    store_lcdline(2, STRING_SERVOS_CONFIGURATION.copy(currentline));
    store_lcdline(3, STRING_EMPTY_STRING.copy(currentline));
    store_lcdline(4, STRING_LONG_PRESS_TO_QUIT.copy(currentline));
}

void show_telemetry_status() {
    if (!telemetry_ok) {
        store_lcdline(1, "P: No Telemetry");
    } else {
        sprintf(currentline, "P:%s SATS:%d FIX:%d", protocol, uav_satellites_visible, uav_fix_type);
        store_lcdline(1, currentline);
    }
}

// SERVO CONFIGURATION

int config_servo(int servotype, int valuetype, int value ) {
    // servo configuration screen function return configured value
    //check long press left right
    if (right_button.holdTime() >= 700 && right_button.isPressed() ) {
        value+=20;
        delay(500);
    }
    else if ( left_button.holdTime() >= 700 && left_button.isPressed() ) {
        value-=20;
        delay(500);
    }

    if (servotype==1) { // Pan servo
        store_lcdline(1, STRING_PAN_SERVO.copy(currentline));
    }
    else if (servotype==2) { // Tilt servo
        store_lcdline(1, STRING_TILT_SERVO.copy(currentline));
    }

    store_lcdline(2, STRING_EMPTY_STRING.copy(currentline));
    switch (valuetype)
    {
        case 1: sprintf(currentline, "min endpoint: <%4d>",  value); break;          //minpwm
        case 2: sprintf(currentline, "min angle: <%3d>    ", value); break;         //minangle
        case 3: sprintf(currentline, "max endpoint: <%4d>",  value); break;          //maxpwm
        case 4: sprintf(currentline, "max angle: <%3d>    ", value); break;         //maxangle
    }
    store_lcdline(3, currentline);

    STRING_LONG_PRESS_TO_QUIT.copy(currentline);
    store_lcdline(4, currentline);
    return value;
}
