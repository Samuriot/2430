// Jomikael Ruiz
// BST.h
// April 14th, 2023

#ifndef BST_H
#define BST_H

#include <string>

class ShelterBST {
private:
    struct Pet {
        std::string name;
        int age;
        Pet(std::string name, int age) {
            this->name = name;
            this->age = age;
        }
    };

    struct TreeNode {
        Pet * pet;
        TreeNode * left;
        TreeNode * right;
        TreeNode(Pet * pet) {
            this->pet = pet;
            this->left = nullptr;
            this->right = nullptr;
        }
    };

    TreeNode * root;

    TreeNode * insert(TreeNode * root, Pet * pet);

    TreeNode * search(TreeNode * root, int age);

    void inorder(TreeNode * root);

    void preorder(TreeNode * root);

    void postorder(TreeNode * root);
public:
    ShelterBST();

    void insertPet(std::string name, int age);

    void searchPet(int age);

    void inorderDisplay();

    void preorderDisplay();

    void postorderDisplay();
};

#endif //BST_H
