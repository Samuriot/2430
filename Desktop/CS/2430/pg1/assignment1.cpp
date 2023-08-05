// Jomikael Ruiz
// assignment1.cpp
// March 31st, 2023
// Purpose: Program replicating the functions of an animal shelter that
// utilizes STL definition of Queue to act as an adoption center with
// error handling when the queue is empty and there are no other animals left

#include <iostream>
#include <queue>
using namespace std;

// constants
const bool DOG = true;
const bool CAT = false;
const int END = 6;
const int CONTINUE = 1;

// Pet Class with properties that show its name and type of pet and also has getter functions
class Pet {
    private:
        string name;
        bool typeOfPet;
    public:
        Pet(string name, bool type);
        string getName() const;
        bool getType() const;
};

// Pet Class Constructor
Pet::Pet(string name, bool type) {
    this->name = name;
    this->typeOfPet = type;
}

// Pet Class name getter function
string Pet::getName() const {
    return name;
}

// Pet Class type getter function
bool Pet::getType() const {
    return typeOfPet;
}

// pushes a created dog Pet into queue
void addDog(queue<Pet *> & shelter, string name);
// pushes a created cat Pet into queue
void addCat(queue<Pet *> & shelter, string name);
// pops the oldest dog Pet from the queue and returns the pointer
Pet * adoptDog(queue<Pet *> & shelter);
// pops the oldest cat Pet from the queue and returns the pointer
Pet * adoptCat(queue<Pet *> & shelter);
// pops the oldest Pet from the queue and returns the pointer
Pet * adoptAny(queue<Pet *> & shelter);
// prints the menu options and takes user input
int printSelection();
// evaluates user input based on menu selection
int evaluateSelection(queue<Pet *> & shelter, int input);

int main() {
    queue<Pet *> animalShelter;
    int selection, endStatement = CONTINUE;
    while(endStatement != END) {
        selection = printSelection();
        endStatement = evaluateSelection(animalShelter, selection);
    }
    return 0;
}

int printSelection() {
    int selection;
    cout << endl;
    cout << "Welcome to the animal shelter. What would you like to do?" << endl;
    cout << "1.\tAdd a CAT to the shelter" << endl;
    cout << "2.\tAdd a DOG to the shelter" << endl;
    cout << "3.\tAdopt a CAT from the shelter" << endl;
    cout << "4.\tAdopt a DOG from the shelter" << endl;
    cout << "5.\tAdopt any animal from the shelter" << endl;
    cout << "6.\tExit" << endl;
    cin >> selection;
    return selection;
}

void addDog(queue<Pet *> & shelter, string name) {
    shelter.push(new Pet(name, DOG));
}

void addCat(queue<Pet *> & shelter, string name) {
    shelter.push(new Pet(name, CAT));
}

Pet * adoptAny(queue<Pet *> & shelter) {
    // if shelter is empty, return nullptr
    if(shelter.empty()) {
        return nullptr;
    } else {
        // get first pet pointer in the queue
        Pet *animal = shelter.front();
        shelter.pop();
        return animal;
    }
}

Pet * adoptCat(queue<Pet *> & shelter) {
    // if shelter is empty, return nullptr
    if(shelter.empty()) {
        return nullptr;
    } else {
        // checks first pet in queue if it is a cat
        Pet *animal = shelter.front();
        if(!animal->getType()) {
            shelter.pop();
            return animal;
        } else if(shelter.front() == shelter.back()) {
            // checks if there is only one pet in the queue and returns if true
            return nullptr;
        } else {
            // pops the first pet then pushes it to the end
            Pet *head = shelter.front();
            Pet *temp = nullptr;
            shelter.pop();
            temp = shelter.front();
            shelter.push(head);
            animal = temp;
            // finds a cat and cycles through the queue until a cat is found or entire queue is seen
            while(animal->getType() && temp != head) {
                temp = animal;
                shelter.pop();
                animal = shelter.front();
                shelter.push(temp);
            }
            // checks if the pet is a cat and reorganizes the queue based on it
            if(!animal->getType()) {
                shelter.pop();
                // returns stack to original order
                while (shelter.front() != head) {
                    temp = shelter.front();
                    shelter.pop();
                    shelter.push(temp);
                }
                return animal;
            } else {
                return nullptr;
            }
        }
    }
}

Pet * adoptDog(queue<Pet *> & shelter) {
    // if the shelter is empty, returns
    if(shelter.empty()) {
        return nullptr;
    } else {
        // checks first pet in queue if it is a dog
        Pet *animal = shelter.front();
        if (animal->getType()) {
            shelter.pop();
            return animal;

        } else if(shelter.front() == shelter.back()) {
            // checks if there is only one pet in the queue and returns if true
            return nullptr;
        } else {
            // pops the first pet then pushes it to the end
            Pet *head = shelter.front();
            Pet *temp = nullptr;
            shelter.pop();
            temp = shelter.front();
            shelter.push(head);
            animal = temp;
            // finds a dog and cycles through the queue until a dog is found or entire queue is seen
            while (!animal->getType() && temp != head) {
                temp = animal;
                shelter.pop();
                animal = shelter.front();
                shelter.push(temp);
            }
            // checks if the pet is a dog and reorganizes the queue based on it
            if (animal->getType()) {
                shelter.pop();
                // returns stack to original order
                while (shelter.front() != head) {
                    temp = shelter.front();
                    shelter.pop();
                    shelter.push(temp);
                }
                return animal;
            } else {
                return nullptr;
            }
        }
    }
}

int evaluateSelection(queue<Pet *> & shelter, int input) {
    string name;
    Pet * tempPet = nullptr;
    // switch case statement to evaluate based on menu selection
    switch (input) {
        case 1:
            cout << "Please enter the CAT's name: ";
            cin >> name;
            addCat(shelter, name);
            break;
        case 2:
            cout << "Please enter the DOG's name: ";
            cin >> name;
            addDog(shelter, name);
            break;
        case 3:
            tempPet = adoptCat(shelter);
            if(tempPet != nullptr) {
                cout << "Congrats on adopting a CAT, ";
                cout << "their name is: " << tempPet->getName();
                // deallocates memory
                delete tempPet;
            } else {
                cout << "Sorry, no cats are available for adoption today";
            }
            break;
        case 4:
            tempPet = adoptDog(shelter);
            if(tempPet != nullptr) {
                cout << "Congrats on adopting a DOG, ";
                cout << "their name is: " << tempPet->getName();
                // deallocates memory
                delete tempPet;
            } else {
                cout << "Sorry, no dogs are available for adoption today";
            }
            break;
        case 5:
            tempPet = adoptAny(shelter);
            if(tempPet != nullptr) {
                cout << "Congrats on adopting a ";
                if (tempPet->getType()) {
                    cout << "DOG, their name is: " << tempPet->getName();
                } else {
                    cout << "CAT, their name is: " << tempPet->getName();
                }
                // deallocates memory
                delete tempPet;
            } else {
                cout << "Sorry, no pets are available for adoption today";
            }
            break;
        case 6:
            return END;
    }
    return CONTINUE;
}
