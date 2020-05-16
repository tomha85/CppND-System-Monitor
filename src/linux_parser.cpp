#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include<iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel,version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel>>version;;
  }
  stream.close();
  return version;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}
float LinuxParser::MemoryUtilization()
{
  string key,value;
  string total,available;
  string line;
  std::ifstream filestream(kProcDirectory+kMeminfoFilename);
  if(filestream.is_open())
  {
    while(std::getline(filestream,line))
    {
      std::istringstream linestream(line);
      linestream>>key>>value;
      if(key=="MemTotal:")
      {
        total=value;
        continue;
      }
      if(key=="MemAvailable:")
      {
        available=value;
        break;
      }
    }
  }
  return 1.0-stof(available)/stof(total);
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() 
{
  string line;
  string Uptime1;
  string Uptime2;
  long lnUptime;
  std::ifstream filestream(kProcDirectory+kUptimeFilename);
  if(filestream.is_open())
  {
    while(std::getline(filestream,line))
    {
      std::istringstream linestream(line);
      while(linestream>>Uptime1>>Uptime2)
      {
        lnUptime=stol(Uptime1);
        return lnUptime;
      }
    }
  
  }
  return lnUptime; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() 
{ 
  
  return UpTime()*sysconf(_SC_CLK_TCK); 
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid)
{
  string line,token;
  vector<string> values;
  std::ifstream filestream(LinuxParser::kProcDirectory +to_string(pid)+LinuxParser::kStatFilename);
  if(filestream.is_open())
  {
    std::getline(filestream,line);
    std::istringstream linestream(line);
    while(linestream>>token)
    {
    values.push_back(token);
    }
  }
  long jiffies{0};
  if(values.size()>21)
  {
    long user=stol(values[13]);
    long kernal=stol(values[14]);
    long children_user=stol(values[15]);
    long children_kernal=stol(values[16]);
    jiffies=user+kernal+children_user+children_kernal;
  }
  return jiffies;
}


// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() 
{ 
  vector<string> time=CpuUtilization();
  return(stol(time[CPUStates::kUser_])+stol(time[CPUStates::kNice_])+
        stol(time[CPUStates::kSystem_])+stol(time[CPUStates::kIRQ_])+
        stol(time[CPUStates::kSoftIRQ_])+stol(time[CPUStates::kSteal_])+
        stol(time[CPUStates::kGuest_])+stol(time[CPUStates::kGuestNice_]));
  
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() 
{ 
  vector<string>time =CpuUtilization();
  return(stol(time[CPUStates::kIdle_])+stol(time[CPUStates::kIOwait_]));
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() 
{ 
  string line;
  string key;
  string value;
  int num;
  std::ifstream filestream(kProcDirectory+ kStatFilename);
  if(filestream.is_open())
  {
    while(std::getline(filestream,line))
    {
      std::istringstream linestream(line);
      while(linestream>>key>>value)
      {
        if(key=="processes")
        {
          num=std::stoi(value);
          return num;
        }
      }
    }
  }
  return num; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() 
{ 
  string line;
  string key;
  string value;
  int nump;
  std::ifstream filestream(kProcDirectory+ kStatFilename);
  if(filestream.is_open())
  {
    while(std::getline(filestream,line))
    {
      std::istringstream linestream(line);
      while(linestream>>key>>value)
      {
        if(key=="procs_running")
        {
          nump=std::stoi(value);
          return nump;
        }
      }
    }
  }
  return nump; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }