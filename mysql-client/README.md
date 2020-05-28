# C Mysql client

vagrant up
sudo apt install libmysqlclient-dev
sudo apt install build-essential
sudo apt install mysql-server

sudo mysql

ALTER USER 'root'@'localhost' IDENTIFIED BY 'root';

use mysql;
ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'root';
FLUSH PRIVILEGES;

gcc version.c -o bin/version  `mysql_config --cflags --libs`

mysql_config --libs
mysql_config --cflags

gcc createdb.c -o bin/createdb -std=c99  `mysql_config --cflags --libs` 

gcc createdb.c -o bin/createdb $(mysql_config --cflags) $(mysql_config --libs)

gcc createdb.c -o bin/createdb -I/usr/include/mysql  -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -lrt -latomic -lssl -lcrypto -ldl

/usr/include/mysql/