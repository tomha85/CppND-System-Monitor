#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include<cmath>
#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

int Process::Pid() { return pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return cpuutilization; }

// TODO: Return the command that generated this process
string Process::Command() { return command; }

// TODO: Return this process's memory utilization
string Process::Ram() { return ram; }

// TODO: Return the user (name) that generated this process
string Process::User() { return user; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return uptime; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }
void Process::Pid(int numPID){pid=numPID;}
void Process::User(int numPID)
{
   string line;
   string key;
   string value;
   string UID;
   std::ifstream filestream(LinuxParser::kProcDirectory+to_string(numPID)+'/'+LinuxParser::kStatusFilename);
   if(filestream.is_open())
   {
       while(std::getline(filestream,line))
       {
           std::istringstream linestream(line);
           while(linestream>>key>>value)
           {
               if(key=="Uid:")
               {
                   UID=value;
               }
           }
       }
   }
   std::ifstream filestream2(LinuxParser::kPasswordPath);
   if(filestream2.is_open())
   {
       while(std::getline(filestream2,line))
       {
            std::replace(line.begin(),line.end(),':',' ');
            std::replace(line.begin(),line.end(),'x',' ');
            std::istringstream linestream2(line);
       
            while(linestream2>>value>>key)
            {
                if(key==UID)
                {
                    user=value;
                }
            }
        }
    }
}
void Process::Command(int numPID)
{
    string line;
    string key;
    string value;
    std::ifstream filestream(LinuxParser::kProcDirectory+to_string(numPID)+'/'+LinuxParser::kCmdlineFilename);
    if(filestream.is_open())
    {
        while(std::getline(filestream,line))
        {
            std::istringstream linestream(line);
            command=line;
        }
    }
}
void Process::Ram(int numPID)
{
    string line;
    string key;
    string value;
    float Ramk;
    int Ramm;
    std::ifstream filestream(LinuxParser::kProcDirectory+ to_string(numPID)+'/'+LinuxParser::kStatusFilename);
    if(filestream.is_open())
    {
        while(std::getline(filestream,line))
        {
            std::istringstream linestream(line);
            while(linestream>>key>>value)
            {
                if(key=="VmSize:")
                {
                    Ramk=std::stof(value);
                    Ramm=floor(Ramk/1024);
                    ram=to_string(Ramm);
                }
            }
        }
    }
}
#define HERTZ sysconf(_SC_CLK_TCK)
void Process::CpuUtilization(int numPID)
{
    string line,uptime;
    float utime,stime,cutime,cstime,starttime;
    string tmp;
    vector<string>pos(22);
    float fuptime;
    string value;
    std::ifstream filestream(LinuxParser::kProcDirectory+LinuxParser::kUptimeFilename);
    if(filestream.is_open())
    {
        while(std::getline(filestream,line))
        {
            std::istringstream linestream(line);
            while(linestream>>uptime>>value)
            {
                fuptime=stof(uptime);
            }
        }
    }
    std::ifstream filestream2(LinuxParser::kProcDirectory+to_string(numPID)+'/'+LinuxParser::kStatFilename);
    if(filestream2.is_open())
    {
        while(std::getline(filestream2,line))
        {
            std::istringstream linestream2(line);
            for(int i=0;i<22;i++)
            {
                linestream2>>tmp;
                pos[i]=tmp;
            }
            utime=stof(pos[13]);
            stime=stof(pos[14]);
            cutime=stof(pos[15]);
            cstime=stof(pos[16]);
            starttime=stof(pos[21]);
            cpuutilization=((utime+stime+cutime+cstime)/HERTZ)/(fuptime-(starttime/HERTZ));

        }
    }
}
void Process::UpTime(int numPID)
{
    string line;
    float starttime;
    string tmp;
    vector<string> statpos(22);
    string value;
    std::ifstream filestream(LinuxParser::kProcDirectory+to_string(numPID)+
                                '/'+LinuxParser::kStatFilename);
    if(filestream.is_open())
    {
        while(std::getline(filestream,line))
        {
            std::istringstream linestream(line);
            for(int i=0;i<22;i++)
            {
                linestream >>tmp;
                statpos[i]=tmp;
            }
            starttime=stof(statpos[21]);
            uptime=starttime/HERTZ;
        }
    }
}