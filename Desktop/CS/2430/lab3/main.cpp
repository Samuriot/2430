// Jomikael Ruiz
// lab3.cpp
// April 14th, 2023
// Purpose: Creating binary search trees and implementation

#include <iostream>
#include "ShelterBST.h"
using namespace std;

void fillTree(ShelterBST & tree);
void testAllDisplays(ShelterBST tree);
void testSearch(ShelterBST tree);

int main() {
    ShelterBST tree;
    fillTree(tree);
    testAllDisplays(tree);
    testSearch(tree);
    return 0;
}

void fillTree(ShelterBST & tree) {
    // creating 10 nodes and inserting them into the tree
    tree.insertPet("Jett", 4);
    tree.insertPet("Reyna", 5);
    tree.insertPet("Raze", 2);
    tree.insertPet("Sage", 1);
    tree.insertPet("Skye", 8);
    tree.insertPet("Yoru", 10);
    tree.insertPet("Fade", 12);
    tree.insertPet("Neon", 6);
    tree.insertPet("Sova", 15);
    tree.insertPet("Viper", 20);
}

void testAllDisplays(ShelterBST tree) {
    cout << "Inorder Display: " << endl;
    tree.inorderDisplay();
    cout << "Preorder Display: " << endl;
    tree.preorderDisplay();
    cout << "Postorder Display: " << endl;
    tree.postorderDisplay();
}

void testSearch(ShelterBST tree) {
    cout << "Example of successful search" << endl;
    // successful search
    tree.searchPet(8);
    cout << "Example of unsuccessful search" << endl;
    // unsuccessful search
    tree.searchPet(100);
}