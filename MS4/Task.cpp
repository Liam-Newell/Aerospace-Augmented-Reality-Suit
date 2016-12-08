#include"Task.h"

Task::Task(const Task &src)
{
	if (this != &src) 
	{
		name = src.name;
		Init(src);
	}
}

Task & Task::operator=(Task &src)
{
	if (this != &src)
	{
		name = src.name;
		Init(src);
	}
	// TODO: insert return statement here
	return *this;
}

void Task::Init(const Task &src)
{
	
	for (auto it = src.stimus.begin();it != src.stimus.end(); it++) 
		{
		Stimulation *temp = (*it);
			stimus.push_back(temp);
		}
}

Task::Task(Task &&src)
{
	if (this != &src)
	{
		name = src.name;
		for (auto it = src.stimus.begin();it != src.stimus.end(); it++)
		{
			stimus.push_back(*it);
		}
	}
	src.~Task();
}

Task& Task::operator+=(Stimulation &src)
{
	stimus.push_back(&src);
	return *this;
}

void Task::removeTask( std::string index)
{
	for (auto it = stimus.begin(); it != stimus.end();) 
	{
		if ((*it)->getStim().compare(index)==0)
			stimus.erase(it++);
		else ++it;
	}
}

std::ostream & Task::dump(ostream & os)
{
	os << "Task: " << name << endl;
	for (auto it = stimus.begin(); it != stimus.end();++it) {
		os << (*it)->getTask() << endl;
	}
	return os;
}
