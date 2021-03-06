#include <getopt.h>

//#ifndef CLI
//#define CLI

static struct option long_options[] = {
    {"version", no_argument, 0, 'v'},
    {"help", no_argument, 0, 'h'},
    {"port", required_argument, 0, 'p'}
};

struct config {
    int port;
};

static int version_flag;
void print_usage();
void print_version();
struct config getOptions(int argc, char **argv);

//#endif 


