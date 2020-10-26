#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

static int verbose_flag;
static int brief_flag;

void print_usage() {
    printf("Usage: rectangle [ap] -l num -b num\n");
}

int main(int argc, char **argv) {
    int opt;

    static struct option long_options[] = {
        {"verbose", no_argument, &verbose_flag, 1},
        {"brief", no_argument, &brief_flag, 0},
        {"add", no_argument, 0, 'a'},
        {"append", no_argument, 0, 'b'},
        {"delete", required_argument, 0, 'd'},
        {"create", required_argument, 0, 'c'},
        {"file", required_argument, 0, 'f'},
        {0,0,0,0}
    };

    int option_index = 0;

    while ((opt = getopt_long(argc, argv, "abc:d:f:", long_options, &option_index)) != -1) {
        
        switch(opt) {
            case 0:
                break;
            case 'a':
                puts("option -a\n");
                break;
            case 'b':
                puts("option -b\n");
                break;
            case 'c':
                printf("option -d with value %s\n", optarg);
                break;
            case 'd':
                printf("option -d with value %s\n", optarg);
                break;
            case 'f':
                printf("option -f with value %s\n", optarg);
                break;
            case '?':
                break;
            default: print_usage(); 
                exit(EXIT_FAILURE);
        }
    }

    if(verbose_flag) {
        puts("verbose flag is set");
    }

    if(brief_flag) {
        puts("brief flag is set");
    }

    if(optind < argc) {
        printf("non-option ARGV-elements:");
        while(optind < argc) {
            printf("%s", argv[optind++]);
        }
        putchar('\n');
    }

    exit(0);
}