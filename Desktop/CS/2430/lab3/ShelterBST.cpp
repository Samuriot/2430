// Jomikael Ruiz
// April 14th, 2023
// BST.cpp

#include <iostream>
#include "ShelterBST.h"
using namespace std;


ShelterBST::TreeNode * ShelterBST::insert(TreeNode * root, Pet * pet) {
    if(!root) {
        root = new TreeNode(pet);
    } else if(pet->age < root->pet->age) {
        root->left = insert(root->left, pet);
    } else if(pet->age > root->pet->age){
        root->right = insert(root->right, pet);
    }
    return root;
}

ShelterBST::TreeNode * ShelterBST::search(TreeNode * root, int age) {
    if(!root) {
        return nullptr;
    } else if(age < root->pet->age) {
        return search(root->left, age);
    } else if(age > root->pet->age) {
        return search(root->right, age);
    }
    return root;
}

void ShelterBST::inorder(TreeNode * root) {
    if(!root) {
        return;
    }
    inorder(root->left);
    cout << "NAME: " << root->pet->name << "\tAGE: " << root->pet->age << endl;
    inorder(root->right);
}

void ShelterBST::preorder(TreeNode * root) {
    if(!root) {
        return;
    }
    cout << "NAME: " << root->pet->name << "\tAGE: " << root->pet->age << endl;
    preorder(root->left);
    preorder(root->right);
}

void ShelterBST::postorder(TreeNode * root) {
    if(!root) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << "NAME: " << root->pet->name << "\tAGE: " << root->pet->age << endl;
}

ShelterBST::ShelterBST() {
    root = nullptr;
}

void ShelterBST::insertPet(string name, int age) {
    root = insert(root, new Pet(name, age));
}

void ShelterBST::searchPet(int age) {
    TreeNode * result = search(root, age);
    if(!result) {
        cout << "Error, Pet not found";
    } else {
        cout << "NAME: " << result->pet->name << "\tAGE: " << result->pet->age << endl;
    }
}

void ShelterBST::inorderDisplay() {
    inorder(root);
}

void ShelterBST::preorderDisplay() {
    preorder(root);
}

void ShelterBST::postorderDisplay() {
    postorder(root);
}