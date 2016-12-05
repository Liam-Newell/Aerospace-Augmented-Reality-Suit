#include "Profile.h"

Profile::Profile(char * f, ostream & os, ARAIG_Sensors & Tsrc)
{
	ifstream file(f);

	if (!file.is_open())
		throw string("Couldn't open the profile file \nPlease check the config");
	else
	{
		
			getline(file, sFname, ',');
			getline(file, sLname, ',');
			file >> sNum;
			file.ignore();
			getline(file, iFname, ',');
			getline(file, iLname, ',');
			file >> iNum;
			file.ignore();
			file >> sInt.max;
			file.ignore();
			file >> sInt.min;
			file.ignore();
			while (!file.eof())
			{
				string tempTask;
				getline(file, tempTask);

				ToRun.push_back(Tsrc.getTask(tempTask));
			}
	}

}

ostream & Profile::displayrun(ostream &os, int i)
{
	os << "\nFor Student " << sFname << endl;

	for (i ;i < ToRun.size();i++)
	{

		ToRun[i]->display(os);
	}
	return os;
}

ostream & Profile::displayCompleted(ostream &os)
{
	os << "\nFor Student " << sFname << endl;

	for (auto i = 0;i < Completed.size();i++)
	{
		Completed[i]->display(os);
	}
	return os;
}

ostream & Profile::recent(ostream & os)
{
	os << "\nPrevious Task is" << endl << LastTask->getName() << endl;
	return os;
}

ostream & Profile::next(ostream & os)
{
	os << "\nNext Task is" << endl << NextTask->getName() << endl;
	return os;
}

ostream & Profile::info(ostream & os)
{
	os << "For Student " << sFname << " " << sLname << " " << sNum << endl;
	os << "With Instructor " << iFname << " " << iLname << " " << iNum << endl;
	cout << "The Flight Plan Is" << endl << endl;
	for (auto i = 0;i < ToRun.size();i++)
	{
		cout << ToRun[i]->getName() << endl;
	}
	os << endl << "Max Intensity Is " << sInt.max << endl << "Min intensity Is " << sInt.min << endl;
	return os;
	// TODO: insert return statement here
}

void Profile::run()
{
	info(cout);
	char input;
	bool cont = true;
	int loopc = 0;
	while (cont == true) {
		cout << endl << "For the previous task type : 'p'\nFor the next Task Type : 'n'\nTo show the tasks to run type : 'r'\nTo show the tasks that are completed : 'c'\nTo advance flight do anything else\nTo repeat the test info press 'i'\nTo Quit Press 'e'\n";
		cin.clear();
		cin.get(input);
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		switch (input)
		{
		case 'p': {
			if (loopc > 0) {
				LastTask = ToRun[loopc -1];
				recent(cout);
			}
			else {
				cout << "\nNo Prev Task";
			}
			break;
		}
		case 'n': {
			if (loopc < ToRun.size()) {
				NextTask = ToRun[loopc];
				next(cout);
			}
			else {
				cout << "\nNo Tasks Left To Run";
			}
			break;
		}
		case 'r': 
			displayrun(cout,loopc);
			if (!cout)
				cout << "'\nno Tasks to run";
			break;
		case 'c': 
			if (Completed.empty())
				cout << "\nNo Completed Tasks";
			else
				displayCompleted(cout);
			break;
		case 'e':
			cont = false;
			break;
		case 'i':
			cout << endl;
			info(cout);
			break;
		default: {
			cout << "\nExecuting ";
			ToRun[loopc]->display(cout);
			Completed.push_back(ToRun[loopc]);
			if (Completed.size() != ToRun.size())
				loopc++;
			else
				cont = false;
			break;
		}
		}
		if (cont) {
			cout << "\nPress Anything to continue\n";
			cin.get();
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		}
		else
		{
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
			cout << "\nYou have excuted Flight Plan\n";
			info(cout);
			cout << "\nPress Anything to continue\n";
			cin.get();
		}
	}
	
} 
