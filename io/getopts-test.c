#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void printHelp();

int main(int argc, char **argv) {

    int aflag = 0;
    int bflag = 0;
    char *cvalue = NULL;
    int index;
    int c;

    opterr = 0;

    while ((c= getopt(argc, argv, "abhc:")) != -1) {
        switch (c) {
            case 'a':
                aflag = 1;
                break;
            case 'b':
                bflag = 1;
                break;
            case 'c':
                cvalue = optarg;
                break;
            case 'h':
                printHelp();
                break;
            case '?':
                //printHelp();
                return 1;
            default:
                abort();
        }
    }

    printf ("aflag = %d, bflag = %d, cvalue = %s\n", aflag, bflag, cvalue);

    for(index = optind; index < argc; index++) {
        printf ("Non-option argument %s\n", argv[index]);
    }

    return 0;
}

void printHelp() {
    printf("Usage : getops-test -a <flag> -b <flag> -c <string>");
}