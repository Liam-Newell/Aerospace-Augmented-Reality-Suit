#include"Task.h"
Task::Task(const Task &src)
{
	if (this != &src) 
	{
		name = src.name;
		
		Init(src);
		

	}
}

void Task::Init(const Task &src)
{
	for (auto it = src.stimus.begin();it != src.stimus.end(); it++) 
		{
			stimus.push_back(*it);
		}
}

Task::Task(Task &&src)
{
	if (this != &src)
	{
		name = src.name;

		Init(src);
	}
	src.~Task();
}

Task& Task::operator+=(Stimulation &src)
{
	stimus.push_back(&src);
	return *this;
	// TODO: insert return statement here
}

void Task::removeTask( std::string index)
{
	//stimus.remove(stimus == index);
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
	// TODO: insert return statement here
}

//Stimulation *& Task::operator+=(const Task &src)
//{
//	// TODO: insert return statement here
//	Init(src);
//	auto it = src.stimus.begin();
//	return src.stimus;
//}