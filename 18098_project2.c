/*
CO222: Programming Methodology - Project 2
Meeting Data Visualizer

GITHUB - https://github.com/ishanfdo18098/CO222_Project2

Notes (different from sample program):
1) wrong entries in .csv handled. (samplev1 doesn't check for these)
    - check if participant count is numerical
    - check if time is in valid format (Ashley_Parry,2,1a:38abc:06 also works in samplev1, and it just ignores those values)
    - invalid time formats lead to segmenation faults in samplev1, in this program it shows an error msg
2) ./sample somename.csvLOG give cannot open given files when its not a csv file. Mine shows that its not a csv file


Author : Fernando K.A. Ishan - E/18/098
*/
#include <stdio.h>
#include <stdlib.h> //aoti()
#include <string.h> //strlen()
#include <ctype.h>  //isdigit()
#include <limits.h> //for the minimum number of long long

//a node in the linked list
typedef struct record
{
    char *name;
    long long data;
    struct record *nextRecord;
} record;

//keep linked lists of names starting from same character
//Thank you Thamish for the idea 😍
typedef struct namesStartingWithChar
{
    record *record;
    struct namesStartingWithChar *nextName;
} namesStartingWithChar;

namesStartingWithChar *array[255] = {}; //there are 255 linked lists for all 255 chars in char type.
//There are only 26 characters in alphabet. but this also works 😂

//pointer to head and tail
record *head = NULL;
record *tail = NULL;

int numberOfElementsInGraph = 10;            // -l option given
int isScaled = 0;                            // flag for --scaled
int isMeeting = 0;                           // flag for -m
int isParticipants = 0;                      // flag for -p
int isTime = 0;                              // flag for -t
char *programName;                           // used to get the program name in printUsage()
record **allMaximumNodes;                    //instead of sorting, find the maximum nodes in each iteration
long long numberOfNodesInMainLinkedList = 0; //numberOfNodes in the linked list
long long numberOfEntriesToPrintInGraph = 0; //how much nodes to print, changes based on -l and number of nodes in linked list

void parseOptions();                      // option parsing
void processFiles();                      // process the files
void printGraph();                        // print the graph
void printUsage();                        // print how to use the program
void readFileThenAddThemToArrays();       // read from file
record *getPointerOfNameInLinkedList();   // get the index of the name in the array
int getIndexOfEmptyElementInNamesArray(); // get index of the first empty element in name array to add element to
void writeNEWRecordToArrays();            // write a record to all 3 arrays
long long convertHoursToMinutes();        // convert hours into minutes
void updateExisitingRecord();             // update existing record
void checkIfStringIsNumerical();          // check if a string is numerical
void sortData();                          // sort the dataset using the -m -t -p
int getNumberOfRecordsInArrays();         // returns the number of entries in the database
int getMaximumEnteredNameLength();        // returns the maximum name length currently in namesArray
void printTopAndLastLineOfEntry();        // print the first line of each entry in graph
void printMiddleLineOfEntry();            // print the middle line in each entry
void printEmptyLineInGraph();             // print the empty line after each entry in graph
void printLastLineOfGraph();              // print the last line of graph
int getBarLength();                       // get the length of the bar to print
int getLengthOfNumber();                  // get length of int number
record *createNewRecord();                // create a new record and return the pointer

int main(int argc, char **argv)
{
    //make a pointer to the name of program, used when printing the usage
    programName = &(argv[0][0]);

    //parse the options -m -t -p -l
    parseOptions(argc, argv);

    //process the files that are inputted by the user
    processFiles(argc, argv);

    //sort the linked list
    //create a array of the maximum nodes
    numberOfEntriesToPrintInGraph = (numberOfElementsInGraph > numberOfNodesInMainLinkedList) ? numberOfNodesInMainLinkedList : numberOfElementsInGraph;
    allMaximumNodes = (record **)malloc(sizeof(record *) * numberOfEntriesToPrintInGraph);
    //set all the pointers to NULL
    for (int i = 0; i < numberOfEntriesToPrintInGraph; i++)
    {
        allMaximumNodes[i] = NULL;
    }
    //populate the array by the maximum entries of the linked list
    sortData();

    //if the maximum number is zero, error
    if (allMaximumNodes[0]->data == 0)
    {
        puts("No data to process");
        exit(0);
    }

    //print the graph
    printGraph();

    //exit the program
    return 0;
}

//parse the options
//set the flags
//check if more than 1 graphing option is given (-m -t -p)
void parseOptions(int argc, char **argv)
{
    //check if all the options are valid
    char optionsPossible[5][10] = {"-m", "-t", "-p", "--scaled", "-l"};
    //-------------------------------0-----1-----2------3----------4   <----indexes
    for (int i = 0; i < argc; i++)
    {
        if (argv[i][0] != '-') // if its not a option, dont check it
        {
            continue;
        }

        //check for matches
        int matchFound = 0;
        int matchIndex = -1;        //which string was it matched to ?
        for (int j = 0; j < 5; j++) //loop over all the possible words
        {
            if (strcmp(argv[i], optionsPossible[j]) == 0) //if it matches
            {
                matchFound = 1; //make the flag 1
                matchIndex = j; //matched index
            }
        }

        //if a match is found
        if (matchFound)
        {
            switch (matchIndex) //switch on which was the option
            {
            case 0: //-m
                isMeeting = 1;
                break;
            case 1: //-t
                isTime = 1;
                break;
            case 2: //-p
                isParticipants = 1;
                break;
            case 3: //--scaled
                isScaled = 1;
                break;
            case 4: // -l with or without another value
                if (i + 1 >= argc)
                {
                    // -l is there but without any number in front of it
                    printf("Not enough options for [-l]\n");
                    printUsage();
                    exit(0);
                }
                //check if optarg is a numerical value
                for (int j = 0; j < strlen(argv[i + 1]); j++)
                {
                    if (isdigit(argv[i + 1][j]) == 0 && argv[i + 1][j] != '-') //if its not a digit and not negative sign
                    {
                        //if its not numerical , etc, -l abc
                        printf("Invalid options for [-l]\n");
                        printUsage();
                        exit(0);
                    }
                }

                //convert string to int
                int numberEntered = atoi(argv[i + 1]);

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
                else if (numberEntered == 0) //samplev1 didnt print anything when -l is 0
                {
                    exit(0);
                }
                break;
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

void processFiles(int argc, char **argv)
{
    //process the files
    int fileCount = 0; //keep a count of files to know if there are 0 files - > error
    for (int index = 1; index < argc; index++)
    {
        //renaming for easiness of reading and writing
        char *currentFileName = &argv[index][0];

        if (strcmp(currentFileName, "-l") == 0) //if its -l, dont read the next string that could be the value for -l
        {
            index++;
            continue;
        }

        if (currentFileName[0] == '-') //if its some other option
        {
            continue;
        }

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
}

//print the graph
void printGraph()
{
    puts("");                                              //go to new line
    int maximumNameLength = getMaximumEnteredNameLength(); //the maximum name length under -l
    //go through all the nodes pointed by the maxiimumArray
    for (int i = 0; i < numberOfEntriesToPrintInGraph; i++)
    {
        if (allMaximumNodes[i] == NULL) //just in case if something is null, dont print it
        {
            break;
        }

        char *name = allMaximumNodes[i]->name;
        long long data = allMaximumNodes[i]->data;
        //get the bar length for this entry
        int barLength = getBarLength(data, maximumNameLength);

        //print a single node
        printTopAndLastLineOfEntry(barLength, maximumNameLength);         //top line
        printMiddleLineOfEntry(name, data, barLength, maximumNameLength); //middle line with name
        printTopAndLastLineOfEntry(barLength, maximumNameLength);         //bottom line with bar
        printEmptyLineInGraph(maximumNameLength);                         //empty line without bars
    }
    printLastLineOfGraph(maximumNameLength); //this is the axis
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
        exit(0);
    }
    else
    {
        ungetc(c, filePointer); //otherwise this character will be missing when we read the line again
    }

    int bufferLength = 255;
    char line[bufferLength];
    //read each line
    while (fgets(line, bufferLength, filePointer))
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
        int doesNameExist = 0;
        record *pointerToExistingRecord = getPointerOfNameInLinkedList(pointerToName, &doesNameExist);

        if (doesNameExist)
        {
            //if it exists, update the corresponding records
            updateExisitingRecord(pointerToName, pointerToParticipants, pointerToTimeInHours, pointerToExistingRecord);
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

//search for name in array and return the pointer if available
record *getPointerOfNameInLinkedList(char *namePointer, int *doesNameExist)
{
    //select the head from the array of linked lists that start from a character
    namesStartingWithChar *currentNode = array[(int)namePointer[0]];

    //loop through the list to find if the name exists
    while (currentNode != NULL)
    {
        if (strcmp(namePointer, currentNode->record->name) == 0)
        {
            //if the name matches, return the pointer
            *doesNameExist = 1;
            return currentNode->record;
        }

        //go to next node
        currentNode = currentNode->nextName;
    }

    //name doesnt exist, return 0
    return 0;
}

//write a new record into the arrays
void writeNEWRecordToArrays(char *nameSTR, char *pariticipantsSTR, char *timeInHoursSTR)
{
    record *thisRecord = createNewRecord(nameSTR); //create a new record with given name

    //add data accordingly
    if (isMeeting)
    {
        thisRecord->data = 1;
    }
    else if (isTime)
    {
        long long timeInMinsINT = convertHoursToMinutes(timeInHoursSTR);
        thisRecord->data = timeInMinsINT;
    }
    else if (isParticipants)
    {
        long long currentNumberOfParticipantsINT = atoll(pariticipantsSTR);
        thisRecord->data = currentNumberOfParticipantsINT;
    }

    //add the new node the the linked list
    if (head == NULL)
    {                      //if this is the first round
        head = thisRecord; //head is this node
        tail = thisRecord; //tail is also this node
    }
    else
    {                                  //if this is not the first record
        tail->nextRecord = thisRecord; //the node after tail is this node
        tail = thisRecord;             //then this node becomes the new tail
    }

    numberOfNodesInMainLinkedList += 1; //keep track of how many elements are there in the linked list
}

//update an existing record, meaning add the current values to the old values
void updateExisitingRecord(char *nameSTR, char *pariticipantsSTR, char *timeInHoursSTR, record *thisRecord)
{
    //update the existing record
    if (isParticipants)
    {
        long long currentNumberOfParticipantsINT = atoll(pariticipantsSTR);
        thisRecord->data += currentNumberOfParticipantsINT;
    }
    else if (isTime)
    {
        long long timeInMinsINT = convertHoursToMinutes(timeInHoursSTR);
        thisRecord->data += timeInMinsINT;
    }
    else if (isMeeting)
    {
        thisRecord->data += 1;
    }
}

//convert string hours into int minutes
long long convertHoursToMinutes(char *timeInHours)
{
    //format is in hh:mm:ss but sometimes its not hh, its h

    char *token;
    /* get the first token */
    token = strtok(timeInHours, ":");
    /* walk through other tokens */
    int round = 0; //keep the round number to know if its hours or minutes
    long long timeInMinutes = 0;
    int breakFlag = 0; //stop strtok on unwated strings, otherwise it goes onto empty strings and cause errors
    while (token != NULL)
    {
        //check if time is in valid format
        if (isTime)
        {
            checkIfStringIsNumerical(token);
        }
        switch (round)
        {
        case 0: //its hours
            timeInMinutes += atoll(token) * 60;
            break;
        case 1: //its minutes
            timeInMinutes += atoll(token);
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
    //create varibale that contains the limit, then strlen wont run every iteration
    int limit = strlen(pointerToString);
    //for each char in the string
    for (int i = 0; i < limit; i++)
    {
        if (isdigit(pointerToString[i]) == 0) //check if that char is not a digit
        {
            puts("File/s contain wrong entries."); //error
            exit(0);
        }
    }
}

//sort the records in the linked list
void sortData()
{
    //Thank you Piumal for the idea 😍
    //instead of sorting, find the top required nodes by going through the linked list and finding the maxmium values
    int index = 0; // which index are we writing in the allMaximumArray

    record *currentNode = head; //traverse the linked list
    record *maximumNode = NULL;

    long long maximumData;
    for (int i = 0; i < numberOfEntriesToPrintInGraph; i++) //get the top most entries
    {
        currentNode = head;
        maximumData = LLONG_MIN;    //minimum number possible in type LONG LONG
        while (currentNode != NULL) //go through all the nodes
        {
            if (currentNode->data > maximumData)
            {
                //checks if the current value is larger than the maximumData
                //if its larger, check if we have already saved that name, then dont save it again
                //if its not save before, then save it and set the new maximum
                //this doesnt have any effect on the linked list, jsut goes throgh everything and extracts the pointers to the needed nodes
                int nameFound = 0;
                for (int i = 0; i < numberOfEntriesToPrintInGraph; i++)
                {
                    if (allMaximumNodes[i] != NULL && strcmp(currentNode->name, allMaximumNodes[i]->name) == 0) //did we already take that name ?
                    {
                        nameFound = 1;
                        break;
                    }
                }
                if (!nameFound) //if we havent taken that node before
                {
                    maximumData = currentNode->data;
                    maximumNode = currentNode;
                }
            }

            currentNode = currentNode->nextRecord; //next node
        }
        //after going through the linked list, the maximum must be saved
        allMaximumNodes[index++] = maximumNode;
    }

    // //bubble sort
    // record *currentNode = head;
    // record *previousNode = head;
    // int didAnythingChange = 1; //run the loop again if something is changed
    // int currentNodeValue = 0;  //are we on -m -t -p ?
    // int nextNodeValue = 0;     //are we on -m -t -p ?

    // while (didAnythingChange)
    // {
    //     //set flag to 0, to stop the loop eventually
    //     didAnythingChange = 0;
    //     //iterate over all the elements except the last
    //     while (currentNode->nextRecord != NULL)
    //     {
    //         //get values of current and next
    //         currentNodeValue = currentNode->data;
    //         nextNodeValue = currentNode->nextRecord->data;

    //         //if the element next to the current one is larger than current one
    //         if (currentNodeValue < nextNodeValue)
    //         {
    //             //set flag to 1, then the loop will occur once again
    //             //at some point, no changes will be made, then the loop ends
    //             didAnythingChange = 1;
    //             if (currentNode == head && currentNode->nextRecord != tail) //current is at head, but there are more than 3 modes in total
    //             {
    //                 // puts("1");

    //                 //update the head pointer
    //                 record *tempCurrentNode = currentNode;
    //                 head = currentNode->nextRecord;
    //                 currentNode->nextRecord = currentNode->nextRecord->nextRecord;
    //                 head->nextRecord = tempCurrentNode;
    //             }
    //             else if (currentNode->nextRecord == tail && currentNode != head) //next is tail, but current is not head. This takes care of the replacing the tail.
    //             {
    //                 // puts("2");
    //                 previousNode->nextRecord = tail;
    //                 tail->nextRecord = currentNode;
    //                 currentNode->nextRecord = NULL;
    //                 tail = currentNode;
    //                 //changed the tail position, therefore dont have to check the next node
    //                 break;
    //             }
    //             else if (currentNode == head && currentNode->nextRecord == tail) //there are only two nodes in the linked list
    //             {
    //                 // puts("3");
    //                 //swap head and tail
    //                 record *tempNode = head;
    //                 tail->nextRecord = tempNode;
    //                 tempNode->nextRecord = NULL;
    //                 head = tail;
    //                 tail = tempNode;
    //                 break;
    //             }
    //             else if (currentNode->nextRecord != NULL && currentNode->nextRecord->nextRecord != NULL)
    //             { //there are 4 consecutive nodes to sort, general case. somewhere in the middle
    //                 // puts("4");
    //                 record *nextNode = currentNode->nextRecord;
    //                 record *secondNextNode = currentNode->nextRecord->nextRecord;

    //                 previousNode->nextRecord = nextNode;
    //                 nextNode->nextRecord = currentNode;
    //                 currentNode->nextRecord = secondNextNode;
    //             }
    //             else //there shouldnt be any other case than that. If there is, my code is wrong 😥
    //             {
    //                 puts("sortData: somethign wrong in the code. This must be impossible");
    //                 exit(0);
    //             }

    //             //I made the sorting method above, but the same is done in a way easier method here https://www.geeksforgeeks.org/bubble-sort-for-linked-list-by-swapping-nodes/

    //             //this is the old sorting by copying values over, this was much slower than the new method

    //             // //swap the elements in the chosenArray to sort
    //             // long long tempLONGLONG = currentNode->numberOfMeetings;
    //             // currentNode->numberOfMeetings = currentNode->nextRecord->numberOfMeetings;
    //             // currentNode->nextRecord->numberOfMeetings = tempLONGLONG;

    //             // tempLONGLONG = currentNode->numberOfParticipants;
    //             // currentNode->numberOfParticipants = currentNode->nextRecord->numberOfParticipants;
    //             // currentNode->nextRecord->numberOfParticipants = tempLONGLONG;

    //             // tempLONGLONG = currentNode->timeDurationInMinutes;
    //             // currentNode->timeDurationInMinutes = currentNode->nextRecord->timeDurationInMinutes;
    //             // currentNode->nextRecord->timeDurationInMinutes = tempLONGLONG;

    //             // //then have to change the names accordingly too. otherwise we dont know which number is whose 😂
    //             // char tempName[MAX_NAME_LENGTH];
    //             // strcpy(tempName, currentNode->name);
    //             // strcpy(currentNode->name, currentNode->nextRecord->name);
    //             // strcpy(currentNode->nextRecord->name, tempName);
    //         }

    //         // go to next node
    //         previousNode = currentNode;
    //         currentNode = currentNode->nextRecord;
    //     }

    //     //go over the whole linked list again
    //     currentNode = head;
    //     previousNode = head;
    // }

    // //if the maximum is zero, there is nothing to print anyway
    // if (head->data == 0)
    // {
    //     puts("No data to process");
    //     exit(0);
    // }
}

//get the maximum length of a single name entered into the namesArray (until whats specified by -l), used when printing the table to scale
int getMaximumEnteredNameLength()
{
    int maxmimumLength = 0;
    //go through the names that will be printed and find the maximum
    for (int i = 0; i < numberOfEntriesToPrintInGraph; i++)
    {
        if (allMaximumNodes[i] != NULL && strlen(allMaximumNodes[i]->name) > maxmimumLength)
        {
            maxmimumLength = strlen(allMaximumNodes[i]->name);
        }
    }

    //retur the maximum
    return maxmimumLength;
}

//this prints the top and the last line of each entry in the graph, the one below the name and above the name
void printTopAndLastLineOfEntry(int barLength, int maximumNameLength)
{
    //get the number of spaces to keep after the name, changes with the longest name
    int numberOfSpacesToKeep = maximumNameLength + 2;
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
void printMiddleLineOfEntry(char *name, long long data, int barLength, int maximumNameLength)
{
    //print the name
    printf(" %s", name);

    //print the correct number of spaces
    int numberOfSpaces = maximumNameLength - strlen(name) + 1;
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
    printf("%lld", data);

    //goto next line
    puts("");
}

//this prints the empty line after each entry in the graph
void printEmptyLineInGraph(int maxLength)
{
    //barlength is zero when its a empty line.
    printTopAndLastLineOfEntry(0, maxLength);
}

//this prints the last line of the graph, the line with the corner
void printLastLineOfGraph(int maxNameLength)
{
    //print the number of spaces before the corner
    int numberOfSpacesToKeep = maxNameLength + 2;
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
int getBarLength(long long currentData, int maximumNameLength)
{
    long long largestNumber;
    int currentNumber;

    largestNumber = allMaximumNodes[0]->data;
    currentNumber = currentData;

    //first find the maximum bar length, this changes because the name length changes and the maximum graph width is 80
    int numberOfSpacesToKeep = maximumNameLength + 2;
    int numberOfBars = 80 - numberOfSpacesToKeep - 1;
    int maximumBarLength = numberOfBars - getLengthOfNumber((int)largestNumber);

    //if its scaled
    if (isScaled)
    {
        //multiply the maximum bar length by the percentage of the curernt index
        int numberOfBarsInThisEntry = (int)(maximumBarLength * ((float)currentNumber) / largestNumber);

        return numberOfBarsInThisEntry;
    }
    else
    {
        //if not scaled

        //find the sum of all the values
        long long sumOfValues = 0;
        record *tempNode = head;
        while (tempNode != NULL)
        {
            sumOfValues += tempNode->data;
            tempNode = tempNode->nextRecord;
        }

        //get the number of bars per unit, this way, the whole bar means the sum of all the entries
        float numberOfBarsPerUnit = maximumBarLength / (float)sumOfValues;
        //get the number of bars for this record
        int numberOfBarsForThisEntry = (float)(numberOfBarsPerUnit * currentNumber);
        // printf("%lf", numberOfBarsPerUnit * chosenArray[index]);
        // printf("%d", numberOfBarsForThisEntry);

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

//creates a new node and returns a pointer to that node
record *createNewRecord(char *nameSTR)
{
    //allocate space
    record *newNode = (record *)malloc(sizeof(record));

    //add this new element to the other linked list too
    int index = (int)nameSTR[0];
    if (array[index] == NULL)
    { //if there are no names starting from that, this is the first one
        namesStartingWithChar *newName = (namesStartingWithChar *)malloc(sizeof(namesStartingWithChar));
        newName->record = newNode;
        newName->nextName = NULL;
        array[index] = newName;
    }
    else
    { // if there are exisitng ones, insert this name at head
        namesStartingWithChar *newName = (namesStartingWithChar *)malloc(sizeof(namesStartingWithChar));
        newName->record = newNode;
        newName->nextName = array[index];
        array[index] = newName;
    }

    //allocate space for a name
    char *namePointer = (char *)malloc(sizeof(char) * strlen(nameSTR) + 1);
    strcpy(namePointer, nameSTR);
    newNode->name = namePointer; //point it the name

    //set other things to zero
    newNode->data = 0;
    newNode->nextRecord = NULL;

    //return the pointer of this new node
    return newNode;
}
