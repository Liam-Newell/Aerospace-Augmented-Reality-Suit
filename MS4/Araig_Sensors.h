#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <map>
#include "Task.h"
using namespace std;
//enum class suit { abs, front, back, traps };
class ARAIG_Sensors
{
public:
	ARAIG_Sensors(char*,char*);
	~ARAIG_Sensors();
	suit suitype(string);
	ostream& dump(ostream&);
	Task* getTask(string index) const;
private:
	//vector <>
	Stimulation** sList;
	Task** tList;
	size_t sIndex = 0;
	size_t tIndex = 0;
};



inline ARAIG_Sensors::ARAIG_Sensors(char* fStim, char* fTask)
{
	
	//Ready tasks
	std::string temp;
	size_t stim_size = 0;
	std::ifstream f(fStim);
	while (!f.eof()) {
		getline(f, temp);
		stim_size++;
	}
	temp.clear();
	typedef map<string, float> StringFloatMap;
	f.close();
	f.open(fStim);
	sList = new Stimulation*[stim_size];
	string sType,sName,sLoc;
	size_t sInt, sDur, sFreq;
	while (!f.eof())
	{
		//Run through stimulation file
		getline(f, sType, ',');
		//Test to see what type of stim
		if (sType[0] == 'e') {
			getline(f, sName, ',');
			f >> sInt;
			f.ignore();
			f >> sDur;
			if (!sName.empty() && (sInt >= 0 && sInt <= 100))
			sList[sIndex] = new Exoskeleton(sName, sInt,sDur);
			else {
				string error = "\nIntensity in line " + to_string(sIndex) + " Caused an error\nPossibly not beteen 0 and 100";
				throw string(error);
			}
			f.ignore();
		}
		else if (sType[0] == 's')  
		{
			getline(f, sName, ',');
			getline(f, sLoc, ',');
			f >> sInt;
			f.ignore();
			f >> sFreq;
			f.ignore();
			f >> sDur;
			//the name has a space before it, it accounts for that and removes it before submission
			if(!(sName.empty() && sLoc.empty()) && (sInt >= 0 && sInt <= 100)) 
			sList[sIndex] = new Stims(sName, suitype(sLoc), sInt,sFreq,sDur);
			else {
				string error = "\nIntensity in line " + to_string(sIndex) + " Caused an error\nPossibly not beteen 0 and 100";
				throw string(error);
			}
			f.ignore();
		}
		else
		{
			//If it had a problem reading a linei n the file
			throw string("General File Error");
		}
		sType.clear();
		sName.clear();
		sLoc.clear();
		
		
		sIndex++;
	}
	f.close();

	f.open(fTask);

	while (!f.eof())
	{
		string temp;
		getline(f, temp);
		if (!temp.find("TASK"))
			tIndex++;
	}
	f.close();
	f.open(fTask);
	tList = new Task*[tIndex];
	size_t index = -1;
	while (!f.eof())
	{
		//fix
		string buffer;
		string tTask, tName,tStim;

		getline(f, buffer);
		if (!buffer.find("TASK")) 
		{
			index++;
			tName = buffer.substr(5,buffer.length());
			tList[index] = new Task(tName);
			
		}
		else {
			if (buffer.find("TASK")) 
				{
				size_t i = 0;
					for (i = 0; i < sIndex; i++)
					{
						
						if (sList[i]->getStim().compare(buffer)==0) 
						{
							(*tList[index])+=*sList[i];
							break;
						}
						
					}
					if (i > sIndex) 
					{
						string err = "\nTask asked for Stimulation that does not exist!\nasked for stim: " + buffer + "Check your config files for stims over ?35?";
						throw string(err);
					}
				}
		}
		//old
		
		
	}
}

inline ARAIG_Sensors::~ARAIG_Sensors()
{
	delete[] sList;
	sList = nullptr;

	delete[] tList;
	tList = nullptr;
}

inline suit ARAIG_Sensors::suitype(string a)
{
	if (a == "abs")
		return suit::abs;
	else if (a == "back")
		return suit::back;
	else if (a == "front")
		return suit::front;
	else if (a == "traps")
		return suit::traps;
	else
		throw string("Invaid suit type");
}

inline ostream& ARAIG_Sensors::dump(ostream& os)
{
	os << endl;
	for (size_t i = 0; i < tIndex; i++)
	{
		(tList[i])->display(os);
	}
	return os;
}

inline Task * ARAIG_Sensors::getTask(string index) const
{
	size_t i = 0;
	for (i = 0; i < tIndex; i++)
	{
		if (tList[i]->getName().compare(index) == 0)
		{
			return tList[i];
			break;
		}

	}
	throw string("Couldn't find task " + index);
}

