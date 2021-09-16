/*
CO222: Programming Methodology - Project 2
Meeting Data Visualizer

Author : Fernando K.A. Ishan - E/18/098
*/
#include <stdio.h>
#include <getopt.h>

int main(int argc, char **argv)
{
    // https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html
    int optionEntered;
    while (1)
    {
        static struct option long_options[] =
            {
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

        switch (optionEntered)
        {
        case 'l':
            printf("option -l with %s\n", optarg);
            break;

        case 'm':
            puts("option -m");
            break;

        case 't':
            printf("option -t\n");
            break;

        case 'p':
            printf("option -p\n");
            break;

        case 's':
            printf("option --scaled\n");
            break;

        case '?':
            /* getopt_long already printed an error message. */
            break;
        }
    }

    for (int index = optind; index < argc; index++)
    {
        printf("Non-option argument %s\n", argv[index]);
    }

    return 0;
}
