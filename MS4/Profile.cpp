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
				//create copy rather than a move
				//Temp to store a copy//Copy task
				ToRun.push_back(new Task(*Tsrc.getTask(tempTask)));//Copy task to pointer array
				//ToRun.push_back(Tsrc.getTask(tempTask));
			}
	}

}

ostream & Profile::displayrun(ostream &os, int i) const
{
	os << "\nFor Student " << sFname << endl;

	for (i ;i < ToRun.size();i++)
	{
		ToRun[i]->display(os);
	}
	return os;
}

ostream & Profile::displayCompleted(ostream &os) const
{
	os << "\nFor Student " << sFname << endl;

	for (auto i = 0;i < Completed.size();i++)
	{
		Completed[i]->display(os);
	}
	return os;
}

ostream & Profile::recent(ostream & os) const
{
	os << "\nPrevious Task is" << endl << LastTask->getName() << endl;
	return os;
}

ostream & Profile::next(ostream & os) const
{
	os << "\nNext Task is" << endl << NextTask->getName() << endl;
	return os;
}

ostream & Profile::info(ostream & os) const
{
	os << "For Student " << sFname << " " << sLname << " " << sNum << endl;
	os << "With Instructor " << iFname << " " << iLname << " " << iNum << endl;
	cout << "The Flight Plan Is" << endl <<endl;
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
	size_t tSize = ToRun.size();
	while (cont == true) {
		cout << endl << "For the previous task type : 'p'\nFor the next Task Type : 'n'\nTo show the tasks to run type : 'r'\nTo show the tasks that are completed : 'c'\nTo advance flight do anything else\nTo repeat the test info press 'i'\nTo repeat a Task type 'a'\nTo Quit Press 'e'\n";
		cin.clear();
		cin.get(input);
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		switch (input)
		{
		case 'p': {
			if (loopc > 0) {
				recent(cout);
			}
			else {
				cout << "\nNo Prev Task";
			}
			break;
		}
		case 'a': {
			bool cont = true;
			string ttask;
			int i = 0, j = 0;
			cout << "\nWhich Task do you wish to repeat?\n";
			cin >> ttask;
			for (i = 0; i < ToRun.size(); i++)
			{
				if (ToRun[i]->getName().compare(ttask) == 0) {
					ToRun.push_back(new Task(*ToRun[i]));
					cout << "\nClass Copied From To Run\n";
					cont = false;
					break;
				}

			}
			if (cont)
			{
				for (size_t i = 0; i < Completed.size(); i++)
				{
					if (Completed[i]->getName().compare(ttask) == 0) {
						ToRun.push_back(new Task(*Completed[i]));
						cout << "\nClass Copied From Completed Tasks\n";
						cont = false;
						break;
					}
					
				}
			}
					
			if (cont)
				cout << "\nNo Such Task could be repeated. Check the list with 'i'\n";
			
			break;
		}
		case 'n': {
			if (!ToRun.empty()) {
				NextTask = ToRun[0];
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
			ToRun[0]->display(cout);
			Task* p = ToRun[0];
			LastTask = p;
			ToRun.pop_front();
			Completed.push_back(p);
			loopc++;
			if (ToRun.empty())
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

Profile::~Profile()
{
	ToRun.~deque();
	Completed.~vector();
	LastTask = nullptr;
	NextTask = nullptr;
	for(auto&& i : ToRun)
	i = nullptr;
	for(auto&& i: Completed)
	i = nullptr;
	/*for (auto i = 0; i < ToRun.size(); i++)
	{
		ToRun[i]->~Task();
		ToRun[i] = nullptr;
	}
	
	delete[] &Completed;
	delete[] LastTask;
	delete[] NextTask;
	for(auto i = 0;ToRun[i] != nullptr;i++)
		ToRun[i] = nullptr;
	for (auto i = 0; Completed[i] != nullptr; i++)
		Completed[i] = nullptr;*/
	

}
