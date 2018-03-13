#pragma once
#include <string>

class Job
{
public:
	Job(std::string name, int arrivalTime, int duration);
	~Job();

	//Properities
	int getArrivalTime();
	int getDuration();
	std::string getName();

	//Methods
	void print();

private:
	std::string name;
	int arrivalTime, duration;
};