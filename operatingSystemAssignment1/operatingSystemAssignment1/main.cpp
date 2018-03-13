#include <iostream>
#include <vector>
#include "Job.hpp"

void runProgram();
void readJobsInFromTheFile(std::vector<Job>& jobVector);
void outputCurrentJob(std::vector<Job>& fifoJobs, int& time, bool& allJobsAreDone, int& job, int currentTime,
	int startingTime);
std::vector<Job> getFIFOSchedule(std::vector<Job> jobVector);
void print(std::vector<Job> vectorStudent, std::string header);
int getStartingTime(std::vector<Job> fifoJobs);
void outputShortestJobFirst(std::vector<Job> originalJobVector, int currentTime, std::vector<Job>& sjfJobs,
	int& sjfJob, bool sjfAJobIsRunning);
void sortSJFJobsList(std::vector<Job>& sjfJobs);
void outputCurrentJobs(Job job, std::string jobType);
void addToEntry(int& currentTime, std::string jobName);
void loadInSchedulers(std::vector<Job>& jobVector, std::vector<Job>& fifoJobs, int& fifoStartingTime);
void outputMessage(std::string message, std::string jobName);
void updateAllOfTheSchedules(std::vector<Job>& fifoJobs, int& fifoJobTime, bool& allJobsAreDone,
	int& currentFIFOJob, int& currentTime, int& fifoStartingTime, bool& allFIFOJobsAreDone);
void updateFIFO(std::vector<Job>& fifoJobs, int& fifoJobTime, int& currentFIFOJob, int& currentTime,
	bool& allFIFOJobsAreDone, bool& allJobsAreDone);

int main()
{
	runProgram();
	
	system("pause");
	return 0;
}

void runProgram()
{
	//Declare all variables
	std::vector<Job> jobVector;
	std::vector<Job> sjfJobs;
	int fifoJobTime = 0, currentTime = 0;
	bool allJobsAreDone = false;
	bool allFIFOJobsAreDone = false;
	//bool allJobsAreDone = false;
	//bool allJobsAreDone = false;
	//bool allJobsAreDone = false;
	std::vector<Job> fifoJobs;
	int fifoStartingTime;
	int currentFIFOJob = 0;

	//Read in from the file
	readJobsInFromTheFile(jobVector);

	//Load in schedules if neccissary, mostly FIFO at this point
	loadInSchedulers(jobVector, fifoJobs, fifoStartingTime);

	while (!allJobsAreDone)
	{
		//Update 
		updateAllOfTheSchedules(fifoJobs, fifoJobTime, allJobsAreDone, currentFIFOJob, currentTime,
			fifoStartingTime, allFIFOJobsAreDone);
		fifoJobTime++;
		currentTime++;
	}

	std::cout << "= SIMULATION COMPLETE" << std::endl;
	
	/*int job = 0;
	int sjfJob = 0;
	bool sjfAJobIsRunning = false;
	//Output current job
	while (!allJobsAreDone)
	{
		outputShortestJobFirst(jobVector, currentTime, sjfJobs, sjfJob, sjfAJobIsRunning);
		outputCurrentJob(fifoJobs, time, allJobsAreDone, job, currentTime, startingTime);
		currentTime++;
	}*/

	
}

void readJobsInFromTheFile(std::vector<Job>& jobVector)
{
	//This is where I will read data in from a file.  For the time being I'm using hard coded values
	Job j1("A", 10, 18);
	Job j2("B", 29, 2);
	Job j3("X", 3, 100);
	Job j4("Z", 4, 49);
	Job j5("UNKNOWN", 1, 92);
	Job j6("C", 1, 10);
	Job j7("D", 1, 49);
	Job j8("E", 1, 100);

	jobVector.push_back(j1);
	jobVector.push_back(j2);
	jobVector.push_back(j3);
	jobVector.push_back(j4);
	jobVector.push_back(j5);
	jobVector.push_back(j6);
	jobVector.push_back(j7);
	jobVector.push_back(j8);
}

void loadInSchedulers(std::vector<Job>& jobVector, std::vector<Job>& fifoJobs, int& fifoStartingTime)
{
	fifoJobs = getFIFOSchedule(jobVector);
	fifoStartingTime = getStartingTime(fifoJobs);
}

std::vector<Job> getFIFOSchedule(std::vector<Job> jobVector)
{
	//Create a new vector or jobs
	std::vector<Job> fifoJobs;

	for (unsigned int i = 0; i < jobVector.size(); i++)
	{
		fifoJobs.push_back(jobVector[i]);
	}

	//Sort new job list;
	for (unsigned int i = 0; i < fifoJobs.size(); i++)
	{
		for (unsigned int testJobPosition = i + 1; testJobPosition < fifoJobs.size(); testJobPosition++)
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

void updateAllOfTheSchedules(std::vector<Job>& fifoJobs, int& fifoJobTime, bool& allJobsAreDone,
	int& currentFIFOJob, int& currentTime, int& fifoStartingTime, bool& allFIFOJobsAreDone)
{
	if (!allFIFOJobsAreDone)
	{
		if (fifoJobTime >= fifoStartingTime)
		{
			updateFIFO(fifoJobs, fifoJobTime, currentFIFOJob, currentTime, allFIFOJobsAreDone, allJobsAreDone);
		}
	}
}

void updateFIFO(std::vector<Job>& fifoJobs, int& fifoJobTime, int& currentFIFOJob, int& currentTime,
	bool& allFIFOJobsAreDone, bool& allJobsAreDone)
{
	//Check if a job has just arrived
	for (Job j : fifoJobs)
	{
		if (j.getArrivalTime() == currentTime)
		{
			outputMessage("ARRIVED: ", j.getName());
		}
	}
	
	//Get the duration of the current job
	int duration = fifoJobs[currentFIFOJob].getDuration();
	
	//Get the current value of the duration
	duration -= fifoJobTime;
	
	//If the job is finished...
	if (duration == 0)
	{
		outputMessage("COMPLETE: ", fifoJobs[currentFIFOJob].getName());
		addToEntry(currentTime, fifoJobs[currentFIFOJob].getName());

		//Move onto the next job
		currentFIFOJob++;

		//Reset the FIFO job time seeing as a new job has started
		fifoJobTime = 0;
		
		//Check if there are any more jobs in the FIFO shedule
		if (currentFIFOJob == fifoJobs.size())
		{
			allFIFOJobsAreDone = true;
			allJobsAreDone = true;
		}
	}
	
	else
	{
		//Output the current time and the FIFO job being run
		addToEntry(currentTime, fifoJobs[currentFIFOJob].getName());
	}
}










void outputShortestJobFirst(std::vector<Job> originalJobVector, int currentTime, std::vector<Job>& sjfJobs,
	int& sjfJob, bool sjfAJobIsRunning)
{
	Job temp;

	//Run through all of the jobs in the job vector
	for (Job j : originalJobVector)
	{
		//If the job is starting now add it to the needsToBeSortedList
		if (j.getArrivalTime() == currentTime)
		{
			sjfJobs.push_back(j);
		}
	}

	//Send the needsToBeSortedList to a method to sort it
	if (sjfJobs.size() > 1)
		sortSJFJobsList(sjfJobs);

	//Check if a job is running at this time
	if (!sjfAJobIsRunning)
	{
		//If there isn't one take the first element off of the list and run that one
		//temp = sjfJobs[sjfJob];
	}

	outputCurrentJobs(temp, "SJF");

	
	//Move the other elements up the list
}

void outputCurrentJobs(Job job, std::string jobType)
{
	
}

void outputMessage(std::string message, std::string jobName)
{
	std::cout << message << jobName << std::endl;
}

void addToEntry(int& currentTime, std::string jobName)
{
	std::cout << currentTime << " " << jobName << std::endl;
}

void sortSJFJobsList(std::vector<Job>& sjfJobs)
{
	for (unsigned int i = 0; i < sjfJobs.size(); i++)
	{
		for (unsigned int testJobPosition = i + 1; testJobPosition < sjfJobs.size(); testJobPosition++)
		{
			if (sjfJobs[i].getDuration() > sjfJobs[testJobPosition].getDuration())
			{
				//Switch the two jobs
				//Make a copy of the first one
				Job temp = sjfJobs[i];

				//Move the second one into the first one
				sjfJobs[i] = sjfJobs[testJobPosition];

				//Replace the second one with the first one from the temp job
				sjfJobs[testJobPosition] = temp;
			}
		}
	}
}



void outputCurrentJob(std::vector<Job>& fifoJobs, int& time, bool& allJobsAreDone, int& job, int currentTime,
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
			std::cout << currentTime << " " << fifoJobs[job].getName() << std::endl;
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

	time++;
}



void print(std::vector<Job> vectorJob, std::string header)
{
	for (unsigned int i = 0; i < vectorJob.size(); i++)
	{
		std::cout << header << " Job " << i << " :";
		vectorJob[i].print();
	}
}

void print(std::vector<Job> vectorJob)
{
	for (unsigned int i = 0; i < vectorJob.size(); i++)
	{
		vectorJob[i].print();
	}
}