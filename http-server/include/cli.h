#include <getopt.h>
#include <config.h>

#ifndef CLI
#define CLI

static struct option long_options[] = {
    {"version", no_argument, 0, 'v'},
    {"help", no_argument, 0, 'h'},
    {"port", required_argument, 0, 'p'},
    {"host", required_argument, 0, 'h'},
    {"target", required_argument, 0, 't'},
    {"config", required_argument, 0, 'c'}
};

static int version_flag;
void print_usage();
void print_version();
config getOptions(int argc, char **argv);

#endif 


