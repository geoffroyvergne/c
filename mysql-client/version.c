#include <my_global.h>
#include <mysql.h>

int main(int argc, char **argv) {

    printf("Mysql client version : %s\n", mysql_get_client_info());
    exit(0);
}