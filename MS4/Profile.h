#pragma once
#include "Araig_Sensors.h"
#include <vector>
#include <deque>

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
	deque <Task*> ToRun;
	vector <Task*> Completed;
	Task *LastTask, *NextTask;
public:
	Profile(char*, ostream&, ARAIG_Sensors&);
	ostream& displayrun(ostream&, int i =0)const;
	ostream & displayCompleted(ostream &)const;
	ostream & recent(ostream& os)const;
	ostream & next(ostream& os)const;
	ostream & info(ostream& os) const;
	void run();
	~Profile();
};

