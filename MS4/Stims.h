#pragma once
#include "Stimulation.h"
#include <string>
#include <iostream>
#include <iomanip>
	enum class suit { abs, front, back, traps };
	class Stims :
		public Stimulation
	{
		std::string name;
		suit location;
		size_t intensity;
		float frequency;
		size_t duration;
	public:
		Stims(std::string n, suit l, size_t i, float f, size_t d) : name(n), location(l), intensity(i), frequency(f), duration(d) { Stimulation::setName("Stimulation"); };
		~Stims() {};
		
		std::ostream& display(std::ostream& os)const { 
			return os << name << std::setw(-5) <<
				std::endl << "	Type = " << getName() <<
				std::endl << "	Location = " << suit(location) << std::endl <<
				"	Intensity = " << intensity << std::endl <<
				"	Frequency = " << frequency << std::endl <<
				"	Duration = " << duration << std::endl;
		};
		std::string suit(suit s) const {
			switch (s) {
			case suit::abs:
				return "abs";
				break;
			case suit::back:
				return "back";
				break;
			case suit::front:
				return "front";
				break;
			case suit::traps:
				return "traps";
			}
			return "ERR";
		};
		std::ostream& operator<<(std::ostream& os) const{ return display(os); };
		std::string getTask()const { return getName(); };
		std::string getStim()const { return name; };

	};



