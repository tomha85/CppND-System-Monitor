#include <string>
#include <math.h>
#include<iostream>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds)
{
    long const  Sec2Hour=3600;
    long const Sec2Min=60;
    long hour=floor(seconds/Sec2Hour);
    long tmpseconds=seconds-hour*Sec2Hour;
    long min=floor(tmpseconds/Sec2Min);
    long second=tmpseconds-min*Sec2Min;
    string Hour;
    string Min;
    string Second;
    if(hour<10){Hour='0'+to_string(hour);}
    else{Hour=to_string(hour);}
    if(min<10){Min='0'+to_string(min);}
    else{Min=to_string(min);}
    if(second<10){Second='0'+to_string(second);}
    else{Second=to_string(second);}

    return string(Hour+":"+Min+":"+Second);

}