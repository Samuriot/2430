//
// Created by Jomikael Ruiz on 4/28/23.
//

#include <vector>
#include <string>
#include <iostream>
using namespace std;

const int EXITVAL = 6;
const int CONTINUE = 1;

struct Pet {
    string name;
    int arrival;
    Pet(string name, int arrival) {
        this->name = name;
        this->arrival = arrival;
    }
};

class PetHeap {
    private:
        vector<Pet *> petHeap;
        void percolateUp(int index);
        void percolateDown(int index);
        void deleteMin();
        Pet * peekMin();
    public:
        PetHeap() {
            petHeap = vector<Pet *>();
        }
        void insert(Pet * pet);
        void adoptOldestPet();
        int numPets();
        void displayPets();
};

void swapPet(Pet *& pet, Pet *& petTwo);
int displayMenu();
int evaluateInput(int input, PetHeap & shelter);
void runTests(PetHeap & shelter);
void startShelter(PetHeap & shelter);
void adoptFive(PetHeap & shelter);

void PetHeap::percolateUp(int index) {
    int parentIndex = (index - 1) / 2;
    if(index == 0) {
        return;
    }
    if(petHeap[index]->arrival > petHeap[parentIndex]->arrival) {
        return;
    } else {
        swapPet(petHeap[index], petHeap[parentIndex]);
        percolateUp(parentIndex);
    }
}

void PetHeap::percolateDown(int index) {
    int leftIndex = ((2*index) + 1);
    int rightIndex = ((2*index) + 2);
    if(leftIndex >= (int)petHeap.size()) {
        return;
    }
    if(rightIndex >= (int)petHeap.size()
        && petHeap[index]->arrival < petHeap[leftIndex]->arrival) {
        return;
    }
    if(petHeap[index]->arrival < petHeap[leftIndex]->arrival
            && petHeap[index]->arrival < petHeap[rightIndex]->arrival) {
        return;
    } else {
        if(petHeap[index]->arrival > petHeap[leftIndex]->arrival && petHeap[leftIndex]->arrival < petHeap[rightIndex]->arrival) {
            swapPet(petHeap[index], petHeap[leftIndex]);
            percolateDown(leftIndex);
        } else {
            swapPet(petHeap[index], petHeap[rightIndex]);
            percolateDown(rightIndex);
        }
    }
}

void PetHeap::deleteMin() {
    swapPet(this->petHeap[0], this->petHeap[numPets() - 1]);
    this->petHeap.pop_back();
    percolateDown(0);
}

Pet * PetHeap::peekMin() {
    if(!petHeap.empty()) {
        return this->petHeap[0];
    } else {
        return nullptr;
    }
}

void PetHeap::insert(Pet * pet) {
    this->petHeap.push_back(pet);
    int index = (int)this->petHeap.size() - 1;
    percolateUp(index);
}

void PetHeap::adoptOldestPet() {
    Pet * oldest = nullptr;
    oldest = peekMin();
    if(oldest) {
        deleteMin();
        cout << "You adopted: " << oldest->name << ", arrival " << oldest->arrival << endl;
        delete oldest;
        oldest = nullptr;
    } else {
        cout << "Sorry, there are no more pets in the shelter." << endl;
    }
}

int PetHeap::numPets() {
    return petHeap.size();
}

void PetHeap::displayPets() {
    if(this->petHeap.empty()) {
        cout << "Sorry, the shelter is empty" << endl;
    }
    for(int i = 0; i < (int)this->petHeap.size(); i++) {
        cout << petHeap[i]->name << ", arrival " << petHeap[i]->arrival << endl;
    }
}

int main() {
    PetHeap shelter;
    int input = CONTINUE;
    while(input != EXITVAL) {
        input = displayMenu();
        input = evaluateInput(input, shelter);
    }
    return 0;
}

void swapPet(Pet *& pet, Pet *& petTwo) {
    Pet * temp = pet;
    pet = petTwo;
    petTwo = temp;
}

int displayMenu() {
    int input;
    cout << endl << "Welcome to Lab 4 on Basic Heap Operations. What would you like to test?" << endl;
    cout << "1.\t Insert Pet" << endl;
    cout << "2.\t Adopt Pet" << endl;
    cout << "3.\t Numbet of Pets" << endl;
    cout << "4.\t Display Pets" << endl;
    cout << "5.\t runTests" << endl;
    cout << "6.\t Exit" << endl;
    cin >> input;
    return input;
}

void startShelter(PetHeap & shelter) {
    cout << "Inserting 10 pets into the shelter" << endl;
    shelter.insert(new Pet("Jett", 10));
    shelter.insert(new Pet("Reyna", 12));
    shelter.insert(new Pet("Yoru", 2));
    shelter.insert(new Pet("Raze", 4));
    shelter.insert(new Pet("Cypher", 7));
    shelter.insert(new Pet("Phoenix", 5));
    shelter.insert(new Pet("Skye", 1));
    shelter.insert(new Pet("Harbor", 30));
    shelter.insert(new Pet("KAYO", 11));
    shelter.insert(new Pet("Fade", 9));
    cout << "Insertion completed" << endl << endl;
}

void adoptFive(PetHeap & shelter) {
    shelter.adoptOldestPet();
    shelter.adoptOldestPet();
    shelter.adoptOldestPet();
    shelter.adoptOldestPet();
    shelter.adoptOldestPet();
}


void runTests(PetHeap & shelter) {
    startShelter(shelter);
    cout << "Current shelter status in level order: " << endl;
    shelter.displayPets();
    cout << endl;
    adoptFive(shelter);
    cout << endl;
    cout << "Current shelter status in level order: " << endl;
    shelter.displayPets();
    cout << endl;
    adoptFive(shelter);
    cout << endl << "Attempted an adoption when heap is empty: " << endl;
    shelter.adoptOldestPet();
}

int evaluateInput(int input, PetHeap & shelter) {
    string tempName;
    int tempVal;
    switch(input) {
        case 1:
            cout << "Enter a name: ";
            cin >> tempName;
            cout << "Enter an arrival integer: ";
            cin >> tempVal;
            shelter.insert(new Pet(tempName, tempVal));
            break;
        case 2:
            shelter.adoptOldestPet();
            break;
        case 3:
            tempVal = shelter.numPets();
            cout << "The shelter heap has " << tempVal << " pets." << endl;
            break;
        case 4:
            shelter.displayPets();
            break;
        case 5:
            runTests(shelter);
            break;
        case 6:
            return EXITVAL;
    }
    return CONTINUE;
}