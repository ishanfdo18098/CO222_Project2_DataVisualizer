/*
CO222: Programming Methodology - Project 2
Meeting Data Visualizer

GITHUB - https://github.com/ishanfdo18098/CO222_Project2

Notes:
1) -l or --length both works. similar to that --meeting --time --participants work too.


Author : Fernando K.A. Ishan - E/18/098
*/
#include <stdio.h>
#include <getopt.h> //option parsing
#include <stdlib.h> //aoti()
#include <string.h> //strlen()
#include <ctype.h>  //isdigit()

//maximums
#define MAX_ENTRIES 1000
#define MAX_NAME_LENGTH 200

//this is kind of like the database 😂🤣
//basically the elements are matched by the index number
char namesARRAY[MAX_ENTRIES][MAX_NAME_LENGTH] = {};
int numberOfMeetingsARRAY[MAX_ENTRIES] = {};
int numberOfParticipantsARRAY[MAX_ENTRIES] = {};
int timeDurationInMinutesARRAY[MAX_ENTRIES] = {};

void parseOptions(int argc, char **argv);                                                 // option parsing
void printUsage();                                                                        // print how to use the program
void readFileThenAddThemToArrays(char *fileName);                                         // read from file
int getIndexOfNameInArray(char *namePointer);                                             // get the index of the name in the array
int getIndexOfEmptyElementInNamesArray();                                                 // get index of the first empty element in name array to add element to
void writeNEWRecordToArrays(char *nameSTR, char *pariticipantsSTR, char *timeInHoursSTR); // write a record to all 3 arrays
int convertHoursToMinutes(char *timeInHours);                                             // convert hours into minutes
void updateExisitingRecord(char *nameSTR, char *pariticipantsSTR, char *timeInHoursSTR);  // update existing record

int numberOfElementsInGraph = 10; // -l option given
int isScaled = 0;                 // flag for --scaled
int isMeeting = 0;                // flag for -m
int isParticipants = 0;           // flag for -p
int isTime = 0;                   // flag for -t
char *programName;                // used to get the program name in printUsage()

int main(int argc, char **argv)
{
    //make a pointer to the name of program, used when printing the usage
    programName = &(argv[0][0]);

    //parse the options -m -t -p -l
    parseOptions(argc, argv);

    //process the files
    int fileCount = 0; //keep a count of files to know if there are 0 files - > error
    for (int index = optind; index < argc; index++)
    {
        //renaming for easiness of reading and writing
        char *currentFileName = &argv[index][0];

        // printf("current filename: %s\n", currentFileName);

        // check if the file format is correct
        char *formatOfCurrentFile = &currentFileName[strlen(currentFileName) - 4]; //get the pointer to the format of file
        if (strcmp(formatOfCurrentFile, ".csv") != 0)                              //check if file format is .csv
        {
            //if its not .csv
            puts("Only .csv files should be given as inputs.");
            exit(0);
        }
        else
        {
            //if its .csv
            fileCount++;
            //read the file line by line and copy the data into respective arrays
            readFileThenAddThemToArrays(currentFileName);
        }
    }

    //if there are no files entered as args
    if (fileCount == 0)
    {
        puts("No input files were given");
        printUsage();
    }

    //just for testing
    for (int i = 0; i < MAX_ENTRIES; i++)
    {
        printf("%s %d %d %d\n", namesARRAY[i], numberOfMeetingsARRAY[i], numberOfParticipantsARRAY[i], timeDurationInMinutesARRAY[i]);
        if (namesARRAY[i][0] == 0)
        {
            break;
        }
    }

    return 0;
}

//parse the options
//set the flags
//check if more than 1 graphing option is given (-m -t -p)
void parseOptions(int argc, char **argv)
{
    // https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html
    int optionEntered;
    opterr = 0; //disable echoing that there is an error
    while (1)   //until there are options left
    {
        //options in long form and short
        static struct option long_options[] =
            {
                //longForm, argsRequired?, flagVariableAddress, shortForm
                {"length", required_argument, 0, 'l'},
                {"meeting", no_argument, 0, 'm'},
                {"time", no_argument, 0, 't'},
                {"participants", no_argument, 0, 'p'},
                {"scaled", no_argument, 0, 's'}, //this is the reason why getopt_long is used
                {0, 0, 0, 0}};

        /* getopt_long stores the option index here. */
        int option_index = 0;

        optionEntered = getopt_long(argc, argv, "l:mtps", long_options, &option_index); //get each option and their respective strings next to them

        /* Detect the end of the options. */
        if (optionEntered == -1) //if there are no options left
            break;

        //switch on each optionEntered
        switch (optionEntered)
        {
        case 'l': //if -l is entered
            //check if optarg is a numerical value
            for (int i = 0; i < strlen(optarg); i++)
            {
                if (isdigit(optarg[i]) == 0)
                {
                    //if its not numerical , etc, -l abc
                    printf("Invalid options for [-l]\n");
                    printUsage();
                    exit(0);
                }
            }

            //convert string to int
            int numberEntered = atoi(optarg);

            if (numberEntered > 0 && numberEntered <= 10)
            {
                //if the number entered is more than 0 and less tham 10
                numberOfElementsInGraph = numberEntered;
            }
            else if (numberEntered < 0)
            {
                //if less than 0
                printf("Invalid option(negative) for [-l]\n");
                printUsage();
                exit(0);
            }
            else if (numberEntered > 10)
            {
                //if more than 10 default to 10
                numberOfElementsInGraph = 10;
            }
            break;
        case 'm': // -m
            isMeeting = 1;
            break;
        case 't': // -t
            isTime = 1;
            break;
        case 'p': //-t
            isParticipants = 1;
            break;
        case 's': //--scaled
            isScaled = 1;
            break;
        case '?': //everything thats not specified (and has - sign before the word)
            if (optopt == 'l')
            {
                // -l is there but without any number in front of it
                printf("Not enough options for [-l]\n");
                printUsage();
                exit(0);
            }
            break;
        }
    }

    //check if all the options are valid
    //had to use whole new thing because the error log showed the argument entered, getopt only returns a char
    //but need to echo the whole word ( -abc vs -a )
    char optionsPossible[5][10] = {"-m", "-t", "-p", "--scaled", "-l"};
    for (int i = 0; i < argc; i++)
    {
        if (argv[i][0] != '-') // if its not a option, dont check it
        {
            continue;
        }

        //check for matches
        int matchFound = 0;
        for (int j = 0; j < 5; j++) //loop over all the possible words
        {
            if (strcmp(argv[i], optionsPossible[j]) == 0) //if it matches
            {
                matchFound = 1; //make the flag 1
            }
        }

        if (matchFound == 0) //if there are no matches for that option
        {
            printf("Invalid option [%s]\n", argv[i]); //show error, %s is the whole reason for using this seperate part for checking those options
            printUsage();
            exit(0);
        }

        if (strcmp(argv[i], "-l") == 0) //if its -l, you dont have to check the next word as its checked in getopt anyway
        {
            i++;
        }
    }

    //if no options are given, default should be meeting
    if (isMeeting + isParticipants + isTime == 0)
    {
        isMeeting = 1;
    }

    //if multiple options are given
    if (isMeeting + isParticipants + isTime > 1)
    {
        puts("Cannot plot multiple parameters in same graph.");
        printUsage();
        exit(0);
    }
}

//print how to use the program, the program name is also printed in it
//thats why the name was stored at the top
void printUsage()
{
    printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n", programName);
}

//read the file and write all the data into the corresponding arrays
void readFileThenAddThemToArrays(char *fileName)
{
    //open the given file
    FILE *filePointer;
    //open file as "r"
    filePointer = fopen(fileName, "r");

    //if file is not available
    if (filePointer == NULL)
    {
        puts("Cannot open one or more given files");
        exit(0);
    }

    //if the file is empty
    int c = fgetc(filePointer);
    if (c == EOF)
    {
        puts("No data to process");
    }
    else
    {
        ungetc(c, filePointer); //otherwise this character will be missing when we read the line again
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    //read each line
    while ((read = getline(&line, &len, filePointer)) != -1)
    {
        // https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm

        char *token;

        //first token
        token = strtok(line, ",");

        //get pointers to the corresponding parts in the line
        char *pointerToName = token; //first token is for the name
        char *pointerToParticipants; //second token - participants
        char *pointerToTimeInHours;  // third token - time
        int round = 1;               //round is counted to idenity which token is going now
        /* walk through other tokens */
        while (token != NULL)
        {
            token = strtok(NULL, ",");
            round++;
            //based on the round, save the tokens into pointer variabels
            if (round == 2)
            {
                pointerToParticipants = token;
            }
            else if (round == 3)
            {
                pointerToTimeInHours = token;
            }
        }

        //check if this name exists in our array
        int isNameExist = getIndexOfNameInArray(pointerToName);

        if (isNameExist)
        {
            //if it exists, update the corresponding records
            updateExisitingRecord(pointerToName, pointerToParticipants, pointerToTimeInHours);
        }
        else
        {
            //if it doesnt exist, create new records
            writeNEWRecordToArrays(pointerToName, pointerToParticipants, pointerToTimeInHours);
        }
    }

    //close the file
    fclose(filePointer);
}

//search for name in array and return the index if available, else return 0
int getIndexOfNameInArray(char *namePointer)
{
    //loop through the list to find if the name exists
    for (int i = 0; i < MAX_ENTRIES; i++)
    {
        if (strcmp(namePointer, namesARRAY[i]) == 0)
        {
            //if the name matches, return the index
            return i;
        }

        //if the first char of current element is NULL, dont have to check for names after that as everything will be NULL after that
        if (namesARRAY[i][0] == 0)
        {
            break;
        }
    }

    //name doesnt exist, return 0
    return 0;
}

//get the index of a empty element in the arrays
//used to write new elements to the arrays
int getIndexOfEmptyElementInNamesArray()
{
    //look through all the elements in namesArray
    for (int i = 0; i < MAX_ENTRIES; i++)
    {
        //if the names first char is NULL, whole record is null, return the index
        if (namesARRAY[i][0] == 0)
        {
            return i;
        }
    }
    //if the index doesnt return it means the array is full. size exceeded
    puts("Array full, please increase MAX_ENTRIES");
    exit(0);
}

//write a new record into the arrays
void writeNEWRecordToArrays(char *nameSTR, char *pariticipantsSTR, char *timeInHoursSTR)
{
    //find the index to write to
    int indexToWriteTo = getIndexOfEmptyElementInNamesArray(nameSTR); //finds index if existing or give new index to write to

    //convert strings to int
    int currentNumberOfParticipantsINT = atoi(pariticipantsSTR);
    int timeInMinsINT = convertHoursToMinutes(timeInHoursSTR);

    //write the data to the arrays at the correct index
    strcpy(namesARRAY[indexToWriteTo], nameSTR);
    numberOfMeetingsARRAY[indexToWriteTo] = 1;
    numberOfParticipantsARRAY[indexToWriteTo] = currentNumberOfParticipantsINT;
    timeDurationInMinutesARRAY[indexToWriteTo] = timeInMinsINT;
}

//update an existing record, meaning add the current values to the old values
void updateExisitingRecord(char *nameSTR, char *pariticipantsSTR, char *timeInHoursSTR)
{
    //find the index to write to
    int indexToWriteTo = getIndexOfNameInArray(nameSTR); //finds index if existing or give new index to write to

    //convert strings to int
    int currentNumberOfParticipantsINT = atoi(pariticipantsSTR);
    int timeInMinsINT = convertHoursToMinutes(timeInHoursSTR);

    //write the data to the arrays
    //name is not updated because it cant change 😊
    numberOfMeetingsARRAY[indexToWriteTo] += 1;
    numberOfParticipantsARRAY[indexToWriteTo] += currentNumberOfParticipantsINT;
    timeDurationInMinutesARRAY[indexToWriteTo] += timeInMinsINT;
}

//convert string hours into int minutes
int convertHoursToMinutes(char *timeInHours)
{
    //format is in hh:mm:ss but sometimes its not hh, its h

    char *token;
    /* get the first token */
    token = strtok(timeInHours, ":");
    /* walk through other tokens */
    int round = 0; //keep the round number to know if its hours or minutes
    int timeInMinutes = 0;
    while (token != NULL)
    {
        switch (round)
        {
        case 0: //its hours
            timeInMinutes += atoi(token) * 60;
            break;
        case 1: //its minutes
            timeInMinutes += atoi(token);
            break;
        }
        round++;                   //increase the round number
        token = strtok(NULL, ":"); //go to next token
    }

    //return the time in minutes
    return timeInMinutes;
}