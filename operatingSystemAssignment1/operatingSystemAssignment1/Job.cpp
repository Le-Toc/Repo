#include <iostream>
#include "Job.hpp"

using namespace std;

//Constructor
Job::Job(string name, int arrivalTime, int duration) : name(name), arrivalTime(arrivalTime), duration(duration)
{
}

//Destructor
Job::~Job()
{
}

//Properties (Usually in header file)
int Job::getArrivalTime()
{
	return arrivalTime;
}

//Properties (Usually in header file)
int Job::getDuration()
{
	return duration;
}

std::string Job::getName()
{
	return name;
}

//Other Methods
void Job::print()
{
	cout << name << ", " << arrivalTime << ", " << duration << endl;
}