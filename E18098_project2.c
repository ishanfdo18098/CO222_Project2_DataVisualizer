/*
CO222: Programming Methodology - Project 2
Meeting Data Visualizer

Author : Fernando K.A. Ishan - E/18/098
*/
#include <stdio.h>
#include <getopt.h>

int main(int argc, char **argv)
{
    char optionEntered;
    opterr = 0;
    // ref - https://stackoverflow.com/a/44371579
    while ((optionEntered = getopt(argc, argv, "l:mtp")) != -1)
    {
        switch (optionEntered)
        {
        case 'l':
            printf("l entered\n");
            break;
        case 'm':
            printf("m entered\n");
            break;
        case 't':
            printf("t entered\n");
            break;
        case 'p':
            printf("p entered\n");
            break;
        case '?':
            printf("%c unkown option entered %s\n", optionEntered, optarg);
            break;
        default:
            printf("default\n");
        }
    }

    for (int index = optind; index < argc; index++)
    {
        printf("Non-option argument %s\n", argv[index]);
    }

    return 0;
}
