#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <cli.h>

struct config getOptions(int argc, char **argv) {
    int opt;
    int option_index = 0;

    struct config conf;
    conf.port = 3000;

    while ((opt = getopt_long(argc, argv, "vhp:", long_options, &option_index)) != -1) {
        switch(opt) {
            case 0:
                break;
            case 'v':
                print_version();
                exit(EXIT_SUCCESS);
                break;
            case 'h':
                print_version();
                print_usage();
                exit(EXIT_SUCCESS);
                break;
            case 'p':                
                conf.port = atoi(optarg);                
                break;
            case '?':
                break;
                exit(EXIT_FAILURE);
            default: print_usage(); 
                exit(EXIT_FAILURE);
        }
    }

    if(optind < argc) {
        printf("non-option ARGV-elements:");
        while(optind < argc) {
            printf("%s", argv[optind++]);
        }
        putchar('\n');

        exit(EXIT_FAILURE);
    }

    return conf;
}

void print_usage() {
    printf("Usage: tcp-server\n");
}

void print_version() {
    printf("version 1.0 \n");
}
