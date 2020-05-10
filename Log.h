//
// Created by Nwolf on 2/17/2020.
//
#include <string>

#ifndef HW2_LOG_H
#define HW2_LOG_H

#endif //HW2_LOG_H
using namespace std;


class Log {
private:


    string textFileString;      //holds textfile name
    string logFileString;       //hold  logfile name

    string currentLog;          //holds accumulated append strings
                                //from each line logged


public:
    //No Arg Constructor
    Log();

    //Parameterized constructor
    Log(string,string);

    //Just using logfile
    Log(string logfile);

    //Setter for Log File
    void setLogFileString(string log);

    //Setter for text File
    void setTextFileString(string text);



    //Appends entire text file with logs to currentLogString
    void appendEntireTextFile();


    //Writes a single line to a log
    void writeLineToLog(string line);



    //writes out timeappendstring to log file
    void makeLogFile();



};


