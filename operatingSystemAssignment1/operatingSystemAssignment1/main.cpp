#include <iostream>
#include <vector>
#include "Job.hpp"

void runProgram();
void readJobsInFromTheFile(std::vector<Job>& jobVector);
void outputCurrentJob(std::vector<Job>& fifoJobs, int& time, bool& allJobsAreDone, int& job, int currentTime,
	int startingTime);
std::vector<Job> getFIFOSchedule(std::vector<Job> jobVector);
void print(std::vector<Job> vectorStudent, std::string header);
void print(std::vector<Job> vectorStudent);
int getStartingTime(std::vector<Job> fifoJobs);
void outputShortestJobFirst(std::vector<Job> originalJobVector, int currentTime, std::vector<Job>& sjfJobs,
	int& sjfJob, bool sjfAJobIsRunning);
void sortSJFJobsList(std::vector<Job>& sjfJobs);
void outputCurrentJobs(Job job, std::string jobType);
void addToEntry(int& currentTime, std::string jobName);
void loadInSchedulers(std::vector<Job>& jobVector, std::vector<Job>& fifoJobs, int& fifoStartingTime);
void outputMessage(std::string message, std::string jobName);
void updateAllOfTheSchedules(std::vector<Job>& fifoJobs, int& fifoJobTime, bool& allJobsAreDone,
	int& currentFIFOJob, int& currentTime, int& fifoStartingTime, bool& allFIFOJobsAreDone,
	bool& allSJFJobsAreDone, std::vector<Job>& jobVector, int& currentSJFJob, bool& sjfAJobIsRunning,
	std::vector<Job>& sjfList, int& sjfJobTime);
void updateFIFO(std::vector<Job>& fifoJobs, int& fifoJobTime, int& currentFIFOJob, int& currentTime,
	bool& allFIFOJobsAreDone, bool& allJobsAreDone);
void updateSJF(std::vector<Job> jobVector, int& sjfJobTime, int& currentTime, std::vector<Job>& sjfList,
	int& currentSJFJob, bool& sjfAJobIsRunning, bool& allSJFJobsAreDone);
void updateSJFList(std::vector<Job> sjfjobVector, int& currentTime, std::vector<Job>& sjfList,
	bool& jobHasBeenAddedToTheList, std::vector<int>& jobsDone);
void runJob(std::vector<Job>& sjfList, int& sjfJobTime, int& currentTime, bool& sjfAJobIsRunning,
	int& currentSJFJob);
void output(int message);
void output(std::string message);

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
	bool allSJFJobsAreDone = false;
	//bool allJobsAreDone = false;
	//bool allJobsAreDone = false;
	std::vector<Job> fifoJobs;
	int fifoStartingTime;
	int currentFIFOJob = 0;

	int currentSJFJob = 0;
	bool sjfAJobIsRunning = false;
	std::vector<Job> sjfList;
	int sjfJobTime = 0;

	//Read in from the file
	readJobsInFromTheFile(jobVector);

	//Load in schedules if neccissary, mostly FIFO at this point
	loadInSchedulers(jobVector, fifoJobs, fifoStartingTime);

	while (!allJobsAreDone)
	{
		//Update 
		updateAllOfTheSchedules(fifoJobs, fifoJobTime, allJobsAreDone, currentFIFOJob, currentTime,
			fifoStartingTime, allFIFOJobsAreDone, allSJFJobsAreDone, jobVector, currentSJFJob, sjfAJobIsRunning,
			sjfList, sjfJobTime);
		fifoJobTime++;
		sjfJobTime++;
		currentTime++;
	}

	std::cout << "= SIMULATION COMPLETE" << std::endl;
	
	/*int job = 0;
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
	fifoStartingTime = fifoJobs[0].getArrivalTime();
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
	int& currentFIFOJob, int& currentTime, int& fifoStartingTime, bool& allFIFOJobsAreDone,
	bool& allSJFJobsAreDone, std::vector<Job>& jobVector, int& currentSJFJob, bool& sjfAJobIsRunning,
	std::vector<Job>& sjfList, int& sjfJobTime)
{
	if (!allFIFOJobsAreDone)
	{
		if (fifoJobTime >= fifoStartingTime)
		{
			//updateFIFO(fifoJobs, fifoJobTime, currentFIFOJob, currentTime, allFIFOJobsAreDone, allJobsAreDone);
		}
	}
	
	if (!allSJFJobsAreDone)
	{
		updateSJF(jobVector, sjfJobTime, currentTime, sjfList, currentSJFJob, sjfAJobIsRunning,
			allSJFJobsAreDone);
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
		}
	}
	
	else
	{
		//Output the current time and the FIFO job being run
		addToEntry(currentTime, fifoJobs[currentFIFOJob].getName());
	}
}

void updateSJF(std::vector<Job> sjfjobVector, int& sjfJobTime, int& currentTime, std::vector<Job>& sjfList,
	int& currentSJFJob, bool& sjfAJobIsRunning, bool& allSJFJobsAreDone)
{
	std::vector<int> jobsDone;
	bool jobHasBeenAddedToTheList = false;
	
	updateSJFList(sjfjobVector, currentTime, sjfList, jobHasBeenAddedToTheList, jobsDone);

	//If there aren't check if we are running a program
	if (!jobHasBeenAddedToTheList)
	{
		//If we aren't check if there are any jobs left in jobVector
		if (!sjfAJobIsRunning)
		{
			//If there isn't any jobs left set allSJFJobsAreDone to true

			if (sjfjobVector.size() == jobsDone.size())
			{
				allSJFJobsAreDone = true;
			}

			//If there are jobs left
			else
			{
				//std::cout << "Dong" << std::endl;
				//output "-" as a message
				addToEntry(currentTime, "-");
			}
		}
	}

	if (sjfList.size() > 1)
	{
		sortSJFJobsList(sjfList);
	}

	//Run the shortest job until completion
	if (sjfList.size() > 0)
	{
		runJob(sjfList, sjfJobTime, currentTime, sjfAJobIsRunning, currentSJFJob);
	}
}

void updateSJFList(std::vector<Job> sjfjobVector, int& currentTime, std::vector<Job>& sjfList,
	bool& jobHasBeenAddedToTheList, std::vector<int>& jobsDone)
{
	//Get a list of all the jobs, jobVector
	for (unsigned int i = 0; i < sjfjobVector.size(); i++)
	{
		//At time t check if there are any jobs arriving
		if (sjfjobVector[i].getArrivalTime() == currentTime)
		{
			//If there are add them to a list of jobsThatNeedToBeSorted and remove them from jobVector
			outputMessage("Arrival: ", sjfjobVector[i].getName());
			sjfList.push_back(sjfjobVector[i]);
			jobHasBeenAddedToTheList = true;
			jobsDone.push_back(i);
		}

		else
		{
			jobHasBeenAddedToTheList = false;
		}
	}
}

void runJob(std::vector<Job>& sjfList, int& sjfJobTime, int& currentTime, bool& sjfAJobIsRunning,
	int& currentSJFJob)
{
	int duration = sjfList[0].getDuration();
	//std::cout << "Duration " << duration << std::endl;

	//Get the current value of the duration
	duration -= sjfJobTime;

	//If the job is finished...
	if (duration == 0)
	{
		outputMessage("COMPLETE: ", sjfList[currentSJFJob].getName());
		addToEntry(currentTime, sjfList[currentSJFJob].getName());
		sjfList.erase(sjfList.begin());

		sjfAJobIsRunning = false;

		//Reset the SJF job time seeing as a new job has started
		sjfJobTime = 0;
	}

	else
	{
		//std::cout << "DING" << std::endl;
		//Output the current time and the SJF job being run
		addToEntry(currentTime, sjfList[0].getName());
		sjfAJobIsRunning = true;
	}
}

void sortSJFJobsList(std::vector<Job>& sjfList)
{
	for (unsigned int i = 0; i < sjfList.size(); i++)
	{
		for (unsigned int testJobPosition = i + 1; testJobPosition < sjfList.size(); testJobPosition++)
		{
			if (sjfList[i].getDuration() > sjfList[testJobPosition].getDuration())
			{
				//Switch the two jobs
				//Make a copy of the first one
				Job temp = sjfList[i];

				//Move the second one into the first one
				sjfList[i] = sjfList[testJobPosition];

				//Replace the second one with the first one from the temp job
				sjfList[testJobPosition] = temp;
			}
		}
	}
}

void output(std::string message)
{
	std::cout << message << std::endl;
}

void output(int message)
{
	std::cout << message << std::endl;
}

void outputMessage(std::string message, std::string jobName)
{
	std::cout << message << jobName << std::endl;
}

void addToEntry(int& currentTime, std::string jobName)
{
	std::cout << currentTime << " " << jobName << std::endl;
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