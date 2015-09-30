/*########################################### MENU ##################################################*/

#ifdef OLEDLCD

MenuSystem displaymenu;
Menu rootMenu("");
MenuItem m1i1Item("Start");
MenuItem m1i2Item("Set Home");
Menu m1m3Menu("Config");
    Menu m1m3m1Menu("Servos");
            Menu m1m3m1m1Menu("Pan");
                MenuItem m1m3m1m1l1Item("Min PWM");
                MenuItem m1m3m1m1l2Item("Max PWM");
                MenuItem m1m3m1m1l3Item("Min Angle");
                MenuItem m1m3m1m1l4Item("Max Angle");
        Menu m1m3m1m2Menu("Tilt");
                MenuItem m1m3m1m2l1Item("Min PWM");
                MenuItem m1m3m1m2l2Item("Max PWM");
                MenuItem m1m3m1m2l3Item("Min Angle");
                MenuItem m1m3m1m2l4Item("Max Angle");
            MenuItem m1m3m1i3Item("Test");
        #if defined(PROTOCOLS) || defined(BAUDRATES)
        Menu m1m3m2Menu("Telemetry");
            #ifdef PROTOCOLS
            MenuItem m1m3m2i1Item("Protocol");
            #endif
            #ifdef BAUDRATES
            MenuItem m1m3m2i2Item("Baudrate");
            #endif
        #endif
        Menu m1m3m3Menu("Others");
            #ifdef OSD_OUTPUT
            MenuItem m1m3m3i1Item("OSD");
            #endif
            #ifdef BEARING_METHODS
            MenuItem m1m3m3i2Item("Bearing");
            #endif
            MenuItem m1m3m3i3Item("Bat Alert");
#ifdef PROFILES
MenuItem m1i4Item("Profile");
#endif

#else

MenuSystem displaymenu;
Menu rootMenu("");
MenuItem m1i1Item("START");
MenuItem m1i2Item("SET HOME");
Menu m1m3Menu("CONFIG");
    Menu m1m3m1Menu("SERVOS");
            Menu m1m3m1m1Menu("PAN");
                MenuItem m1m3m1m1l1Item("MINPWM");
                MenuItem m1m3m1m1l2Item("MAXPWM");
                MenuItem m1m3m1m1l3Item("MINANGLE");
                MenuItem m1m3m1m1l4Item("MAXANGLE");
        Menu m1m3m1m2Menu("TILT");
                MenuItem m1m3m1m2l1Item("MINPWM");
                MenuItem m1m3m1m2l2Item("MAXPWM");
                MenuItem m1m3m1m2l3Item("MINANGLE");
                MenuItem m1m3m1m2l4Item("MAXANGLE");
            MenuItem m1m3m1i3Item("TEST");
        #if defined(PROTOCOLS) || defined(BAUDRATES)
        Menu m1m3m2Menu("TELEMETRY");
            #ifdef PROTOCOLS
            MenuItem m1m3m2i1Item("PROTOCOL");
            #endif
            #ifdef BAUDRATES
            MenuItem m1m3m2i2Item("BAUDRATE");
            #endif
        #endif
        Menu m1m3m3Menu("OTHERS");
            #ifdef OSD_OUTPUT
            MenuItem m1m3m3i1Item("OSD");
            #endif
            #ifdef BEARING_METHODS
            MenuItem m1m3m3i2Item("BEARING METHOD");
            #endif
            MenuItem m1m3m3i3Item("BATTERY ALERT");
#ifdef PROFILES
MenuItem m1i4Item("SWITCH SETTINGS");
#endif

#endif
