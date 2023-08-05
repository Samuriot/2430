// Jomikael Ruiz
// main.cpp
// May 9th, 2023
// Purpose: Driver program that provides UI to work with hashTable function
// and reads in data from a specific csv file

#include "CovidDB.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// constants
const string FILENAME = "WHO-COVID-data.csv";
const char COMMA = ',';
const int CONTINUE = 1;
const int END = -1;

// function declarations
// takes in a CovidDB variable and fills it with data from the csv
void fillHashTable(CovidDB & table);
// display a UI menu and allows user to choose a value
int displayMenu();
// takes in userInput and evaluates their choice
int evaluateInput(int input, CovidDB & table);
// adds a new value into CovidDB
void addValue(CovidDB & table);

int main() {
    CovidDB hashTable;
    int input = CONTINUE;
    // while loop to maintain functionality until user exits
    while(input != END) {
        input = displayMenu();
        input = evaluateInput(input, hashTable);
    }
    return 0;
}

void fillHashTable(CovidDB & table) {
    // variables to fill table
    fstream inFile;
    string line;
    string date, country, token;
    int cases, deaths;
    // opens file
    inFile.open(FILENAME);
    if(inFile.fail()) {
        cout << "File Read Failed. Exit Program.";
        return;
    }
    // ignores first line of csv
    getline(inFile, line);
    // while loop to read values into table
    while(getline(inFile, line)) {
        stringstream ss(line);
        getline(ss, date, COMMA);
        getline(ss, country, COMMA);
        getline(ss, token, COMMA);
        cases = stoi(token);
        getline(ss, token, COMMA);
        deaths = stoi(token);
        table.add(new DataEntry(date, country, cases, deaths));
    }
    // exits file
    inFile.close();
}

int displayMenu() {
    int temp;
    cout << endl << "Covid Tracker" << endl;
    cout << "Please choose an operation: " << endl;
    cout << "1.\tCreate the initial Hash Table." << endl;
    cout << "2.\tAdd a data entry." << endl;
    cout << "3.\tGet a data entry." << endl;
    cout << "4.\tRemove a data entry." << endl;
    cout << "5.\tDisplay Hash Table." << endl;
    cout << "6.\tRehash the Hash Table" << endl;
    cout << "7.\tExit Program." << endl;
    cin >> temp;
    return temp;
}

void addValue(CovidDB & table) {
    string date, country;
    int cases, deaths;
    bool success;
    // asks users for values to store in table
    cout << "Please enter a date: ";
    cin.ignore();
    getline(cin, date);
    cout << "Please enter a country: ";
    getline(cin, country);
    cout << "Please enter the number of cases: ";
    cin >> cases;
    cout << "Please enter the number of deaths: ";
    cin >> deaths;
    success = table.add(new DataEntry(date, country, cases, deaths));
    if(!success) {
        cout << "Value could not be placed into the table." << endl;
    } else {
        cout << "Data successfully placed into the table." << endl;
    }
}

int evaluateInput(int input, CovidDB & table) {
    string date, country;
    DataEntry * temp;
    // switch case to evaluate input
    switch(input) {
        case 1:
            fillHashTable(table);
            break;
        case 2:
            addValue(table);
            break;
        case 3:
            cout << "Please enter a country's name: ";
            cin.ignore();
            getline(cin, country);
            temp = table.get(country);
            if(!temp) {
                cout << "Error, Country Not Found in Table." << endl;
            } else {
                temp->printEntry();
            }
            break;
        case 4:
            cout << "Please enter a country's name: ";
            cin.ignore();
            getline(cin, country);
            table.remove(country);
            break;
        case 5:
            table.displayTable();
            break;
        case 6:
            table.resizeTable();
            fillHashTable(table);
            break;
        case 7:
            return END;
    }
    return CONTINUE;
}
