#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  
  void Pid(int numPID);
  void User(int numPID);
  void Command(int numPID);
  void CpuUtilization(int numPID);
  void Ram(int numPID);
  void UpTime(int numPID);
  // TODO: Declare any necessary private members
 private:
 int pid;
 std::string user;
 std::string command;
 float cpuutilization;
 std::string ram;
 long int uptime;
};

#endif