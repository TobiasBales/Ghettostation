//LCD

#define DISPLAY_WIDTH 10


void init_lcdscreen() {
#ifdef DEBUG
    Serial.println("starting lcd");
#endif

  display.setTextSize(2);
  display.setTextColor(WHITE);
}

void store_lcdline( int i, char sbuffer[20] ) {

    switch (i) {
        case 1:
                strcpy(lcd_line1,sbuffer);
                break;
        case 2:
                strcpy(lcd_line2,sbuffer);
                break;
        case 3:
                strcpy(lcd_line3,sbuffer);
                break;
        case 4:
                strcpy(lcd_line4,sbuffer);
                break;
        default:
                break;
    }

}

void refresh_lcd() {
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
        delay(100);
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
        char currentline[21];
        if ( menu_components_number >= n ) {
            if (menu_components_number <= 4)
                m = n;
            else if (selected_item < (menu_components_number - selected_item - 1))
                m =  selected_item + n ;
            else
                m =  menu_components_number - (menu_components_number - n - 1);
            MenuComponent const* displaymenu_comp = displaymenu_current->get_menu_component(m - 1);
            sprintf(currentline, displaymenu_comp->get_name());
//            for (int l = strlen(currentline); l < (DISPLAY_WIDTH - 1); l++) {
//                strcat(currentline," ");
//            }
            if (displaymenu_sel == displaymenu_comp)
                strcat(currentline,"<");
            else
                strcat(currentline," ");
         }
         else {
             EMPTY_STRING.copy(currentline);
         }
         store_lcdline(n, currentline);
    }
}


// SET_HOME SCREEN
void lcddisp_sethome() {
    show_telemetry_state();

    if (!telemetry_ok) {
        WAITING.copy(lcd_line2);
        EMPTY_STRING.copy(lcd_line3);
        EMPTY_STRING.copy(lcd_line4);
        return;
    }

    if (!gps_fix) {
        NO_GPS_FIX.copy(lcd_line2);
        PLEASE_WAIT.copy(lcd_line3);
        LONG_PRESS_TO_QUIT.copy(lcd_line4);
        return;
    }

    sprintf(lcd_line2, "Alt: %dm", (int)round(uav_alt/100.0f));
    char lat[10];
    char lon[10];
    dtostrf(uav_lat/10000000.0, 5, 5, lat);
    dtostrf(uav_lon/10000000.0, 5, 5, lon);
    sprintf(lcd_line3,"%s %s", lat, lon);
    SAVE_HOME.copy(lcd_line4);

}

void show_telemetry_state() {
    if (!telemetry_ok) {
        strcpy(lcd_line1, "P:NO TELEMETRY");
    } else {
        sprintf(lcd_line1, "P:%s SATS:%d FIX:%d", protocol, uav_satellites_visible, uav_fix_type);
    }
}

void lcddisp_setbearing() {
    show_telemetry_state();
    EMPTY_STRING.copy(lcd_line2);
    MOVE_20_METERS.copy(lcd_line3);
    AHEAD.copy(lcd_line4);
}

void lcddisp_homeok() {
    show_telemetry_state();
    HOME_SET.copy(lcd_line2);
    START.copy(lcd_line3);
    MENU_RESET.copy(lcd_line4);
}

void lcddisp_tracking(){
    show_telemetry_state();
    sprintf(lcd_line2, "Alt:%dm Spd:%d", (int)round(rel_alt/100.0f), uav_groundspeed);
    sprintf(lcd_line3, "Dist:%dm Hdg:%d", (int)round(home_dist/100.0f), uav_heading);
    char bufferl[10];
    char bufferL[10];
    sprintf(lcd_line4, "%s %s", dtostrf(uav_lat/10000000.0, 5, 5, bufferl),dtostrf(uav_lon/10000000.0, 5, 5, bufferL));
}

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
    for ( int i = 1 ; i<5; i++ ) {
        char currentline[21]="";
        char extract[21];
        switch (i) {
            case 1:
                SET_VOLTAGE.copy(currentline);  break;
            case 2:
                char bufferV[6];
                sprintf(currentline,"Voltage: %s V", dtostrf(voltage_actual, 4, 2, bufferV));
                break;
            case 3:
                char bufferX[5];
                sprintf(currentline,"Ratio:  %s ", dtostrf(voltage_ratio, 3, 2, bufferV));
                break;
            case 4:
                strcpy(currentline, LONG_PRESS_TO_QUIT.copy(extract));  break;
        }
        for ( int l = strlen(currentline); l<20 ; l++ ) {
            strcat(currentline," ");
        }
        store_lcdline(i,currentline);
    }
}

void lcddisp_testservo() {
    TESTING.copy(lcd_line1);
    SETUP.copy(lcd_line2);
    EMPTY_STRING.copy(lcd_line3);
    LONG_PRESS_TO_QUIT.copy(lcd_line4);
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
        char currentline[21];
        char extract[21];
    if (servotype==1) {
        PAN_SERVO.copy(currentline);                              // Pan servo
        store_lcdline(1, currentline);
    }
    else if (servotype==2) {
        TILT_SERVO.copy(currentline);                              // Tilt servo
        store_lcdline(1, currentline);
    }
    EMPTY_STRING.copy(currentline);
        store_lcdline(2, currentline);
    switch (valuetype)
    {
        case 1: sprintf(currentline, "min endpoint: <%4d>",  value); break;          //minpwm
        case 2: sprintf(currentline, "min angle: <%3d>    ", value); break;         //minangle
        case 3: sprintf(currentline, "max endpoint: <%4d>",  value); break;          //maxpwm
        case 4: sprintf(currentline, "max angle: <%3d>    ", value); break;         //maxangle
    }
    store_lcdline(3, currentline);
    LONG_PRESS_TO_QUIT.copy(currentline);
    store_lcdline(4, currentline);
    return value;

}
