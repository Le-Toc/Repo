#pragma once
#include <string>

class Job
{
public:
  Job(std::string name, int arrivalTime, int duration);
  Job();
  ~Job();

  //Properities
  int getArrivalTime();
  int getDuration();
  void setDuration(int duration);
  std::string getName();

  //Methods
  void print();

private:
  std::string name;
  int arrivalTime, duration;
};
