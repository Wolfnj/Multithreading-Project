//
// Created by Nwolf on 1/28/2020.
//

#include "Log.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

/*
 * no-arg constructor
 */
Log::Log() {
    this -> textFileString = "";
    this -> logFileString = "";
    this -> currentLog = "";
}



/*
 * Log Constructor
 *
 * textfile - inputted text file
 * logfile - log file, will hold "None" if not given
 */
Log::Log(string textfile, string logfile) {

    this -> textFileString = textfile;
    this -> logFileString = logfile;
    this -> currentLog = "";

}




/*
 * Log Constructor
 *

 * logfile - log file, will hold "None" if not given
 */
Log::Log(string logfile) {

    this -> textFileString = "";
    this -> logFileString = logfile;
    this -> currentLog = "";

}





void Log::setLogFileString(string log) {
    this -> logFileString = log;
}

void Log::setTextFileString(string text) {
    this -> textFileString = text;
}



/*
 * makeTimeAppendString()
 * will make the time appended string
 */
void Log::appendEntireTextFile() {

    string logfileString = "";
    string line = "";
    string logAsString;


    //ctime usage adapted from Programiz
    //Source: https://www.programiz.com/cpp-programming/library-function/ctime/ctime
    time_t curr_time = time(NULL);


    //Code Adapted from the example in the "Read a File" section on w3schools
    //Source: https://www.w3schools.com/cpp/cpp_files.asp
    ifstream textFile(this->textFileString);

    if (textFile.is_open())
    {

        // Use a while loop together with the getline() function to read the file line by line
        logAsString.append(ctime(&curr_time));
        logAsString.append("Begin\n");
        while (getline(textFile, line)) {
            // Output the text from the file
            curr_time = time(NULL);

            logAsString.append(ctime(&curr_time));
            logAsString.append(line + "\n");
        }
        logAsString.append(ctime(&curr_time));
        logAsString.append("End\n");

    }
    else{
        cout << "Couldn't find file \n";
        cout << "Required text input file " << this->textFileString << " does not exist \n";
        logAsString.append(ctime(&curr_time));
        logAsString.append("End\n");
    }


    // Close the file
    textFile.close();


    currentLog.append(logAsString);
}





/**
 * Write a single line to the log
 * Will put a Begin if nothing written to yet
 *
 * line - The line how want to write to the log
 */
void Log::writeLineToLog(string line) {

    time_t curr_time = time(NULL);

    if(!this->currentLog.compare(""))
    {
        currentLog.append(ctime(&curr_time));
        currentLog.append("Begin\n");
    }

    currentLog.append(ctime(&curr_time));
    currentLog.append(line+ "\n");


}






/*
 * Will make the log file from the time append string in the previous method
 *
 * return - if no log file specified, then log return as "log" in a file
 *        - if log file is specified, then append to the log file given
 */
void Log::makeLogFile() {
    //Code Adapted from"Create and Write To a File" section on w3schoolscd
    //Source: https://www.w3schools.com/cpp/cpp_files.asp
    string logAsString = this->currentLog;

    if (!this->logFileString.compare("None")) {
        //no Log given

        writeLineToLog("END");

        ofstream LogFile("log");
        //return log file as "log"
        LogFile << logAsString;
        // Close the file
        LogFile.close();
    } else {


        writeLineToLog("END");


        ofstream fout;  // Create Object of Ofstream
        ifstream fin;
        fin.open(this->logFileString);
        fout.open(this->logFileString, ios::app); // Append mode
        if (fin.is_open()) {
            fout << logAsString + "\n"; // Writing data to file
        }
        else{
            cout << "Log file cannot be opened. \n" ;
        }
        fin.close();
        fout.close(); // Closing the file

    }


}
