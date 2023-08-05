CovidDB: assignment4.o CovidDB.o
	g++ -o HashTest assignment4.o CovidDB.o

assignment4.o: main.cpp CovidDB.h
	g++ -c -Wall -Werror -pedantic -std=c++11 -o assignment4.o main.cpp

CovidDB.o: CovidDB.cpp CovidDB.h
	g++ -c -Wall -Werror -pedantic -std=c++11 CovidDB.cpp