// Jomikael Ruiz
// CovidDB.h
// May 9th, 2023
// Purpose: provide definitions for Date, DataEntry, and CovidDB

#ifndef COVIDDB_H
#define COVIDDB_H
#include <string>
#include <vector>

// Date struct to correctly analyze dates
struct Date {
    int month;
    int day;
    int year;
    // constructor for Date
    Date(std::string date) {
        std::string temp = "";
        // takes in the string and converts it into month, day, and year variables
        for(int i = 0; i < (int)date.size(); i++) {
            if(date[i] == '/') {
                if(i <= 2) {
                    month = std::stoi(temp);
                    temp = "";
                } else if(i <= 5) {
                    day = std::stoi(temp);
                    temp = "";
                }
            } else {
                temp += date[i];
            }
        }
        year = std::stoi(temp);
    }
};

// DataEntry class to handle data to be placed in CovidDB
class DataEntry {
    private:
        // variables for DataEntry
        std::string date;
        std::string country;
        int c_cases;
        int c_deaths;
    public:
        // constructor
        DataEntry(std::string date, std::string country, int c_cases, int c_deaths);
        // getter functions
        std::string getDate();
        std::string getCountry();
        int getCases();
        int getDeaths();
        // adder/setter functions
        void addCases(int cases);
        void addDeaths(int deaths);
        void updateDate(std::string newDate);
        void printEntry();
};

// CovidDB class to store data in a hashTable
class CovidDB {
    private:
        // variables
        std::vector<std::vector<DataEntry *>> hashTable;
        int tableSize;
    public:
        // constructor
        CovidDB();
        // destructor
        ~CovidDB();
        // add function that adds a DataEntry pointer into the hashTable
        bool add(DataEntry * entry);
        // get function that takes a country as input and finds it in the hashTable
        DataEntry * get(std::string country);
        // remove function that takes a country as input and removes it from hashTable
        void remove(std::string country);
        // hash function to get the index in a hashTable
        int hash(std::string country);
        // display function to display the entire hashTable
        void displayTable();
        // resizes hashtable
        void resizeTable();
};


#endif //COVIDDB_H
