/*########################################### MENU ##################################################*/

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
        Menu m1m3m3Menu("Others");
            MenuItem m1m3m3i3Item("Bat Alert");

