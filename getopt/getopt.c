#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int aflag = 0;
    int bflag = 0;
    char *cvalue = NULL;
    int index;
    int option;

    while((option = getopt(argc, argv, "abc:")) != -1) {
        switch(option) {
            case 'a':
                aflag = 1;
                break;
            case 'b':
                bflag = 1;
                break;
            case 'c':
                cvalue = optarg;
                break;
            case '?':
                printf("Unknown option %c\n", optopt);
            default:
                abort();
        }
    }

    printf ("aflag = %d, bflag = %d, cvalue = %s\n", aflag, bflag, cvalue);

    for (index = optind; index < argc; index++) {
        printf ("Non-option argument %s\n", argv[index]);
    }

    return 0;
}
