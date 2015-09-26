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
        Menu m1m3m2Menu("Telemetry");
            MenuItem m1m3m2i1Item("Protocol");
            MenuItem m1m3m2i2Item("Baudrate");
        Menu m1m3m3Menu("Others");
            MenuItem m1m3m3i1Item("OSD");
            MenuItem m1m3m3i2Item("Bearing");
            MenuItem m1m3m3i3Item("Bat Alert");
MenuItem m1i4Item("Profile");

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
        Menu m1m3m2Menu("TELEMETRY");
            MenuItem m1m3m2i1Item("PROTOCOL");
            MenuItem m1m3m2i2Item("BAUDRATE");
        Menu m1m3m3Menu("OTHERS");
            MenuItem m1m3m3i1Item("OSD");
            MenuItem m1m3m3i2Item("BEARING METHOD");
            MenuItem m1m3m3i3Item("BATTERY ALERT");
MenuItem m1i4Item("SWITCH SETTINGS");

#endif
