/*
CO222: Programming Methodology - Project 2
Meeting Data Visualizer

GITHUB - https://github.com/ishanfdo18098/CO222_Project2

Notes (different from sample program):
1) -l or --length both works. similar to that --meeting --time --participants work too.
2) -h is there to print how to use it
3) wrong entries in .csv handled. (samplev1 doesn't check for these)
    - check if participant count is numerical
    - check if time is in valid format (Ashley_Parry,2,1a:38abc:06 also works in samplev1, and it just ignores those values)
    - invalid time formats lead to segmenation faults in samplev1, in this program it shows an error msg

Author : Fernando K.A. Ishan - E/18/098
*/
#include <stdio.h>
#include <getopt.h> //option parsing
#include <stdlib.h> //aoti()
#include <string.h> //strlen()
#include <ctype.h>  //isdigit()

//maximums
#define MAX_ENTRIES 1000
#define MAX_NAME_LENGTH 200 + 1

//this is kind of like the database 😂🤣
//basically the elements are matched by the index number.
//IMPORTANT: element at index 0 is not used. For some reason it didnt work properly (checking if the name exists didnt work for index 0)
//therefore, records are save from index 1 and onwards, index 0 is not used for anything
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
void checkIfStringIsNumerical(char *pointerToString);                                     // check if a string is numerical
void sortData(int *chosenArray);                                                          // sort the dataset using the -m -t -p
int getNumberOfRecordsInArrays();                                                         // returns the number of entries in the database
int getMaximumEnteredNameLength();                                                        // returns the maximum name length currently in namesArray
void printTopAndLastLineOfEntry(int barLength);                                           // print the first line of each entry in graph
void printMiddleLineOfEntry(char *name, int numberAfterTheBar, int barLength);            // print the middle line in each entry
void printEmptyLineInGraph();                                                             // print the empty line after each entry in graph
void printLastLineOfGraph();                                                              // print the last line of graph
int getBarLength(int index, int *chosenArray);                                            // get the length of the bar to print
int getLengthOfNumber(int number);                                                        // get length of int number

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
        exit(0);
    }

    // SORTING
    //select which array to sort
    int *chosenArrayToSort;
    if (isMeeting)
    {
        chosenArrayToSort = numberOfMeetingsARRAY;
    }
    else if (isParticipants)
    {
        chosenArrayToSort = numberOfParticipantsARRAY;
    }
    else if (isTime)
    {
        chosenArrayToSort = timeDurationInMinutesARRAY;
    }

    //sort data according to values in thatt array
    sortData(chosenArrayToSort);
    //after this point, only the names array and chosenArray are in order, other arrays dont mean anything because they were not sorted accordingly

    //print the graphh
    puts("");                                         //go to new line
    for (int i = 0; i < numberOfElementsInGraph; i++) //number of items according to -l
    {
        //if there is no record there, dont print it , and anything after that
        if (namesARRAY[i + 1][0] == 0)
        {
            break;
        }

        int barLength = getBarLength(i + 1, chosenArrayToSort);

        printTopAndLastLineOfEntry(barLength);
        printMiddleLineOfEntry(namesARRAY[i + 1], chosenArrayToSort[i + 1], barLength);
        printTopAndLastLineOfEntry(barLength);
        printEmptyLineInGraph();
    }
    printLastLineOfGraph();

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
                {"help", no_argument, 0, 'h'},
                {"scaled", no_argument, 0, 's'}, //this is the reason why getopt_long is used
                {0, 0, 0, 0}};

        /* getopt_long stores the option index here. */
        int option_index = 0;

        optionEntered = getopt_long(argc, argv, "l:mtpsh", long_options, &option_index); //get each option and their respective strings next to them

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

            if (numberEntered > 0)
            {
                //if the number entered is more than 0
                numberOfElementsInGraph = numberEntered;
            }
            else if (numberEntered < 0)
            {
                //if less than 0
                printf("Invalid option(negative) for [-l]\n");
                printUsage();
                exit(0);
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
        case 'h':
            printUsage();
            exit(0);
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

        //if the line is not formatted properly, error
        if (strlen(line) < 7) //h:mm:ss is at least 7 chars long, if thats not there, wrong format
        {
            puts("File/s contain wrong entries.");
            exit(0);
        }

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
        //now all the pointers are pointed correctly

        //if there were no 2 commas, then something is wrong
        if (round < 4)
        {
            puts("File/s contain wrong entries.");
            exit(0);
        }

        //error checking
        if (isParticipants)
        {
            checkIfStringIsNumerical(pointerToParticipants);
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
    for (int i = 1; i < MAX_ENTRIES; i++)
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
    for (int i = 1; i < MAX_ENTRIES; i++)
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
    int breakFlag = 0; //stop strtok on unwated strings, otherwise it goes onto empty strings and cause errors
    while (token != NULL)
    {
        if (isTime)
        {
            checkIfStringIsNumerical(token);
        }
        switch (round)
        {
        case 0: //its hours
            timeInMinutes += atoi(token) * 60;
            break;
        case 1: //its minutes
            timeInMinutes += atoi(token);
            breakFlag = 1; //dont want to read any other strings after this
            break;
        }
        if (breakFlag)
            break;
        round++;                   //increase the round number
        token = strtok(NULL, ":"); //go to next token
    }

    //return the time in minutes
    return timeInMinutes;
}

//check if the string is numerical
void checkIfStringIsNumerical(char *pointerToString)
{
    //for each char in the string
    for (int i = 0; i < strlen(pointerToString); i++)
    {
        if (isdigit(pointerToString[i]) == 0) //check if that char is not a digit
        {
            puts("File/s contain wrong entries."); //error
            exit(0);
        }
    }
}

//sort the records by the given array
void sortData(int *chosenArray)
{
    //bubble sort
    int didAnythingChange = 1;

    while (didAnythingChange)
    {
        //set flag to 0, to stop the loop eventually
        didAnythingChange = 0;
        //iterate over all the elements except the last
        for (int i = 1; i < getNumberOfRecordsInArrays(); i++)
        {
            //if the element next to the current one is larger than current one
            if (chosenArray[i] < chosenArray[i + 1])
            {
                //swap the elements in the chosenArray to sort
                int tempINT = chosenArray[i];
                chosenArray[i] = chosenArray[i + 1];
                chosenArray[i + 1] = tempINT;

                //then have to change the names accordingly too. otherwise we dont know which number is whose 😂
                char tempName[MAX_NAME_LENGTH];
                strcpy(tempName, namesARRAY[i]);
                strcpy(namesARRAY[i], namesARRAY[i + 1]);
                strcpy(namesARRAY[i + 1], tempName);

                //set flag to 1, then the loop will occur once again
                //at some point, no changes will be made, then the loop ends
                didAnythingChange = 1;
            }
        }
    }
}

//get the current number of records in the array
int getNumberOfRecordsInArrays()
{
    return getIndexOfEmptyElementInNamesArray() - 1; //because index 0 is not used
}

//get the maximum length of a single name entered into the namesArray (until whats specified by -l), used when printing the table to scale
int getMaximumEnteredNameLength()
{
    int maxmimumLength = 0;
    //go through the names that will be printed and find the maximum
    for (int i = 0; i < numberOfElementsInGraph + 1; i++)
    {
        if (strlen(namesARRAY[i]) > maxmimumLength)
        {
            maxmimumLength = strlen(namesARRAY[i]);
        }
    }

    //retur the maximum
    return maxmimumLength;
}

//this prints the top and the last line of each entry in the graph, the one below the name and above the name
void printTopAndLastLineOfEntry(int barLength)
{
    //get the number of spaces to keep after the name, changes with the longest name
    int numberOfSpacesToKeep = getMaximumEnteredNameLength() + 2;
    //print the spaces
    for (int i = 0; i < numberOfSpacesToKeep; i++)
    {
        printf(" ");
    }
    //print the vertical line
    printf("\u2502");

    //print the bar
    for (int i = 0; i < barLength; i++)
    {
        printf("\u2591");
    }
    //goto next line
    puts("");
}

//this prints the middle line of each entry in graph, the line with name and the number
void printMiddleLineOfEntry(char *name, int numberAfterTheBar, int barLength)
{
    //print the name
    printf(" %s", name);

    //print the correct number of spaces
    int numberOfSpaces = getMaximumEnteredNameLength() - strlen(name) + 1;
    for (int i = 0; i < numberOfSpaces; i++)
    {
        printf(" ");
    }

    //prin the verticle line
    printf("\u2502");

    //print the bar
    for (int i = 0; i < barLength; i++)
    {
        printf("\u2591");
    }

    //print the number
    printf("%d", numberAfterTheBar);

    //goto next line
    puts("");
}

//this prints the empty line after each entry in the graph
void printEmptyLineInGraph()
{
    //barlength is zero when its a empty line.
    printTopAndLastLineOfEntry(0);
}

//this prints the last line of the graph, the line with the corner
void printLastLineOfGraph()
{
    //print the number of spaces before the corner
    int numberOfSpacesToKeep = getMaximumEnteredNameLength() + 2;
    for (int i = 0; i < numberOfSpacesToKeep; i++)
    {
        printf(" ");
    }

    //print the corner symbol
    printf("\u2514");

    //get how many lines to print
    int numberOfBars = 80 - numberOfSpacesToKeep - 1;
    //print those lines
    for (int i = 0; i < numberOfBars; i++)
    {
        printf("\u2500");
    }

    //go to new line
    printf("\n");
}

//get the bar length according to --scaled or not
int getBarLength(int index, int *chosenArray)
{
    //first find the maximum bar length, this changes because the name length changes and the maximum graph width is 80
    int numberOfSpacesToKeep = getMaximumEnteredNameLength() + 2;
    int numberOfBars = 80 - numberOfSpacesToKeep - 1;
    int maximumBarLength = numberOfBars - getLengthOfNumber(chosenArray[index]);

    //if its scaled
    if (isScaled)
    {
        //the maximum number in chosenArray is taken as the max length and scaled accordingly

        //this give the number of bars for each unit of chosenArray() based on the maximum number of chosenArray()
        double numberOfBarsPerUnit = maximumBarLength / (double)chosenArray[1];
        int numberOfBarsInThisEntry = (int)(numberOfBarsPerUnit * chosenArray[index]); //multiply that by current records chosenArray() number

        return numberOfBarsInThisEntry;
    }
    else
    {
        //if not scaled

        //find the sum of all the values
        int sumOfValues = 0;
        for (int i = 1; i < MAX_ENTRIES; i++)
        {
            sumOfValues += chosenArray[i];
        }

        //get the number of bars per unit, this way, the whole bar means the sum of all the entries
        double numberOfBarsPerUnit = (double)maximumBarLength / sumOfValues;
        //get the number of bars for this record
        int numberOfBarsForThisEntry = (int)(numberOfBarsPerUnit * chosenArray[index]);

        //return the bar length
        return numberOfBarsForThisEntry;
    }
}

//get length of an int number
int getLengthOfNumber(int number)
{
    //start with length 0
    int length = 0;
    //repeat until number is not 0
    while (number != 0)
    {
        //increment the length
        length++;
        //divide number by 10 (remove one digit from the number)
        number = number / 10;
    }

    //return the length
    return length;
}