shelterTest: main.o shelterTest.o
	g++ -o shelterTest main.o shelterTest.o

main.o: main.cpp ShelterBST.h
	g++ -c -Wall -Werror -pedantic -std=c++11 main.cpp

shelterTest.o: ShelterBST.cpp ShelterBST.h
	g++ -c -Wall -Werror -pedantic -std=c++11 ShelterBST.cpp