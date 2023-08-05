// Jomikael Ruiz
// CovidDB.cpp
// May 9th, 2023
// Purpose: provide implementation for DataEntry and CovidDB class to allow
// Hash Table and Hash Function to properly function

#include "CovidDB.h"
#include <iostream>
using namespace std;

const string SAME = "same";

// function used in insert to see which date is the latest date
string compareDates(string country1, string country2) {
    Date first(country1);
    Date second(country2);
    // comparing years
    if(second.year > first.year) {
        return country2;
    } else if(first.year > second.year) {
        return country1;
    } else {
        // if years are equal, compare months
        if(second.month > first.month) {
            return country2;
        } else if(first.month > second.month) {
            return country1;
        } else {
            // if months are equal, compare days
            if(second.day > first.day) {
                return country2;
            } else if(first.day > second.day) {
                return country1;
            } else {
                // if everything is equal, return a const
                return SAME;
            }
        }
    }
}

// constructor for DataEntry
DataEntry::DataEntry(string date, string country, int c_cases, int c_deaths) {
    this->date = date;
    this->country = country;
    this->c_cases = c_cases;
    this->c_deaths = c_deaths;
}

// getter functions for DataEntry
string DataEntry::getDate() {
    return this->date;
}

string DataEntry::getCountry() {
    return this->country;
}

int DataEntry::getCases() {
    return this->c_cases;
}

int DataEntry::getDeaths() {
    return this->c_deaths;
}

// setter functions for DataEntry
void DataEntry::addCases(int cases) {
    this->c_cases += cases;
}

void DataEntry::addDeaths(int deaths) {
    this->c_deaths += deaths;
}

void DataEntry::updateDate(string newDate) {
    this->date = newDate;
}

void DataEntry::printEntry() {
    cout << date << ", " << country << ", "
         << c_cases << ", " << c_deaths << endl;
}

// CovidDB constructor
CovidDB::CovidDB() {
    tableSize = 17;
    vector<DataEntry *> emptyVector;
    for(int i = 0; i < tableSize; i++) {
        hashTable.push_back(emptyVector);
    }
}

// hash function using implementation from assignment
// takes in country name and converts it into a hash index
int CovidDB::hash(string country) {
    int sum = 0;
    for(int i = 0; i < (int)country.size(); i++) {
        sum += ((i+1) * (int)country[i]);
    }
    sum = sum % tableSize;
    return sum;
}

// add function that uses hash() to input a value into the hash table
bool CovidDB::add(DataEntry * entry) {
    // gets the country from input and hashes the key
    string country = entry->getCountry();
    int hashIndex = hash(country);
    int index = 0;
    string temp = "";
    // if the vector at hashIndex is empty, push back into vector
    if(hashTable[hashIndex].empty()) {
        hashTable[hashIndex].push_back(entry);
    } else {
        // linear search on vector
        while(index < (int)hashTable[hashIndex].size()
                && hashTable[hashIndex][index]->getCountry() != entry->getCountry()) {
            index++;
        }
        // if vector does not have current record, push back record
        if(index >= (int)hashTable[hashIndex].size()) {
            hashTable[hashIndex].push_back(entry);
        }
        // current record is found in vector, must compare dates
        else {
            temp = compareDates(hashTable[hashIndex][index]->getDate(), entry->getDate());
            // if the hashtable date is greater, return false;
            if(temp == hashTable[hashIndex][index]->getDate()) {
                return false;
            } else if(temp == SAME) {
                // return false if record has the same date
                return false;
            } else {
                // if the entry date is greater, update variables
                hashTable[hashIndex][index]->addCases(entry->getCases());
                hashTable[hashIndex][index]->addDeaths(entry->getDeaths());
                hashTable[hashIndex][index]->updateDate(entry->getDate());
            }
        }
    }
    // returns true to show successful input into table
    return true;
}

// get function to retrieve a value in the hash table based on country
DataEntry * CovidDB::get(string country) {
    // hashes country key to get index
    int hashIndex = hash(country);
    int index = 0;
    // if the vector is empty, value is not found
    if(hashTable[hashIndex].empty()) {
        return nullptr;
    } else {
        // linear search in the vector
        while(index < (int)hashTable[hashIndex].size()
              && hashTable[hashIndex][index]->getCountry() != country) {
            index++;
        }
        // if initial condition is false, then return nullptr since value not found
        if(index >= (int)hashTable[hashIndex].size()) {
            return nullptr;
        } else {
            // return found value
            return hashTable[hashIndex][index];
        }
    }
}

// remove function to remove a value from the hash table
void CovidDB::remove(string country) {
    // hashes country key to get index
    int hashIndex = hash(country);
    int index = 0;
    // linear search on vector
    while(index < (int)hashTable[hashIndex].size()
          && hashTable[hashIndex][index]->getCountry() != country) {
        index++;
    }
    // if country not found, return from function
    if(index >= (int)hashTable[hashIndex].size()) {
        return;
    } else {
        // once found, process and delete data and delete from vector
        delete hashTable[hashIndex][index];
        hashTable[hashIndex].erase(hashTable[hashIndex].begin() + index, hashTable[hashIndex].begin() + index + 1);
    }
}

// display function to print out table
void CovidDB::displayTable() {
    for(int i = 0; i < tableSize; i++) {
        if(!this->hashTable[i].empty()) {
            for(int j = 0; j < (int)hashTable[i].size(); j++) {
                cout << hashTable[i][j]->getDate() << ", " << hashTable[i][j]->getCountry() << ", "
                     << hashTable[i][j]->getCases() << ", " << hashTable[i][j]->getDeaths() << endl;
            }
        }
    }
}
