//Joystick button - view
//16 -1 =  left
//16 +1 = right
//17 -1 = front
//17 +1 = back
//292 1 = Zoom out
//293 1 = Zoom in
//290 1 = blindspot left
//291 1 = blindspot right
//6 0 = Enable joystick
//6 anything else = disable joystick

#define SRV_VIEW_ZOOMED_OUT 0
#define SRV_VIEW_ZOOMED_IN 1
#define SRV_VIEW_FRONT 2
#define SRV_VIEW_BACK 3
#define SRV_VIEW_LEFT 4
#define SRV_VIEW_RIGHT 5
#define SRV_VIEW_BS_LEFT 6
#define SRV_VIEW_BS_RIGHT 7

srv_coords_t srv_coords[] = {
	{0.000000, 0.000000, 440.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000}, //zoomed out
	{0.000000, 0.000000, 240.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000}, //zoomed in
	{0.000000, 88.200000, 192.000000, -1.000000, 26.000000, 34.000000, -1.500000, 0.000000, 0.000000}, //Front
	{0.000000, 88.200000, 192.000000, -1.000000, 26.000000, 34.000000, -1.500000, 0.000000, -3.1416},//Back
	{-0.000000, 200.000000, 220.000000, -7.000000, 63.000000, 0.000000, -1.500000, -0.000000, -1.570169}, //Left
	{-0.000000, 200.000000, 220.000000, -7.000000, 63.000000, 0.000000, -1.500000, 0.000000, 1.570169}, //Right
	{-0.000000, -29.049999, 440.000000, -67.374092, -39.541992, 0.000000, 0.000000, -0.000000, 0.000000}, //Left blindspot
	{-0.000000, -29.049999, 440.000000, 67.374092, -39.541992, 0.000000, 0.000000, -0.000000, 0.000000} //Right blindspot
};


