//#include <my_global.h>
#include "stdio.h"
#include <string.h>
#include <mysql.h>

struct mysqlCredentials {
    const char *host;
    const char *login;
    const char *password;
};

void process_result_set (MYSQL_RES *res_set);
void query(MYSQL *mysql, char *query);
MYSQL* do_connect();

MYSQL* do_connect() {
    MYSQL *mysql = mysql_init(NULL);
    //MYSQL *mysql = NULL;
    //mysql = mysql_init(mysql);

    if(mysql == NULL) {
        fprintf(stderr, "%s\n", mysql_error(mysql));
        exit(1);
    }

    // init as pointer structure
    struct mysqlCredentials *mc;
    mc = (struct mysqlCredentials*) malloc(sizeof(struct mysqlCredentials));

    mc->host = "192.168.1.19";
    mc->login = "root";
    mc->password = "root";
    
    printf("host: %s, login: %s password: %s\n", mc->host, mc->login, mc->password);

    if(mysql_real_connect(mysql, mc->host, mc->login, mc->password, NULL, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(mysql));
        mysql_close(mysql);
        
        exit(1);
    }

    free(mc);
    
    printf("connected to mysql %s\n", mc->host);
    printf("Mysql client version : %s\n", mysql_get_client_info());

    return mysql;
}

void query(MYSQL *mysql, char *query) {
    if (mysql_query(mysql, query)) {
      printf("Query failed: %s\n", mysql_error(mysql));
    } else {
      MYSQL_RES *result = mysql_use_result(mysql);

      if (result) {
        printf("Query : %s\n", query);
        process_result_set(result);
        mysql_free_result(result);
      } else {
        printf("Couldn't get results set: %s\n", mysql_error(mysql));
      }
    }
}

void process_result_set (MYSQL_RES *res_set){
  MYSQL_FIELD		*field;
  MYSQL_ROW		    row;
  unsigned int	i, col_len;
  
  while ((row = mysql_fetch_row (res_set)) != NULL){
    mysql_field_seek (res_set, 0);
    
    for (i = 0; i < mysql_num_fields (res_set); i++){
      field = mysql_fetch_field (res_set);
      printf ("%s |",row[i]);
    }
    printf("\n");
  }
  printf ("%lu rows returned\n", (unsigned long) mysql_num_rows (res_set));
}


int main(int argc, char **argv) {
    /*MYSQL *mysql = mysql_init(NULL);

    if(mysql == NULL) {
        fprintf(stderr, "%s\n", mysql_error(mysql));
        exit(1);
    }

    // init as pointer structure
    struct mysqlCredentials *mc;
    mc = (struct mysqlCredentials*) malloc(sizeof(struct mysqlCredentials));

    mc->host = "192.168.1.19";
    mc->login = "root";
    mc->password = "root";
    
    printf("host: %s, login: %s password: %s\n", mc->host, mc->login, mc->password);

    //mysql --protocol tcp
    //MYSQL_OPT_PROTOCOL mysql_protocol_type
    //protocol={TCP|SOCKET|PIPE|MEMORY}

    //mysql_options(mysql, MYSQL_READ_DEFAULT_FILE, (void *)"./my.cnf");
    //if(mysql_real_connect(mysql, "localhost", "root", "root", NULL, 0, NULL, 0) == NULL) {        
    //if(mysql_real_connect(mysql, NULL, NULL, NULL, NULL, 0, NULL, CLIENT_FOUND_ROWS) == NULL) {

    if(mysql_real_connect(mysql, mc->host, mc->login, mc->password, NULL, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(mysql));
        mysql_close(mysql);
        
        exit(1);
    }
    
    printf("connected to mysql %s\n", mc->host);
    printf("Mysql client version : %s\n", mysql_get_client_info());*/

    MYSQL *mysql = do_connect();
    query(mysql, "SELECT VERSION()");

    // Do stuff

    /*if(mysql_query(conn, "CREATE DATABASE testdb")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }*/

    //free(mysql);
    mysql_close(mysql);
    //exit(0);
    return EXIT_SUCCESS;
}
