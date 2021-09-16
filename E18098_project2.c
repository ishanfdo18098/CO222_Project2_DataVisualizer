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

#define MAX_ENTRIES 1000

char namesARRAY[MAX_ENTRIES][100] = {};
int numberOfMeetingsARRAY[MAX_ENTRIES] = {};
int numberOfParticipantsARRAY[MAX_ENTRIES] = {};
int timeDurationInMinutesARRAY[MAX_ENTRIES] = {};

void parseOptions(int argc, char **argv);                                                 // option parsing
void printUsage();                                                                        // print how to use the program
void readFile(char *fileName);                                                            // read from file
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
char *programName;                //used to get the program name in printUsage()

int main(int argc, char **argv)
{
    programName = &(argv[0][0]);

    //parse the options -m -t -p -l
    parseOptions(argc, argv);

    //process the files
    int fileCount = 0;
    for (int index = optind; index < argc; index++)
    {
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
            readFile(currentFileName);
            continue;
        }
    }

    if (fileCount == 0)
    {
        puts("No input files were given");
        printUsage();
    }

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

void parseOptions(int argc, char **argv)
{
    // https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html
    int optionEntered;
    opterr = 0;
    while (1)
    {
        //options in long form and short
        static struct option long_options[] =
            {
                //longForm, argsRequired?, flagVariableAddress, shortForm
                {"length", required_argument, 0, 'l'},
                {"meeting", no_argument, 0, 'm'},
                {"time", no_argument, 0, 't'},
                {"participants", no_argument, 0, 'p'},
                {"scaled", no_argument, 0, 's'},
                {0, 0, 0, 0}};

        /* getopt_long stores the option index here. */
        int option_index = 0;

        optionEntered = getopt_long(argc, argv, "l:mtps", long_options, &option_index);

        /* Detect the end of the options. */
        if (optionEntered == -1)
            break;

        //switch on each optionEntered
        switch (optionEntered)
        {
        case 'l':
            // printf("option -l with %s\n", optarg);

            for (int i = 0; i < strlen(optarg); i++)
            {
                if (isdigit(optarg[i]) == 0)
                {
                    printf("Invalid options for [-l]\n");
                    printUsage();
                    exit(0);
                }
            }

            int numberEntered = atoi(optarg);
            if (numberEntered > 0 && numberEntered <= 10)
            {
                numberOfElementsInGraph = numberEntered;
            }
            else if (numberEntered < 0)
            {
                printf("Invalid option(negative) for [-l]\n");
                printUsage();
                exit(0);
            }
            else if (numberEntered > 10)
            {
                numberOfElementsInGraph = 10;
            }

            // printf("-l changed to %d\n", numberOfElementsInGraph);
            break;
        case 'm':
            // puts("option -m");
            isMeeting = 1;
            break;
        case 't':
            // printf("option -t\n");
            isTime = 1;
            break;
        case 'p':
            // printf("option -p\n");
            isParticipants = 1;
            break;
        case 's':
            // printf("option --scaled\n");
            isScaled = 1;
            break;
        case '?':
            if (optopt == 'l')
            {
                printf("Not enough options for [-l]\n");
                printUsage();
                exit(0);
            }
            break;
        }
    }

    //check if all the options are valid
    char optionsPossible[5][10] = {"-m", "-t", "-p", "--scaled", "-l"};
    for (int i = 0; i < argc; i++)
    {
        if (argv[i][0] != '-') // if its not a option, dont check it
        {
            continue;
        }
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
            printf("Invalid option [%s]\n", argv[i]); //show error
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

void printUsage()
{
    printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n", programName);
}

void readFile(char *fileName)
{
    //open the given file
    FILE *filePointer;
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
        ungetc(c, filePointer);
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, filePointer)) != -1)
    {
        // https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm

        char *token;

        /* get the first token */
        token = strtok(line, ",");

        char *pointerToName = token;
        char *pointerToParticipants;
        char *pointerToTimeInHours;
        int round = 1;
        /* walk through other tokens */
        while (token != NULL)
        {
            token = strtok(NULL, ",");
            if (round == 1)
            {
                pointerToParticipants = token;
            }
            else if (round == 2)
            {
                pointerToTimeInHours = token;
            }
            round++;
        }

        // printf("%s %s %s", pointerToName, pointerToParticipants, pointerToTimeInHours);

        int isNameExist = getIndexOfNameInArray(pointerToName);
        // printf("%d", isNameExist);

        if (isNameExist)
        {
            updateExisitingRecord(pointerToName, pointerToParticipants, pointerToTimeInHours);
        }
        else
        {
            writeNEWRecordToArrays(pointerToName, pointerToParticipants, pointerToTimeInHours);
        }
    }

    fclose(filePointer);
}

int getIndexOfNameInArray(char *namePointer)
{
    //loop through the list to find if the name exists
    for (int i = 0; i < MAX_ENTRIES; i++)
    {
        if (strcmp(namePointer, namesARRAY[i]) == 0)
        {
            return i;
        }

        //if a name is 0, dont have to check for names after that.
        if (namesARRAY[i][0] == 0)
        {
            break;
        }
    }
    //name doesnt exist
    return 0;
}

int getIndexOfEmptyElementInNamesArray()
{
    for (int i = 0; i < MAX_ENTRIES; i++)
    {
        if (namesARRAY[i][0] == 0)
        {
            return i;
        }
    }
    puts("Array full, please increase MAX_ENTRIES");
    exit(0);
}

void writeNEWRecordToArrays(char *nameSTR, char *pariticipantsSTR, char *timeInHoursSTR)
{
    //find the index to write to
    int indexToWriteTo = getIndexOfEmptyElementInNamesArray(nameSTR); //finds index if existing or give new index to write to

    //convert strings to int
    int currentNumberOfParticipantsINT = atoi(pariticipantsSTR);
    int timeInMinsINT = convertHoursToMinutes(timeInHoursSTR);
    // printf("%d\n", timeInMinsINT);
    // printf("%d\n", currentNumberOfParticipantsINT);

    //write the data to the arrays
    strcpy(namesARRAY[indexToWriteTo], nameSTR);
    numberOfMeetingsARRAY[indexToWriteTo] = 1;
    numberOfParticipantsARRAY[indexToWriteTo] = currentNumberOfParticipantsINT;
    timeDurationInMinutesARRAY[indexToWriteTo] = timeInMinsINT;
}

void updateExisitingRecord(char *nameSTR, char *pariticipantsSTR, char *timeInHoursSTR)
{
    //find the index to write to
    int indexToWriteTo = getIndexOfNameInArray(nameSTR); //finds index if existing or give new index to write to

    //convert strings to int
    int currentNumberOfParticipantsINT = atoi(pariticipantsSTR);
    int timeInMinsINT = convertHoursToMinutes(timeInHoursSTR);

    //write the data to the arrays
    numberOfMeetingsARRAY[indexToWriteTo] += 1;
    numberOfParticipantsARRAY[indexToWriteTo] += currentNumberOfParticipantsINT;
    timeDurationInMinutesARRAY[indexToWriteTo] += timeInMinsINT;
}

int convertHoursToMinutes(char *timeInHours)
{
    //format is in hh:mm:ss but sometimes its no hh, its h

    char *token;
    /* get the first token */
    token = strtok(timeInHours, ":");
    /* walk through other tokens */
    int round = 0;
    int timeInMinutes = 0;
    while (token != NULL)
    {
        switch (round)
        {
        case 0:
            timeInMinutes += atoi(token) * 60;
            break;
        case 1:
            timeInMinutes += atoi(token);
            break;
        }
        round++;
        token = strtok(NULL, ":");
    }

    return timeInMinutes;
}