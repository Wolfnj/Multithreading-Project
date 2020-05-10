#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <locale>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <iostream>
#include "Log.h"
#include <iostream>
#include <algorithm>
#include <csignal>
#include <semaphore.h>
#include "Rabbit.h"
#include "Knight.h"
#include "SafeQueue.h"
#include <queue>

using namespace std;

/**
 * Messages for logging info
 */
struct msg {
    char str[64];
};




/**
 * Messages for attacking info
 */
struct attackMsg{
    int from;   //Who sent this 0 == Rabbit, 1 == first knight, etc.
    int type;   //0 == bite, 1 ==quick, 2 == throat, 3 == first knight
    int damage; //How much damage caused
};


attackMsg* createAttackMsg(){
    attackMsg *result = new attackMsg;
    return result;
}



void sigtermHandler(int signum) {
    fflush(stdout);
    exit(143);
}




//Reference
//https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
}
// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}
// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}
// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}
// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}
// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}


/**
 * Checks if the user entered valid sqirchs
 * @param argc -  number of args
 * @param argv - array of the args
 * @param logMessageWrite - string to would log message
 * @param logPipe - pipe to send message to log
 */
void checkingValidSwitches(int argc, char *const *argv, string &logMessageWrite, const int *logPipe) {
    for (int i = 0; i < (argc - 1); i++) {
        msg msg;
        //Check if valid switches are entered
        if (!(strcmp(argv[i + 1], "-r") || strcmp(argv[i + 1], "-k") || strcmp(argv[i + 1], "-l"))) {
            logMessageWrite = "Incorrect switch given. Only -r, -k, or -l";
            memset(msg.str,0,64);
            strcpy(msg.str,logMessageWrite.c_str());
            write(logPipe[1], (char *) &msg, sizeof(msg));
        }

    }

}







/**
 * Checks for valid input orders. Makes sure the user entered valid info
 * @param argc -  number of args
 * @param argv - array of the args
 * @param knightFileName - name of the knight file entered
 * @param logFileName - name of log file entered
 * @param logPipe - log pipe to send messages to log process
 * @param logMessageWrite - message to send to log file
 * @param rabbitFileName - name of rabbit
 */
void
checkingValidInputOrders(int argc, char *const *argv, string &knightFileName, string &logFileName, const int *logPipe,
                         string &logMessageWrite, string &rabbitFileName) {

    msg msg;

    if (argc == 3) {
        //Only Rabbit File entered
        if (strcmp(argv[1], "-r") == 0) {
            string s(argv[2]);
            rabbitFileName = argv[2];
            knightFileName = "None";
            logFileName = "None";


            //           logFileName = "DEFAULT KNIGHT will be used";

            memset(msg.str,0,64);
            strcpy(msg.str, logFileName.c_str());
            write(logPipe[1], (char *) &msg, sizeof(msg));

            memset(msg.str,0,64);
            strcpy(msg.str, "DEFAULT KNIGHT will be used");
            write(logPipe[1], (char *) &msg, sizeof(msg));


        } else {


            memset(msg.str,0,64);
            strcpy(msg.str, "None");
            write(logPipe[1], (char *) &msg, sizeof(msg));


            logMessageWrite = "3 argument entered. -r not found";

            memset(msg.str,0,64);
            strcpy(msg.str,logMessageWrite.c_str());
            write(logPipe[1], (char *) &msg, sizeof(msg));


            memset(msg.str,0,64);
            strcpy(msg.str, "END");
            write(logPipe[1], (char *) &msg, sizeof(msg));



        }

    }


    else if (argc == 5) {

        if (strcmp(argv[1], "-r") == 0 && strcmp(argv[3], "-k") == 0) {
            //cout << "\n  Rabbit then knight" << endl;
            rabbitFileName = argv[2];
            knightFileName = argv[4];
            logFileName = "None";

            memset(msg.str,0,64);
            strcpy(msg.str,logFileName.c_str());
            write(logPipe[1], (char *) &msg, sizeof(msg));


        } else if (strcmp(argv[1], "-r") == 0 && strcmp(argv[3], "-l") == 0) {
            //cout << "\n  knight then log" << endl;
            rabbitFileName = argv[2];
            knightFileName = "None";
            logFileName = argv[4];

            memset(msg.str,0,64);
            strcpy(msg.str,logFileName.c_str());
            write(logPipe[1], (char *) &msg, sizeof(msg));

        } else if (strcmp(argv[1], "-k") == 0 && strcmp(argv[3], "-r") == 0) {
            //cout << "\n  knight then Rabbit" << endl;
            rabbitFileName = argv[4];
            knightFileName = argv[2];
            logFileName = "None";

            memset(msg.str,0,64);
            strcpy(msg.str,logFileName.c_str());
            write(logPipe[1], (char *) &msg, sizeof(msg));
        } else if (strcmp(argv[1], "-l") == 0 && strcmp(argv[3], "-r") == 0) {
            //cout << "\n  Log then Rabbit" << endl;
            rabbitFileName = argv[4];
            knightFileName = "None";
            logFileName = argv[2];

            memset(msg.str,0,64);
            strcpy(msg.str,logFileName.c_str());
            write(logPipe[1], (char *) &msg, sizeof(msg));
        }


        else{


            memset(msg.str,0,64);
            strcpy(msg.str, "None");
            write(logPipe[1], (char *) &msg, sizeof(msg));


            logMessageWrite = "5 argument entered. Invalid Switches";
            memset(msg.str,0,64);
            strcpy(msg.str,logMessageWrite.c_str());
            write(logPipe[1], (char *) &msg, sizeof(msg));


            memset(msg.str,0,64);
            strcpy(msg.str, "END");
            write(logPipe[1], (char *) &msg, sizeof(msg));


        }
    }



    else if (argc == 7) {

        if (strcmp(argv[1], "-r") == 0) {

            if (strcmp(argv[3], "-k") == 0) {
                // cout << "\n  Rabbit,knight,Log" << endl;
                rabbitFileName = argv[2];
                knightFileName = argv[4];
                logFileName = argv[6];

                memset(msg.str,0,64);
                strcpy(msg.str,logFileName.c_str());
                write(logPipe[1], (char *) &msg, sizeof(msg));

            } else {
                //cout << "\n  Rabbit,Log,knight" << endl;
                rabbitFileName = argv[2];
                knightFileName = argv[6];
                logFileName = argv[4];

                memset(msg.str,0,64);
                strcpy(msg.str,logFileName.c_str());
                write(logPipe[1], (char *) &msg, sizeof(msg));

            }
        } else if (strcmp(argv[3], "-r") == 0) {
            if (strcmp(argv[1], "-k") == 0) {
                //cout << "\n  knight,Rabbit,Log" << endl;
                rabbitFileName = argv[4];
                knightFileName = argv[2];
                logFileName = argv[6];

                memset(msg.str,0,64);
                strcpy(msg.str,logFileName.c_str());
                write(logPipe[1], (char *) &msg, sizeof(msg));


            } else {
                //cout << "\n  Log,Rabbit,knight" << endl;
                rabbitFileName = argv[4];
                knightFileName = argv[6];
                logFileName = argv[2];

                memset(msg.str,0,64);
                strcpy(msg.str,logFileName.c_str());
                write(logPipe[1], (char *) &msg, sizeof(msg));


            }
        } else if (strcmp(argv[5], "-r") == 0) {
            if (strcmp(argv[1], "-k") == 0) {
                //cout << "\n  knight,Log,Rabbit" << endl;
                rabbitFileName = argv[6];
                knightFileName = argv[2];
                logFileName = argv[4];

                memset(msg.str,0,64);
                strcpy(msg.str,logFileName.c_str());
                write(logPipe[1], (char *) &msg, sizeof(msg));


            } else if (strcmp(argv[1], "-l") == 0){
                rabbitFileName = argv[6];
                knightFileName = argv[4];
                logFileName = argv[2];

                memset(msg.str,0,64);
                strcpy(msg.str,logFileName.c_str());
                write(logPipe[1], (char *) &msg, sizeof(msg));
            }
            else{


                memset(msg.str,0,64);
                strcpy(msg.str, "None");
                write(logPipe[1], (char *) &msg, sizeof(msg));


                logMessageWrite = "7 argument entered. Invalid Switches";
                memset(msg.str,0,64);
                strcpy(msg.str,logMessageWrite.c_str());
                write(logPipe[1], (char *) &msg, sizeof(msg));


                memset(msg.str,0,64);
                strcpy(msg.str, "END");
                write(logPipe[1], (char *) &msg, sizeof(msg));

            }
        }

    }


    else {

        logMessageWrite = "Error when reading in input files";
        memset(msg.str,0,64);
        strcpy(msg.str,logMessageWrite.c_str());
        write(logPipe[1], (char *) &msg, sizeof(msg));
    }
}





/**
 * Reads in the rabbit file. Will check for errors and log them.
 * @param logMessageWrite - message to send to log file
 * @param rabbitFileName - name of rabbit file
 * @param line - read each line from the file
 * @param delimiter - ':' to separate input lines
 * @param token - part of string to put in setter of rabbit
 * @param type - what type of setter element
 * @param rabbit - rabbit class to create from rabiit file info
 * @param logPipe -pipe to send logs to log process
 */
void readInRabbitFile(string &logMessageWrite, const string &rabbitFileName, string &line, const string &delimiter,
                      string &token, string &type, Rabbit &rabbit, const int *logPipe) {


    ifstream rabbitFile(rabbitFileName);


    if(rabbitFileName.compare("rabbit") == 0){
        //cout << "Good" << endl;
    }
    else{
        //cout << "Bad" << endl;

    }

    msg msg;

    //Reading in Rabbit File
    if (rabbitFile.is_open()) {
        while (getline(rabbitFile, line)) {
            // Output the text from the file



            trim(line);

            memset(msg.str,0,64);
            strcpy(msg.str, line.c_str());

            write(logPipe[1],(char*)&msg,sizeof(msg));






            token = line.substr((line.find(delimiter) + 1), line.length());
            type = line.substr(0, line.find(delimiter));


            if(stoi(token)<0){
                memset(msg.str,0,64);
                strcpy(msg.str, "Negative Value entered");
                write(logPipe[1],(char*)&msg,sizeof(msg));
                memset(msg.str,0,64);
                strcpy(msg.str, "END");
                write(logPipe[1],(char*)&msg,sizeof(msg));
                exit(0);
            }



            if (type.compare("hp") == 0) {
                rabbit.setRabbitHp(stoi(token));
                if(stoi(token)<25 || stoi(token)>100 ){
                    memset(msg.str,0,64);
                    strcpy(msg.str, "Rabbit HP must be [25,100]");
                    write(logPipe[1],(char*)&msg,sizeof(msg));
                    memset(msg.str,0,64);
                    strcpy(msg.str, "END");
                    write(logPipe[1],(char*)&msg,sizeof(msg));
                    exit(0);
                }


            } else if (type.compare("rate") == 0) {
                rabbit.setRabbitAttackRate(stoi(token));

                if(stoi(token)<3 || stoi(token)>10 ){
                    memset(msg.str,0,64);
                    strcpy(msg.str, "Rabbit Attack Rate must be [3,10]");
                    write(logPipe[1],(char*)&msg,sizeof(msg));
                    memset(msg.str,0,64);
                    strcpy(msg.str, "END");
                    write(logPipe[1],(char*)&msg,sizeof(msg));
                    exit(0);
                }


            } else if (type.compare("bite") == 0) {
                rabbit.setRabbitBite(stoi(token));

                if(stoi(token)<60 || stoi(token)>75 ){
                    memset(msg.str,0,64);
                    strcpy(msg.str, "Rabbit Bite must be [60,75]");
                    write(logPipe[1],(char*)&msg,sizeof(msg));
                    memset(msg.str,0,64);
                    strcpy(msg.str, "END");
                    write(logPipe[1],(char*)&msg,sizeof(msg));
                    exit(0);
                }

            } else if (type.compare("quick") == 0) {
                rabbit.setRabbitQuick(stoi(token));

                if(stoi(token)<10 || stoi(token)>20 ){
                    memset(msg.str,0,64);
                    strcpy(msg.str, "Rabbit Quick must be [10,20]");
                    write(logPipe[1],(char*)&msg,sizeof(msg));
                    memset(msg.str,0,64);
                    strcpy(msg.str, "END");
                    write(logPipe[1],(char*)&msg,sizeof(msg));
                    exit(0);
                }


            } else if (type.compare("throat") == 0) {
                rabbit.setRabbitThroat(stoi(token));


                if(stoi(token)<5 || stoi(token)>20 ){
                    memset(msg.str,0,64);
                    strcpy(msg.str, "Rabbit Throat must be [5,20]");
                    write(logPipe[1],(char*)&msg,sizeof(msg));
                    memset(msg.str,0,64);
                    strcpy(msg.str, "END");
                    write(logPipe[1],(char*)&msg,sizeof(msg));
                    exit(0);
                }

            } else if (type.compare("weak") == 0) {
                rabbit.setRabbitWeak(stoi(token));

                if(stoi(token)<1 || stoi(token)>9 ){
                    memset(msg.str,0,64);
                    strcpy(msg.str, "Rabbit Weak must be [1,9]");
                    write(logPipe[1],(char*)&msg,sizeof(msg));
                    memset(msg.str,0,64);
                    strcpy(msg.str, "END");
                    write(logPipe[1],(char*)&msg,sizeof(msg));
                    exit(0);
                }


            } else if (type.compare("strong") == 0) {
                rabbit.setRabbitStrong(stoi(token));

                if(stoi(token)<30 || stoi(token)>40){
                    memset(msg.str,0,64);
                    strcpy(msg.str, "Rabbit Strong must be [30,40]");
                    write(logPipe[1],(char*)&msg,sizeof(msg));
                    memset(msg.str,0,64);
                    strcpy(msg.str, "END");
                    write(logPipe[1],(char*)&msg,sizeof(msg));
                    exit(0);
                }

            } else if (type.compare("evade") == 0) {
                rabbit.setRabbitEvasion(stoi(token));

                if(stoi(token)<5 || stoi(token)>95 ){
                    memset(msg.str,0,64);
                    strcpy(msg.str, "Rabbit Evade must be [5,95]");
                    write(logPipe[1],(char*)&msg,sizeof(msg));
                    memset(msg.str,0,64);
                    strcpy(msg.str, "END");
                    write(logPipe[1],(char*)&msg,sizeof(msg));
                    exit(0);
                }



            } else {




                memset(msg.str,0,64);
                strcpy(msg.str, "Error when reading in Rabbit Files");
                write(logPipe[1],(char*)&msg,sizeof(msg));
            }

        }
    }
    else {


        memset(msg.str,0,64);
        strcpy(msg.str, "ERROR couldn't find the rabbit file");
        write(logPipe[1],(char*)&msg,sizeof(msg));

    }
}



/**
 *Reads in the knight file
 * @param logMessageWrite - mesage to send to the log process
 * @param knightFileName - name of knight file
 * @param line - read each line from the file
 * @param delimiter - ':' to separate input lines
 * @param token - part of string to put in setter of knight
 * @param type - what type of setter element
 * @param loopcounter - counts each knight info
 * @param knightIndexArray - index for each knight in the knights array
 * @param NumOfKnights - holds how many knights there are
 * @param knights - knights array
 * @param logPipe -pipe to send logs to log process
 * @return the pointer to the knights array that was filled up
 */
Knight* readInKnightFiles(string &logMessageWrite, string knightFileName, string &line, const string &delimiter,
                          string &token, string &type, int loopcounter, int knightIndexArray, int &NumOfKnights,
                          Knight * knights, const int *logPipe) {


    msg msg;

    loopcounter = 1;
    knightIndexArray = 0;
    if (knightFileName.compare("None") == 0) {
        //Make the default Knight
//        logMessageWrite = "DEFAULT KNIGHT will be used";

        NumOfKnights = 1;


        knights = new Knight[NumOfKnights];

        Knight dKnight("Default Knight", 100, 10, 20, 3);

        knights[0].setKnightName("Default Knight");
        knights[0].setKnightHp(100);
        knights[0].setKnightBravery(10);
        knights[0].setKnightAttackRate(20);
        knights[0].setKnightDamage(3);

//        memset(msg.str,0,64);
//        strcpy(msg.str, logMessageWrite.c_str());
//        write(logPipe[1], (char *) &msg, sizeof(msg));
    }
        //HANDLE Knight file entered
    else {
        ifstream knightFile(knightFileName);


        if (knightFile.is_open()) {


            try {

                while (getline(knightFile, line)) {

                    if (line.find(delimiter) != std::string::npos) {
                        // : found in line

                        trim(line);

                        //cout << line << endl;


                        memset(msg.str, 0, 64);
                        strcpy(msg.str, line.c_str());
                        write(logPipe[1], (char *) &msg, sizeof(msg));


                        token = line.substr((line.find(delimiter) + 1), line.length());
                        type = line.substr(0, line.find(delimiter));


                        if (type.compare("count") == 0) {
                            NumOfKnights = stoi(token);



                            if(stoi(token)<1 || stoi(token)>8 ){
                                memset(msg.str,0,64);
                                strcpy(msg.str, "Knight count must be [1,8]");
                                write(logPipe[1],(char*)&msg,sizeof(msg));
                                memset(msg.str,0,64);
                                strcpy(msg.str, "END");
                                write(logPipe[1],(char*)&msg,sizeof(msg));
                                exit(0);
                            }



                            //HOLDS ALL KNIGHTS FROM INPUT
                            knights = new Knight[NumOfKnights];
                        } else {
                            if (type.compare("count") == 0) {
                                //do nothing
                                if(stoi(token)<1 || stoi(token)>8 ){
                                    memset(msg.str,0,64);
                                    strcpy(msg.str, "Knight count must be [1,8]");
                                    write(logPipe[1],(char*)&msg,sizeof(msg));
                                    memset(msg.str,0,64);
                                    strcpy(msg.str, "END");
                                    write(logPipe[1],(char*)&msg,sizeof(msg));
                                    exit(0);
                                }
                            } else if (type.compare("name") == 0) {


                                if(token.length()<2 || token.length()>50){
                                    memset(msg.str,0,64);
                                    strcpy(msg.str, "Knight name must be [2,50] characters");
                                    write(logPipe[1],(char*)&msg,sizeof(msg));
                                    memset(msg.str,0,64);
                                    strcpy(msg.str, "END");
                                    write(logPipe[1],(char*)&msg,sizeof(msg));
                                    exit(0);
                                }

                                knights->incNumKnight();
                                loopcounter = 1;
                                knights[knightIndexArray].setKnightName(token);

                            } else if (type.compare("hp") == 0) {


                                if(stoi(token)<10 || stoi(token)>40 ){
                                    memset(msg.str,0,64);
                                    strcpy(msg.str, "Knight HP must be [10,40]");
                                    write(logPipe[1],(char*)&msg,sizeof(msg));
                                    memset(msg.str,0,64);
                                    strcpy(msg.str, "END");
                                    write(logPipe[1],(char*)&msg,sizeof(msg));
                                    exit(0);
                                }


                                knights[knightIndexArray].setKnightHp(stoi(token));
                                loopcounter += 1;
                            } else if (type.compare("bravery") == 0) {



                                if(stoi(token)<0 || stoi(token)>=knights[knightIndexArray].getKnightHp() ){
                                    memset(msg.str,0,64);
                                    strcpy(msg.str, "Knight Bravery must be above 0 and below knight hp");
                                    write(logPipe[1],(char*)&msg,sizeof(msg));
                                    memset(msg.str,0,64);
                                    strcpy(msg.str, "END");
                                    write(logPipe[1],(char*)&msg,sizeof(msg));
                                    exit(0);
                                }


                                knights[knightIndexArray].setKnightBravery(stoi(token));
                                loopcounter += 1;

                            } else if (type.compare("rate") == 0) {


                                if(stoi(token)<10 || stoi(token)>50 ){
                                    memset(msg.str,0,64);
                                    strcpy(msg.str, "Knight rate must be [10,50]");
                                    write(logPipe[1],(char*)&msg,sizeof(msg));
                                    memset(msg.str,0,64);
                                    strcpy(msg.str, "END");
                                    write(logPipe[1],(char*)&msg,sizeof(msg));
                                    exit(0);
                                }




                                knights[knightIndexArray].setKnightAttackRate(stoi(token));
                                loopcounter += 1;
                            } else if (type.compare("damage") == 0) {


                                if(stoi(token)<1 || stoi(token)>8 ){
                                    memset(msg.str,0,64);
                                    strcpy(msg.str, "Knight damage must be [1,8]");
                                    write(logPipe[1],(char*)&msg,sizeof(msg));
                                    memset(msg.str,0,64);
                                    strcpy(msg.str, "END");
                                    write(logPipe[1],(char*)&msg,sizeof(msg));
                                    exit(0);
                                }


                                knights[knightIndexArray].setKnightDamage(stoi(token));
                                loopcounter += 1;

                            }


                            if (loopcounter == 5) {
                                knightIndexArray += 1;
                                loopcounter = 1;
                            }
                        }


                    }


                }


            }catch(int error){

                memset(msg.str, 0, 64);
                strcpy(msg.str, "ERROR read in Knight file -- Not correct format");
                write(logPipe[1], (char *) &msg, sizeof(msg));

                memset(msg.str, 0, 64);
                strcpy(msg.str, "END");
                write(logPipe[1], (char *) &msg, sizeof(msg));


            }




        }


    }


    return knights;

}










/**
 * Logging child function which will keep on reading from all processes until "END" is sent
 * @param msg - msg struct which holds the log message passed through the pipes
 * @param logPipe - log pipe to send and receive from other processes
 */
void LoggingChildFunction(msg &msg, const int *logPipe) {
    Log lo("None");

    read(logPipe[0],(char*)&msg,sizeof(msg));


    string s;

    s = msg.str;

    lo.setLogFileString(s);


    if(strcmp(msg.str,"None") != 0){
        s = msg.str;
        lo.setLogFileString(s);
    }


    lo.writeLineToLog(s);
    // cout << msg.str << endl;

    while(strcmp("END",msg.str) != 0){
        // cout << msg.str << endl;
        read(logPipe[0],(char*)&msg,sizeof(msg));
        s = msg.str;
        trim(s);
        lo.writeLineToLog(s);

    }

    lo.makeLogFile();
}


//Globals

SafeQueue<attackMsg> rabbitSafeQueue;
SafeQueue<attackMsg>  *knightSafeQueue;

int indexCounterForKnightThreads=0;





Rabbit rabbit;
Knight dKnight("Default Knight", 100, 10, 20, 3);
int NumOfKnights = 0;
//Initialize Knights in memory will set values to it later.
Knight *knights;

int logPipe[2];








struct sharedThreadStruct {
    Knight *knights;
    Rabbit rab;
    int knightNum;
};



/**
 * Rabbit Thread
 * @param arg
 * @return
 */
void* rabbitAttackThread(void * arg) {
    bool rabbitAlive = true;
    bool rabbitEvade = true;
    string rabbitEvadeStr = "";
    string logMessage;

    int knightsAlive = NumOfKnights;

    int randomNum = 0;

    int randomKnightAttack = 0;
    int backUpKnightAttack = 0;

    bool *knightsFighting;
    knightsFighting = new bool[NumOfKnights];

    for(int i=0; i<NumOfKnights; i++ ){
        knightsFighting[i] = true;
    }


    msg msg; //Message for logging


    //while
    while (rabbitAlive) {

        //cout<< "In Rabbit thread" << endl;

        attackMsg receivedAttack={};
        attackMsg sentAttack={};


        //pthread_mutex_lock(&rabbitLock);
        //Add to Rabbit Queue

        if(NumOfKnights != 1){
            randomKnightAttack =( rand() % (NumOfKnights-1) )+ 0;
        }


        randomNum = rand() % 100 + 1;
        //cout << "Random Num: " << randomNum << endl;

        //cout << "ATTACK: " << knights[randomKnightAttack].getKnightName() << endl;






        /**
         * If the random knight chosen to attack is already died, we will have a backUpKnightIndex. The back up
         * will search through knightsFighting Array and find the first alive knight it can find. If the random knight
         * chosen is dead, then this backup will replace random knight attack
         */
        for(int i=0; i<NumOfKnights; i++){
            if(knightsFighting[i]==true){
                backUpKnightAttack = i;
                break;
            }
        }
        if(knightsFighting[randomKnightAttack]==false){
            randomKnightAttack = backUpKnightAttack;
        }





        if (randomNum <= rabbit.getRabbitBite()) {

            //Bite Attack
            sentAttack.from = 0;   //From the rabbit
            sentAttack.type = 0;   //Bite
            sentAttack.damage = rabbit.getRabbitWeak();
            //knightQueue.push(sentAttack);
            knightSafeQueue[randomKnightAttack].enqueue(sentAttack);

            //cout << "Bite!" << endl;

        } else if (randomNum > rabbit.getRabbitBite() &&
                   (randomNum <= (rabbit.getRabbitBite() + rabbit.getRabbitQuick()))) {

            sentAttack.from = 0;   //From the rabbit
            sentAttack.type = 1;   //Quick
            sentAttack.damage = rabbit.getRabbitWeak();
            //cout << "Quick!" << endl;
            for (int i = 0; i < NumOfKnights; i++) {
                if (knightsFighting[i]==true) {
                    //knightQueue.push(sentAttack);
                    knightSafeQueue[i].enqueue(sentAttack);
                }
            }
        } else {

            //Throat attack
            sentAttack.from = 0; // From the the rabbit
            sentAttack.type = 2; //Throat
            sentAttack.damage = rabbit.getRabbitStrong();
            //knightQueue.push(sentAttack);
            knightSafeQueue[randomKnightAttack].enqueue(sentAttack);
            //cout << "Throat!" << endl;
        }

        //Dequeue from the rabbit queue
        receivedAttack = rabbitSafeQueue.dequeue();

        //cout << "Rabbit Queue Result from: " << receivedAttack.from << endl;


        if(receivedAttack.type == -1){
            //Knight dieded or runded away

            knightsFighting[receivedAttack.from] = false;
            //cout << "Knight: " << knights[receivedAttack.from].getKnightName() << endl;


            knightsAlive = knightsAlive -1;

            if(knightsAlive <=0){
                //All Knights Died
                rabbitAlive = false; // Rabbit not died but need to stop the loop

                memset(msg.str,0,64);
                strcpy(msg.str,"Rabbit WINS!!!");
                write(logPipe[1], (char *) &msg, sizeof(msg));

            }

        }
        else{

            //Does Rabbit Evade?

            if (randomNum <= rabbit.getRabbitEvasion()) {
                //Rabbit Evade
                rabbitEvade = true;
                rabbitEvadeStr = "Evade<true>";

            } else {
                //Rabbit hit
                rabbitEvade = false;
                rabbitEvadeStr = "Evade<false>";
                rabbit.knightAttack(receivedAttack.damage);
            }

            logMessage = "Rabbit;" + rabbitEvadeStr + "Damage;" + to_string(receivedAttack.damage);


//        cout << "Rabbit HP: " << rabbit.getRabbitHp() << endl;
//        cout << "Knight HP: " << knights[0].getKnightHp() << endl;

            //Does Rabbit Die?
            if(rabbit.getRabbitHp()<=0){

                rabbitAlive = false;
                memset(msg.str,0,64);
                strcpy(msg.str,"Rabbit Killed");
                write(logPipe[1], (char *) &msg, sizeof(msg));

                sentAttack.type = -1; // From the the rabbit

                for(int i=0; i<NumOfKnights; i++){
                    if(knightsFighting[i]==true){
                        //knightQueue.push(sentAttack);
                        knightSafeQueue[i].enqueue(sentAttack);
                        //sem_post(&knightSem);
                        //knightSafeQueue.semaphorePost();
                    }
                }


            }else{
                memset(msg.str, 0, 64);
                strcpy(msg.str, logMessage.c_str());
                write(logPipe[1], (char *) &msg, sizeof(msg));
            }

        }
    } //while

    return NULL;
}

/**
 * Knight Thread
 * @param arg
 * @return
 */
void* knightAttackThread(void * arg) {
    int knightIndex = 0;
    bool knightAlive = true;

    msg msg;

    string logMessage = "";
    string type = "";



    knightIndex = indexCounterForKnightThreads++;


    //while
    while (knightAlive)
    {
        attackMsg receivedAttack={};
        attackMsg sentAttack={};


        // read from knight queue
        receivedAttack = knightSafeQueue[knightIndex].dequeue();


        if (receivedAttack.type == 0) {
            type = "Bite";
            knights[knightIndex].rabbitAttack(receivedAttack.damage);
            logMessage = knights[knightIndex].getKnightName() + ";" + type + ";" + to_string(receivedAttack.damage);
        } else if (receivedAttack.type == 1) {
            type = "Quick";

            knights[knightIndex].rabbitAttack(receivedAttack.damage);
            logMessage = "ALL KNIGHTS;" + type + ";" + to_string(receivedAttack.damage);


        } else if (receivedAttack.type == 2) {
            type = "Throat";
            knights[knightIndex].rabbitAttack(receivedAttack.damage);
            logMessage = knights[knightIndex].getKnightName() + ";" + type + ";" + to_string(receivedAttack.damage);

        } else if (receivedAttack.type == -1) {
            knightAlive = false; //Knight still alive, but we need to stop the loop
            logMessage = knights[knightIndex].getKnightName() + "; " "KILLED THE RABBIT";

        }


        //cout << logMessage << endl;

        memset(msg.str, 0, 64);
        strcpy(msg.str, logMessage.c_str());
        write(logPipe[1], (char *) &msg, sizeof(msg));


        if(knights[knightIndex].getKnightHp()>0)
        {
            // pthread_mutex_lock(&knightLock);
            //Add to Knight queue
            sentAttack.from = knightIndex;
            sentAttack.damage = knights[knightIndex].getKnightDamage();
            //rabbitQueue.push(sentAttack);
            //pthread_mutex_unlock(&knightLock);
            rabbitSafeQueue.enqueue(sentAttack);


            //sem_post(&rabbitSem);
            //rabbitSafeQueue.semaphorePost();
        } else{

            //cout<< "KNIGHT DIED" << endl;

            if(knights[knightIndex].getKnightHp() <= knights[knightIndex].getKnightBravery()){
                knightAlive=false;
                logMessage = knights[knightIndex].getKnightName() + "; " "RUNS AWAY from; "+ type + "!";
                memset(msg.str,0,64);
                strcpy(msg.str,logMessage.c_str());
                write(logPipe[1], (char *) &msg, sizeof(msg));
            }else{
                knightAlive=false;
                logMessage = knights[knightIndex].getKnightName() + "; " "KILLED BY; "+ type + "!";
                memset(msg.str,0,64);
                strcpy(msg.str,logMessage.c_str());
                write(logPipe[1], (char *) &msg, sizeof(msg));
            }



            //Add to Knight queue
            sentAttack.from = knightIndex;
            sentAttack.type = -1; //Knight died message

            rabbitSafeQueue.enqueue(sentAttack);

        }

    }//end

    return NULL;
}


/**
 * Main Method
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char* argv[]) {

    int value,pid,i;
    string logMessageRead;
    string logMessageWrite;
    //Holds rabbit file as string
    string rabbitFileName="";
    //Holds knight file as string
    string knightFileName="";
    //Holds Log file as string
    string logFileName="";
    //Reads In a single line from the text file
    string line="";
    //delimiter for reading in files
    string delimiter = ":";
    //token for holding deliminated string
    string token = "";
    //type of value from input files
    string type = "";
    int loopcounter = 0;
    int knightIndexArray = 0;

    msg msg;    //Message for logs
    attackMsg attackMsg;    //Messages for attacks

    sharedThreadStruct sts; //for passing info into the threads

    //log pipe







    //START FIRST FORK
    signal(SIGTERM, &sigtermHandler);
    pipe(logPipe);
    value = fork();
    if(value == -1)
    {kill(0,SIGKILL);}

    else if(value == 0){
        //Fork off logging process
        LoggingChildFunction(msg, logPipe);
        exit(0);

    }

    else {

        //Check for valid switches
        checkingValidSwitches(argc, argv, logMessageWrite, logPipe);

        //Checking for valid input orders
        checkingValidInputOrders(argc, argv, knightFileName, logFileName, logPipe, logMessageWrite, rabbitFileName);

        //Read in Rabbit file
        readInRabbitFile(logMessageWrite, rabbitFileName, line, delimiter, token, type, rabbit, logPipe);

        //Read in Knight file
        knights = readInKnightFiles(logMessageWrite, knightFileName, line, delimiter, token, type, loopcounter, knightIndexArray,NumOfKnights,knights, logPipe);



        memset(msg.str,0,64);
        strcpy(msg.str,"ATTACK STARTS");
        write(logPipe[1], (char *) &msg, sizeof(msg));

        sts.knightNum = NumOfKnights;
        sts.knights = knights;
        sts.rab = rabbit;


        knightSafeQueue = new SafeQueue<struct attackMsg>[NumOfKnights];



        pthread_t rabbitThread;
        pthread_t knightThread;


        for(int i=0; i<NumOfKnights; i++ ){
            //cout<<"Knight thread start: " << i << endl;
            pthread_create(&knightThread, NULL, knightAttackThread,NULL);
        }

        pthread_create(&rabbitThread, NULL, rabbitAttackThread,NULL);

        //cout << "Num of Knights: " << NumOfKnights << endl;


        pthread_join(rabbitThread, NULL);
        //cout << "RABBIT JOIN" << endl;
        pthread_join(knightThread, NULL);

        //Tell Logger to stop
        memset(msg.str,0,64);
        strcpy(msg.str,"END");
        write(logPipe[1], (char *) &msg, sizeof(msg));
        exit(0);

    }

    return 0;
}
