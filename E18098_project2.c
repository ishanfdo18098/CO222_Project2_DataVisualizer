/*
CO222: Programming Methodology - Project 2
Meeting Data Visualizer

Notes:
1) -l or --length both works. similar to that --meeting --time --participants work too.


To do:
-Invalid option [%s], do this outside getopt as the whole string needs to be printed

Author : Fernando K.A. Ishan - E/18/098
*/
#include <stdio.h>
#include <getopt.h> //option parsing
#include <stdlib.h> //aoti()
#include <string.h> //strlen()
#include <ctype.h>  //isdigit()

void parseOptions(int argc, char **argv); // option parsing
void printUsage();                        // print how to use the program

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

    //file names
    for (int index = optind; index < argc; index++)
    {
        char *currentFileName = &argv[index][0];

        printf("current filename: %s\n", currentFileName);

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
            continue;
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
            printf("option -l with %s\n", optarg);

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

            printf("-l changed to %d\n", numberOfElementsInGraph);
            break;
        case 'm':
            puts("option -m");
            isMeeting = 1;
            break;
        case 't':
            printf("option -t\n");
            isTime = 1;
            break;
        case 'p':
            printf("option -p\n");
            isParticipants = 1;
            break;
        case 's':
            printf("option --scaled\n");
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