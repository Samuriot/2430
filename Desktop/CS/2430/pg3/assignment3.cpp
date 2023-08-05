// Jomikael Ruiz
// lab3.cpp
// April 14th, 2023
// Purpose: Creating binary search trees and implementation

#include <iostream>
#include "ShelterBST.h"
using namespace std;

const int ENDVAL = -1;
const int CONTINUE = 1;

void fillTree(ShelterBST & tree);
void testAllDisplays(ShelterBST tree);
void testSearch(ShelterBST & tree);
void testAllFunctions(ShelterBST & tree);
void testNumFunctions(ShelterBST & tree);
void testDelete(ShelterBST & tree);
int displayMenu();
int evaluateInput(ShelterBST & tree, int input);

int main() {
    ShelterBST tree;
    int input = CONTINUE;
    while(input != ENDVAL) {
        input = displayMenu();
        input = evaluateInput(tree, input);
    }
    return 0;
}

void fillTree(ShelterBST & tree) {
    // creating 10 nodes and inserting them into the tree
    cout << "Filling tree with 10 pets: " << endl;
    tree.insertPet("Eddy", 4);
    tree.insertPet("Boil", 5);
    tree.insertPet("Gary", 2);
    tree.insertPet("Aaron", 1);
    tree.insertPet("Casey", 8);
    tree.insertPet("Finn", 10);
    tree.insertPet("Ike", 12);
    tree.insertPet("Duke", 6);
    tree.insertPet("Hut", 15);
    tree.insertPet("Jake", 20);
    cout << "Tree successfully filled." << endl;
}

void testAllDisplays(ShelterBST tree) {
    cout << endl << "Inorder Display: " << endl;
    tree.inorderDisplay();
    cout << endl << "Preorder Display: " << endl;
    tree.preorderDisplay();
    cout << endl << "Postorder Display: " << endl;
    tree.postorderDisplay();
    cout << endl;
}

void testSearch(ShelterBST & tree) {
    cout << "Example of successful search" << endl;
    // successful search
    tree.searchPet("Hut");
    cout << endl << "Example of unsuccessful search" << endl;
    // unsuccessful search
    tree.searchPet("Jett");
    cout << endl << endl;
}

void testDelete(ShelterBST & tree) {
    cout << endl << "Deleting node with no children";
    tree.deleteANode("Jake");
    cout << endl << "Updated Inorder Display: " << endl;
    tree.inorderDisplay();
    cout << endl << "Deleting node with 1 child";
    tree.deleteANode("Casey");
    cout << endl << "Updated Inorder Display: " << endl;
    tree.inorderDisplay();
    cout << endl << "Deleting node with 2 children";
    tree.deleteANode("Aaron");
    cout << endl << "Updated Inorder Display: " << endl;
    tree.inorderDisplay();
    cout << endl;
}

void testNumFunctions(ShelterBST & tree) {
    cout << "Testing integer returning and balance functions: " << endl;
    tree.getHeight();
    tree.getNumNodes();
    tree.getInternalNodes();
    cout << "Getting number of nodes at level 1: " << endl;
    tree.getLevelNodes(1);
    cout << endl;
    tree.getBalance();
    cout << endl;
}

void testAllFunctions(ShelterBST & tree) {
    fillTree(tree);
    testAllDisplays(tree);
    testSearch(tree);
    testDelete(tree);
    testNumFunctions(tree);
    cout << "Deleting Tree: " << endl;
    tree.destroyAllTree();
    cout << "Tree Successfully Deleted." << endl << endl;
}

int displayMenu() {
    int input;
    cout << endl << "Welcome to the implementation of ShelterBST, choose an operation." << endl;
    cout << "1.\t Insert a node" << endl;
    cout << "2.\t Search a value" << endl;
    cout << "3.\t Delete a node" << endl;
    cout << "4.\t Print the tree" << endl;
    cout << "5.\t Find the number of nodes in a tree" << endl;
    cout << "6.\t Find the number of internal nodes" << endl;
    cout << "7.\t Find the height of the tree" << endl;
    cout << "8.\t Check for tree's balance" << endl;
    cout << "9.\t Find the number of nodes at a given level" << endl;
    cout << "10.\t Find the parent of a node" << endl;
    cout << "11.\t Find the predecessor of a node" << endl;
    cout << "12.\t Destroy entire tree" << endl;
    cout << "13.\t Test All Function" << endl;
    cout << "14.\t Exit" << endl;
    cin >> input;
    return input;
}

int evaluateInput(ShelterBST & tree, int input) {
    string tempName;
    int tempVal;
    switch(input) {
        case 1:
            cout << "Enter a name: ";
            cin >> tempName;
            cout << "Enter an age: ";
            cin >> tempVal;
            tree.insertPet(tempName, tempVal);
            break;
        case 2:
            cout << "Enter a node's name: ";
            cin >> tempName;
            tree.searchPet(tempName);
            break;
        case 3:
            cout << "Enter a node's name: ";
            cin >> tempName;
            tree.deleteANode(tempName);
            break;
        case 4:
            cout << "Enter a choice for print" << endl;
            cout << "1.\t inorder" << endl;
            cout << "2.\t preorder" << endl;
            cout << "3.\t postorder" << endl;
            cin >> tempVal;
            switch(tempVal) {
                case 1:
                    tree.inorderDisplay();
                    break;
                case 2:
                    tree.preorderDisplay();
                    break;
                case 3:
                    tree.postorderDisplay();
                    break;
            }
            break;
        case 5:
            tree.getNumNodes();
            break;
        case 6:
            tree.getInternalNodes();
            break;
        case 7:
            tree.getHeight();
            break;
        case 8:
            tree.getBalance();
            break;
        case 9:
            cout << "Enter a specific level in the tree: ";
            cin >> tempVal;
            tree.getLevelNodes(tempVal);
            break;
        case 10:
            cout << "Enter an existing node's name: ";
            cin >> tempName;
            tree.getParent(tempName);
            break;
        case 11:
            cout << "Enter a node with 2 existing children: ";
            cin >> tempName;
            tree.getPredecessor(tempName);
            break;
        case 12:
            cout << "Starting tree destruction: " << endl;
            tree.destroyAllTree();
            cout << "Tree successfully destroyed, root set to nullptr." << endl;
            break;
        case 13:
            testAllFunctions(tree);
            break;
        case 14:
            return ENDVAL;
    }
    return input;
}