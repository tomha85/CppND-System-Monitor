#include "processor.h"
#include <string>
#include "linux_parser.h"
#include<vector>
using std::vector;
using std::stof;
using std::string;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() 
{
    string line,key,user,nice,system,idle,iowait,irq,softirq,steal,guest,guest_nice;
    float total_time;
    std::ifstream filestream(LinuxParser::kProcDirectory+LinuxParser::kStatFilename);
    if(filestream.is_open())
    {
        while(std::getline(filestream,line))
        {
            std::istringstream linestream(line);
            while(linestream>>key>>user>>nice>>system>>idle>>iowait>>irq>>softirq>>steal>>guest>>guest_nice)
            {
                if(key=="cpu")
                {
                    total_time=stof(user)+stod(system)+stof(idle)+stof(iowait)+stof(softirq)+stof(irq)+stof(steal)+stof(guest)+stof(guest_nice);
                    return(total_time-stof(idle))/total_time;
                }
            }
        }
    }    
    
    return 0.0; 
}