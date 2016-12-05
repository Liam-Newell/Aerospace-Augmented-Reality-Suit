#pragma once
#include <string>
#include <iostream>
#include "Stimulation.h"
#include <iomanip>
	class Exoskeleton :
		public Stimulation
	{
		std::string name;
		size_t intensity;
		size_t duration;

	public:
		Exoskeleton();

		Exoskeleton(std::string n, size_t i, size_t d) : name(n), intensity(i), duration(d) { setName("Exoskeleton"); };
		std::ostream& display(std::ostream& os) const
		{
			return os << name << std::endl << std::setw(-5)
				 << "	Type = " << getName() << std::endl <<
				"	Intensity = "  << intensity << 
				std::endl << "	Duration = " << duration << std::endl;
		};
		std::string getTask()const { return getName(); }
		std::ostream& operator<<(std::ostream& os)const { return display(os); };
		std::string getStim()const { return name; };
		~Exoskeleton();
	};



