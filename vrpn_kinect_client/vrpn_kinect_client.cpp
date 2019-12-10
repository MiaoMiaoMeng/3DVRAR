#include "vrpn_Tracker.h"
#include <iostream>
using namespace std;

void VRPN_CALLBACK handle_tracker_Right_Elbow(void* userData, const vrpn_TRACKERCB t)
{
	cout << "Tracker_Elbow '" << t.sensor << "' : " << t.pos[0] << "," << t.pos[1] << "," << t.pos[2] << endl;
}

void VRPN_CALLBACK handle_tracker_Right_Wrist(void* userData, const vrpn_TRACKERCB t)
{
	cout << "Tracker_Wrist '" << t.sensor << "' : " << t.pos[0] << "," << t.pos[1] << "," << t.pos[2] << endl;
}

void VRPN_CALLBACK handle_tracker_Right_Hand(void* userData, const vrpn_TRACKERCB t)
{
	cout << "Tracker_Hand '" << t.sensor << "' : " << t.pos[0] << "," << t.pos[1] << "," << t.pos[2] << endl;
}

void VRPN_CALLBACK handle_tracker_Right_Fingertip(void* userData, const vrpn_TRACKERCB t)
{
	cout << "Tracker_Fingertip '" << t.sensor << "' : " << t.pos[0] << "," << t.pos[1] << "," << t.pos[2] << endl;
}



int main(int argc, char* argv[])
{   
	vrpn_Tracker_Remote* vrpnTracker_Right_Elbow = new vrpn_Tracker_Remote("Tracker0@localhost");
	vrpn_Tracker_Remote* vrpnTracker_Right_Wrist = new vrpn_Tracker_Remote("Tracker1@localhost");
	vrpn_Tracker_Remote* vrpnTracker_Right_Hand = new vrpn_Tracker_Remote("Tracker2@localhost");
	vrpn_Tracker_Remote* vrpnTracker_Right_Fingertip = new vrpn_Tracker_Remote("Tracker3@localhost");

	vrpnTracker_Right_Elbow->register_change_handler(0, handle_tracker_Right_Elbow);
	vrpnTracker_Right_Wrist->register_change_handler(0, handle_tracker_Right_Wrist);
	vrpnTracker_Right_Hand->register_change_handler(0, handle_tracker_Right_Hand);
	vrpnTracker_Right_Fingertip->register_change_handler(0, handle_tracker_Right_Fingertip);

	while (1)
	{
		vrpnTracker_Right_Elbow->mainloop();
		vrpnTracker_Right_Wrist->mainloop();
		vrpnTracker_Right_Hand->mainloop();
		vrpnTracker_Right_Fingertip->mainloop();
	}

	return 0;
}