#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <config.h>
#include <ini.h>

static int handler(void* conf, const char* section, const char* name, const char* value) {
    config* pconfig = (config*)conf;

    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if (MATCH("http", "port")) {
        pconfig->port = atoi(value);
    } else if (MATCH("http", "host")) {
        pconfig->host = strdup(value);
    } else if (MATCH("http", "target")) {
        pconfig->target = strdup(value);
    } else {
        return 0; 
    }
    return 1;
}

config getIniConfig(char* file) {
    config conf;

    if (ini_parse(file, handler, &conf) < 0) {
        printf("Can't load '%s'\n", file);
    }

    return conf;
}

/*void printConfig(config conf) {    
    printf("Config loaded from 'etc/conf.ini': port=%d, host=%s, target=%s\n", conf.port, conf.host, conf.target);
}*/
