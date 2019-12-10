#include "vrpn_Button.h"
#include "vrpn_Analog.h"

#include <iostream>
using namespace std;
#define ZONE_A 0
#define ZONE_B 1
#define ZONE_C 2
#define ZONE_D 3
#define ACTIF 4
#define UNACTIF 5

static int currentSTATE = ACTIF;
static int currentZONE = ZONE_A;
static int previousZONE;

void VRPN_CALLBACK handle_analog(void* userData, const vrpn_ANALOGCB a)
{
	//1. Tracking and 2.Interpretation 
	double x = a.channel[0];
	double y = a.channel[1];


	if (x < 0.5 && y < 0.5) {
		currentZONE = ZONE_A;
	}
	else if (x < 0.5 && y > 0.5) {//change
		currentZONE = ZONE_B;
	}
	else if (x > 0.5 && y < 0.5) {//change
		currentZONE = ZONE_C;
	}
	else if (x > 0.5 && y > 0.5) {//change
		currentZONE = ZONE_D;
	}
	//3.4 recalculate params and refresh scene
	if (currentSTATE == ACTIF && previousZONE!= currentZONE) {
		cout << "\a";

		if (currentZONE == ZONE_A) {
			cout << "ZONE A";
		}
		else if (currentZONE == ZONE_B) {
			cout << "ZONE B";
		}
		else if (currentZONE == ZONE_D) {
			cout << "ZONE D";
		}
		else if (currentZONE == ZONE_C) {
			cout << "ZONE C";
		}
		cout << "\n";

	}
	previousZONE = currentZONE;
}


void VRPN_CALLBACK handle_button(void* userData, const vrpn_BUTTONCB b)
{
	if (b.button == 2 && currentSTATE == ACTIF) {
		cout << '\a';
	}
	else if (b.button == 2 && currentSTATE == UNACTIF) {
		currentSTATE = ACTIF;
	}
	else if (b.button == 0 && currentSTATE == ACTIF) {
		currentSTATE = UNACTIF;
		cout << "Desactivated ...\n";

	}
}


int main(int argc, char* argv[])
{

	vrpn_Analog_Remote* vrpnAnalog = new vrpn_Analog_Remote("Mouse0@localhost");
	vrpn_Button_Remote* vrpnButton = new vrpn_Button_Remote("Mouse0@localhost");
	vrpnAnalog->register_change_handler(0, handle_analog);
	vrpnButton->register_change_handler(0, handle_button);

	while (1)
	{
		vrpnAnalog->mainloop();
		vrpnButton->mainloop();
	}

	return 0;
}