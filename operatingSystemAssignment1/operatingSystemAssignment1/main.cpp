#include <iostream>
#include <vector>
#include "Job.hpp"

void runProgram();
void readJobsInFromTheFile(std::vector<Job>& jobVector);
std::vector<Job> getFIFOSchedule(std::vector<Job> jobVector);
void print(std::vector<Job> vectorStudent, std::string header);
void print(std::vector<Job> vectorStudent);
int getStartingTime(std::vector<Job> fifoJobs);
void sortSTJFJobsList(std::vector<Job>& sjfJobs);
void addToEntry(std::string jobName, std::vector<std::string>& outputArray, int pos);
void loadInSchedulers(std::vector<Job>& jobVector, std::vector<Job>& fifoJobs, int& fifoStartingTime,
	std::vector<Job>& sjfJobs, std::vector<Job>& rrList);
void outputMessage(std::string message, std::string jobName);
void updateAllOfTheSchedules(std::vector<Job>& fifoJobs, int& fifoJobTime, bool& allJobsAreDone,
	int& currentFIFOJob, int& currentTime, int& fifoStartingTime, bool& allFIFOJobsAreDone,
	bool& allSTCFJobsAreDone, std::vector<Job>& jobVector, int& currentSTCFJob, bool& stcfAJobIsRunning,
	std::vector<Job>& stcfList, int& stcfJobTime, unsigned int& stcfAmountOfJobsDone,
	std::vector<std::string>& outputArray, bool& allSJFJobsAreDone, std::vector<Job>& sjfJobs,
	int& currentSJFJob, int& sjfJobTime, int& currentRRJob, int& rrJobTime, bool& allRRJobsAreDone,
	int& rrNumberOfJobsCompleted, int& timeSliceCount, std::vector<Job>& rrList);
void updateFIFO(std::vector<Job>& fifoJobs, int& fifoJobTime, int& currentFIFOJob, int& currentTime,
	bool& allFIFOJobsAreDone, bool& allJobsAreDone, std::vector<std::string>& outputArray);
void updateSTCF(std::vector<Job> sjfjobVector, int& sjfJobTime, int& currentTime, std::vector<Job>& sjfList,
	int& currentSJFJob, bool& sjfAJobIsRunning, bool& allSJFJobsAreDone, unsigned int& sjfAmountOfJobsDone,
	std::vector<std::string>& outputArray);
void updateSJFList(std::vector<Job> sjfjobVector, int& currentTime, std::vector<Job>& sjfList,
	bool& jobHasBeenAddedToTheList);
void runJob(std::vector<Job>& sjfList, int& sjfJobTime, int& currentTime, bool& sjfAJobIsRunning,
	int& currentSJFJob, unsigned int& sjfAmountOfJobsDone, std::vector<std::string>& outputArray);
void output(int message);
void output(std::string message);
void outputArrayMethod(std::vector<std::string>& outputArray, int& currentTime);
void updateSJF(std::vector<Job>& sjfJobs, int& currentSJFJob, int& sjfJobTime,
	std::vector<std::string>& outputArray, bool& allSJFJobsAreDone, int& currentTime);
void getSJFSchedule(std::vector <Job> jobVector, std::vector<Job>& sjfJobs);
void updateRR(std::vector<Job>& rrList, int timeSlice, int& currentRRJob, int& rrJobTime,
	std::vector<std::string>& outputArray, bool& allRRJobsAreDone, std::vector<Job>& jobVector,
	int& rrNumberOfJobsCompleted, int& timeSliceCount);

int main()
{
	runProgram();
	
	system("pause");
	return 0;
}

void runProgram()
{
	//Declare all variables
	std::vector<std::string> outputArray = {"-", "-", "-", "-", "-" };
	std::vector<Job> jobVector;
	std::vector<Job> stcfJobs;
	int fifoJobTime = 0, currentTime = 0;
	bool allJobsAreDone = false;
	bool allFIFOJobsAreDone = false;
	bool allSJFJobsAreDone = false;
	bool allSTCFJobsAreDone = false;
	bool allRRJobsAreDone = false;
	std::vector<Job> fifoJobs;
	int fifoStartingTime;
	int currentFIFOJob = 0;

	int currentSJCFJob = 0;
	bool stcfJobIsRunning = false;
	std::vector<Job> stcfList;
	int stcfJobTime = 0;
	unsigned int stcfAmountOfJobsDone = 0;

	std::vector<Job> sjfJobs;
	int currentSJFJob = 0;
	int sjfJobTime = 0;
	int currentRRJob = 0;
	int rrJobTime = 0;
	int rrNumberOfJobsCompleted = 0;
	int timeSliceCount = -1;
	std::vector<Job> rrList;

	std::cout << "Time			FIFO		SJF		SJCF		RR		RR" << std::endl;

	//Read in from the file
	readJobsInFromTheFile(jobVector);

	//Load in schedules if neccissary, mostly FIFO at this point
	loadInSchedulers(jobVector, fifoJobs, fifoStartingTime, sjfJobs, rrList);

	while (!allJobsAreDone)
	{
		//Update 
		updateAllOfTheSchedules(fifoJobs, fifoJobTime, allJobsAreDone, currentFIFOJob, currentTime,
			fifoStartingTime, allFIFOJobsAreDone, allSTCFJobsAreDone, jobVector, currentSJCFJob,
			stcfJobIsRunning, stcfList, stcfJobTime, stcfAmountOfJobsDone, outputArray, allSJFJobsAreDone,
			sjfJobs, currentSJFJob, sjfJobTime, currentRRJob, rrJobTime, allRRJobsAreDone,
			rrNumberOfJobsCompleted, timeSliceCount, rrList);

		outputArrayMethod(outputArray, currentTime);
		fifoJobTime++;
		stcfJobTime++;
		sjfJobTime++;
		rrJobTime++;
		currentTime++;
	}

	std::cout << "= SIMULATION COMPLETE" << std::endl;
}

/*
std::vector<Job> getSJCFSchedule(std::vector<Job> jobVector)
{
	std::vector<int> jobCompletionTimes;

	for(int i = 0; i < jobVector.size(); i++)
	{
		jobCompletionTimes[i] = jobVector[i].
	}

	//Create a new vector or jobs
	std::vector<Job> sjcfJobs;

	for (unsigned int i = 0; i < jobVector.size(); i++)
	{
		sjcfJobs.push_back(jobVector[i]);
	}

	//Sort new job list;
	for (unsigned int i = 0; i < sjcfJobs.size(); i++)
	{
		for (unsigned int testJobPosition = i + 1; testJobPosition < sjcfJobs.size(); testJobPosition++)
		{
			if (sjcfJobs[i].getArrivalTime() > sjcfJobs[testJobPosition].getArrivalTime())
			{
				//Switch the two jobs
				//Make a copy of the first one
				Job temp = sjcfJobs[i];

				//Move the second one into the first one
				sjcfJobs[i] = sjcfJobs[testJobPosition];

				//Replace the second one with the first one from the temp job
				sjcfJobs[testJobPosition] = temp;
			}
		}
	}
	return sjcfJobs;
}

void updateSJCF()
{

}
*/

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

void loadInSchedulers(std::vector<Job>& jobVector, std::vector<Job>& fifoJobs, int& fifoStartingTime,
	std::vector<Job>& sjfJobs, std::vector<Job>& rrList)
{
	fifoJobs = getFIFOSchedule(jobVector);
	fifoStartingTime = fifoJobs[0].getArrivalTime();
	getSJFSchedule(jobVector, sjfJobs);
	rrList = getFIFOSchedule(jobVector);
}

void getSJFSchedule(std::vector <Job> jobVector, std::vector<Job>& sjfJobs)
{
	for (unsigned int i = 0; i < jobVector.size(); i++)
	{
		sjfJobs.push_back(jobVector[i]);
	}

	//Sort new job list;
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
	bool& allSTCFJobsAreDone, std::vector<Job>& jobVector, int& currentSTCFJob, bool& stcfAJobIsRunning,
	std::vector<Job>& stcfList, int& stcfJobTime, unsigned int& stcfAmountOfJobsDone,
	std::vector<std::string>& outputArray, bool& allSJFJobsAreDone, std::vector<Job>& sjfJobs,
	int& currentSJFJob, int& sjfJobTime, int& currentRRJob, int& rrJobTime, bool& allRRJobsAreDone,
	int& rrNumberOfJobsCompleted, int& timeSliceCount, std::vector<Job>& rrList)
{
	if (!allFIFOJobsAreDone)
	{
		if (fifoJobTime >= fifoStartingTime)
		{
			updateFIFO(fifoJobs, fifoJobTime, currentFIFOJob, currentTime, allFIFOJobsAreDone, allJobsAreDone,
				outputArray);
		}
	}

	if (!allSTCFJobsAreDone)
	{
		updateSTCF(jobVector, stcfJobTime, currentTime, stcfList, currentSTCFJob, stcfAJobIsRunning,
			allSTCFJobsAreDone, stcfAmountOfJobsDone, outputArray);
	}

	if (!allSJFJobsAreDone)
	{
		if (currentTime > 0)
		{
			updateSJF(sjfJobs, currentSJFJob, sjfJobTime, outputArray, allSJFJobsAreDone, currentTime);
		}
	}

	if (!allRRJobsAreDone)
	{
		if (currentTime > 0)
		{
			int timeSlice = 5;
			updateRR(rrList, timeSlice, currentRRJob, rrJobTime, outputArray, allRRJobsAreDone, jobVector,
				rrNumberOfJobsCompleted, timeSliceCount);
		}
	}

	if (allFIFOJobsAreDone)
	{
		if (allSTCFJobsAreDone)
		{
			if (allSJFJobsAreDone)
			{
				if (allRRJobsAreDone)
				{
					allJobsAreDone = true;
				}
			}
		}
	}
}

void updateRR(std::vector<Job>& rrList, int timeSlice, int& currentRRJob, int& rrJobTime,
	std::vector<std::string>& outputArray, bool& allRRJobsAreDone, std::vector<Job>& jobVector,
	int& rrNumberOfJobsCompleted, int& timeSliceCount)
{
	timeSliceCount++;

	if (timeSliceCount == timeSlice)
	{
		timeSliceCount = 0;
		currentRRJob++;
		if (currentRRJob == rrList.size())
		{
			currentRRJob = 0;
		}
	}

	//Get the duration of the current job
	rrList[currentRRJob].setDuration(rrList[currentRRJob].getDuration() - 1);

	//If the job is finished...
	if (rrList[currentRRJob].getDuration() == 0)
	{
		addToEntry(rrList[currentRRJob].getName(), outputArray, 3);
		outputMessage("RR COMPLETE: ", rrList[currentRRJob].getName());

		rrList.erase(rrList.begin() + currentRRJob);

		if (currentRRJob == rrList.size())
		{
			currentRRJob = 0;
			timeSliceCount = -1;
		}

		rrNumberOfJobsCompleted++;

		//Check if there are any more jobs in the FIFO shedule
		if (rrNumberOfJobsCompleted == jobVector.size())
		{
			allRRJobsAreDone = true;
		}
	}

	else
	{
		//Output the current time and the SJF job being run
		addToEntry(rrList[currentRRJob].getName(), outputArray, 3);
	}
}

void updateSJF(std::vector<Job>& sjfJobs, int& currentSJFJob, int& sjfJobTime,
	std::vector<std::string>& outputArray, bool& allSJFJobsAreDone, int& currentTime)
{
	//Get the duration of the current job
	int duration = sjfJobs[currentSJFJob].getDuration();

	//Get the current value of the duration
	duration -= sjfJobTime;

	//If the job is finished...
	if (duration == 0)
	{
		outputMessage("COMPLETE: ", sjfJobs[currentSJFJob].getName());
		addToEntry(sjfJobs[currentSJFJob].getName(), outputArray, 1);

		//Move onto the next job
		currentSJFJob++;

		//Reset the FIFO job time seeing as a new job has started
		sjfJobTime = 0;

		//Check if there are any more jobs in the FIFO shedule
		if (currentSJFJob == sjfJobs.size())
		{
			allSJFJobsAreDone = true;
			addToEntry("-", outputArray, 1);
		}
	}

	else
	{
		//Output the current time and the SJF job being run
		addToEntry(sjfJobs[currentSJFJob].getName(), outputArray, 1);
	}
}

void updateFIFO(std::vector<Job>& fifoJobs, int& fifoJobTime, int& currentFIFOJob, int& currentTime,
	bool& allFIFOJobsAreDone, bool& allJobsAreDone, std::vector<std::string>& outputArray)
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
		outputMessage("FIFO COMPLETE: ", fifoJobs[currentFIFOJob].getName());
		addToEntry(fifoJobs[currentFIFOJob].getName(), outputArray, 0);

		//Move onto the next job
		currentFIFOJob++;

		//Reset the FIFO job time seeing as a new job has started
		fifoJobTime = 0;

		//Check if there are any more jobs in the FIFO shedule
		if (currentFIFOJob == fifoJobs.size())
		{
			allFIFOJobsAreDone = true;
			addToEntry("-", outputArray, 0);
		}
	}

	else
	{
		//Output the current time and the FIFO job being run
		addToEntry(fifoJobs[currentFIFOJob].getName(), outputArray, 0);
	}
}

void updateSTCF(std::vector<Job> stcfJobVector, int& stcfJobTime, int& currentTime, std::vector<Job>& stcfFList,
	int& currentSTCFJob, bool& stcfAJobIsRunning, bool& allSTCFJobsAreDone, unsigned int& stcfAmountOfJobsDone,
	std::vector<std::string>& outputArray)
{
	bool jobHasBeenAddedToTheList = false;
	
	updateSJFList(stcfJobVector, currentTime, stcfFList, jobHasBeenAddedToTheList);

	//If there aren't check if we are running a program
	if (!jobHasBeenAddedToTheList)
	{
		//If we aren't check if there are any jobs left in jobVector
		if (!stcfAJobIsRunning)
		{
			//If there isn't any jobs left set allSJFJobsAreDone to true
			if (stcfAmountOfJobsDone >= stcfJobVector.size())
			{
				allSTCFJobsAreDone = true;
				addToEntry("-", outputArray, 2);
			}

			//If there are jobs left
			else
			{
				//std::cout << "Dong" << std::endl;
				//output "-" as a message

				addToEntry("-", outputArray, 2);
			}
		}
	}

	if (stcfFList.size() > 1)
	{
		sortSTJFJobsList(stcfFList);
	}

	//Run the shortest job until completion
	if (stcfFList.size() > 0)
	{
		runJob(stcfFList, stcfJobTime, currentTime, stcfAJobIsRunning, currentSTCFJob, stcfAmountOfJobsDone,
			outputArray);
	}
}

void updateSJFList(std::vector<Job> stcfJobVector, int& currentTime, std::vector<Job>& stcfList,
	bool& jobHasBeenAddedToTheList)
{
	//Get a list of all the jobs, jobVector
	for (unsigned int i = 0; i < stcfJobVector.size(); i++)
	{
		//At time t check if there are any jobs arriving
		if (stcfJobVector[i].getArrivalTime() == currentTime)
		{
			//If there are add them to a list of jobsThatNeedToBeSorted and remove them from jobVector
			outputMessage("ARRIVED: ", stcfJobVector[i].getName());
			stcfList.push_back(stcfJobVector[i]);
			jobHasBeenAddedToTheList = true;
		}

		else
		{
			jobHasBeenAddedToTheList = false;
		}
	}
}

void runJob(std::vector<Job>& stcfList, int& stcfJobTime, int& currentTime, bool& stcfAJobIsRunning,
	int& currentSTJFJob, unsigned int& stcfAmountOfJobsDone, std::vector<std::string>& outputArray)
{
	int duration = stcfList[0].getDuration();

	//Get the current value of the duration
	duration -= stcfJobTime;

	//If the job is finished...
	if (duration == 0)
	{
		outputMessage("COMPLETE: ", stcfList[currentSTJFJob].getName());
		addToEntry(stcfList[currentSTJFJob].getName(), outputArray, 2);
		stcfList.erase(stcfList.begin());
		stcfAmountOfJobsDone++;

		stcfAJobIsRunning = false;

		//Reset the SJF job time seeing as a new job has started
		stcfJobTime = 0;
	}

	else
	{
		//Output the current time and the SJF job being run
		addToEntry(stcfList[0].getName(), outputArray, 2);
		stcfAJobIsRunning = true;
	}
}

void sortSTJFJobsList(std::vector<Job>& stcfList)
{
	for (unsigned int i = 0; i < stcfList.size(); i++)
	{
		for (unsigned int testJobPosition = i + 1; testJobPosition < stcfList.size(); testJobPosition++)
		{
			if (stcfList[i].getDuration() > stcfList[testJobPosition].getDuration())
			{
				//Switch the two jobs
				//Make a copy of the first one
				Job temp = stcfList[i];

				//Move the second one into the first one
				stcfList[i] = stcfList[testJobPosition];

				//Replace the second one with the first one from the temp job
				stcfList[testJobPosition] = temp;
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

void addToEntry(std::string jobName, std::vector<std::string>& outputArray, int pos)
{
	outputArray[pos] = jobName;
}

void outputArrayMethod(std::vector<std::string>& outputArray, int& currentTime)
{
	std::cout << currentTime << "			" << outputArray[0] << "		" << outputArray[1] <<
		"		" << outputArray[2] << "		" << outputArray[3] << "		" <<
		outputArray[4] << std::endl;
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