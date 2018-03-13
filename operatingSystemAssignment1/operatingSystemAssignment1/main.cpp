#include <iostream>
#include <vector>
#include "Job.hpp"

void outputCurrentJob(std::vector<Job>& fifoJobs, int& time, bool& allJobsAreDone, int& job, int& currentTime,
	int startingTime);
std::vector<Job> getFIFOSchedule(std::vector<Job> jobVector);
void print(std::vector<Job> vectorStudent, std::string header);
int getStartingTime(std::vector<Job> fifoJobs);

int main()
{
	int time = 0, currentTime = 0;
	bool allJobsAreDone = false;

	Job s1("A", 10, 18);
	Job s2("B", 29, 2);
	Job s3("X", 3, 100);
	Job s4("Z", 4, 49);
	Job s5("UNKNOWN", 1, 92);

	std::vector<Job> jobVector;
	jobVector.push_back(s1);
	jobVector.push_back(s2);
	jobVector.push_back(s3);
	jobVector.push_back(s4);
	jobVector.push_back(s5);

	std::vector<Job> fifoJobs = getFIFOSchedule(jobVector);

	//print(fifoJobs, "fifoJobs");

	int startingTime = getStartingTime(fifoJobs);

	int job = 0;
	//Output current job
	while (!allJobsAreDone)
	{
		outputCurrentJob(fifoJobs, time, allJobsAreDone, job, currentTime, startingTime);
	}

	system("pause");
	return 0;
}

int getStartingTime(std::vector<Job> fifoJobs)
{
	int startingTime = 100000;//I'm assumming that no arrival time will exceed this.

	for (Job j : fifoJobs)
	{
		if (j.getArrivalTime() < startingTime)
			startingTime = j.getArrivalTime();
	}

	return startingTime;
}

void outputCurrentJob(std::vector<Job>& fifoJobs, int& time, bool& allJobsAreDone, int& job, int& currentTime,
	int startingTime)
{
	if (time >= startingTime)
	{
		for (Job j : fifoJobs)
		{
			if (j.getArrivalTime() == currentTime)
				std::cout << "ARRIVED: " << j.getName() << std::endl;
		}

		int duration = fifoJobs[job].getDuration();

		duration -= time;

		if (duration == 0)
		{
			std::cout << "COMPLETE: " << fifoJobs[job].getName() << std::endl;
			job++;
			time = 0;

			if (job == fifoJobs.size())
			{
				allJobsAreDone = true;
			}
		}

		else
		{
			std::cout << currentTime << " " << fifoJobs[job].getName() << std::endl;
		}
	}
	
	time++, currentTime++;
}

std::vector<Job> getFIFOSchedule(std::vector<Job> jobVector)
{
	//Create a new vector or jobs
	std::vector<Job> fifoJobs;

	for (int i = 0; i < jobVector.size(); i++)
	{
		fifoJobs.push_back(jobVector[i]);
	}

	//Sort new job list;
	for (int i = 0; i < fifoJobs.size(); i++)
	{
		for (int testJobPosition = i + 1; testJobPosition < fifoJobs.size(); testJobPosition++)
		{
			if (fifoJobs[i].getArrivalTime() > fifoJobs[testJobPosition].getArrivalTime())
			{
				//Switch the two jobs
				//Make a copy of the first one
				Job temp = fifoJobs[i];

				//Move the second one into the first one
				fifoJobs[i] = fifoJobs[testJobPosition];

				//Replace the second one with the first one from the temp job
				fifoJobs[testJobPosition] = temp;
			}
		}
	}

	return fifoJobs;
}

void print(std::vector<Job> vectorJob, std::string header)
{
	for (int i = 0; i < vectorJob.size(); i++)
	{
		std::cout << header << " Job " << i << " :";
		vectorJob[i].print();
	}
}