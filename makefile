app : main.o VspdToMySQL.o
	g++ main.o VspdToMySQL.o -o app `mysql_config --cflags --libs` 
main.o : main.cpp VspdToMySQL.h VspdToMySQL.cpp
	g++ -c main.cpp  `mysql_config --cflags --libs` -std=c++11
VspdToMySQL.o : VspdToMySQL.cpp VspdToMySQL.h
	g++ -c VspdToMySQL.cpp  `mysql_config --cflags --libs` -std=c++11
CLEAN:
	rm -rf *.o
