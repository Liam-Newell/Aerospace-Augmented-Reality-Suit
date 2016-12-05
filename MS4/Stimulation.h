#pragma once
#include <string>
#include <iostream>


	class Stimulation
	{
		std::string name;
	protected:
		std::string getName()const { return name; };
		void setName(std::string src) { name = src; }
	public:
		virtual std::ostream& display(std::ostream&)const = 0;
		virtual std::ostream& operator<<(std::ostream&)const = 0;
		virtual std::string getTask() const = 0;
		virtual std::string getStim() const = 0;
	};


