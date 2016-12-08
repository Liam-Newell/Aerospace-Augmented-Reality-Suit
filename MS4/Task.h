#pragma once
#include "Stimulation.h"
#include "Exoskeleton.h"
#include "Stims.h"
#include <string>
#include <list>
#include <iostream>

using namespace std;

	class Task
	{
		list <Stimulation*> stimus;
		string name;
	public:
		Task() {
			stimus.clear();
		};
		Task(std::string _name) {
			stimus.clear();
			name = _name;
		}
		
		Task(const Task&);
		Task& operator =(Task&);
		string getName() { return name; }
		void Init(const Task&);
		Task(Task&&);
		Task& operator+=(Stimulation&);
		Stimulation*& operator[](const int pos)
		{
			if (pos >= 0 && pos < stimus.size()) {
				auto it = stimus.begin();
				for (int i = 0; i < pos; i++) ++it;
				return (*it);
			}
			throw std::string("Out of Bounds!");
		};
		void removeTask(std::string);
		std::ostream& dump(ostream&);
		void display(std::ostream& os)const {
			os << "Task: " << name << endl;
			if (!name.empty()) {
				for (auto it = stimus.begin(); it != stimus.end(); ++it) {
					(*it)->display(os);
				}
			}
		}
		std::ostream& operator<<(std::ostream& os)const {
			display(os);
			return os;
		};
		~Task() {
			for (auto&& stim : stimus) {
				delete stim;
				stim = nullptr;
			}
		};

	};


