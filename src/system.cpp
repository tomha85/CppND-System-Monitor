#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include<iostream>
#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"
#include <algorithm>

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }
bool Comparecpu(Process a,Process b)
{
    return a.CpuUtilization()>b.CpuUtilization();
}
// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() 
{ 
    int PID;
    vector<int>vecPID=LinuxParser::Pids();
    int nump=vecPID.size();
    vector<Process> tmp(nump);
    processes_=tmp;
    for(int i=0;i<nump;i++)
    {
        PID=vecPID[i];
        processes_[i].Pid(PID);
        processes_[i].User(PID);
        processes_[i].Command(PID);
        processes_[i].Ram(PID);
        processes_[i].CpuUtilization(PID);
        processes_[i].UpTime(PID);

    }
    sort(processes_.begin(),processes_.end(),Comparecpu);
    return processes_; 
}

std::string System::Kernel()
{
    std::string s=LinuxParser::Kernel();
    return s;
}


// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }