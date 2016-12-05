#pragma once
#include "Araig_Sensors.h"
#include <vector>

using namespace std;
struct calibration
{
	int max = 0, min = 0;
};


class Profile
{
	string sFname,sLname;
	int sNum;
	string iFname, iLname;
	int iNum;
	calibration sInt;
	vector <Task*> ToRun;
	vector <Task*> Completed;
	Task *LastTask, *NextTask;

public:

	Profile(char*, ostream&, ARAIG_Sensors&);
	ostream& displayrun(ostream&, int i =0);
	ostream & displayCompleted(ostream &);
	ostream & recent(ostream& os);
	ostream & next(ostream& os);
	ostream & info(ostream& os);
	void run();
};

