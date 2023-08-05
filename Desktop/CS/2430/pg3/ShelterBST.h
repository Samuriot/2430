// Jomikael Ruiz
// BST.h
// April 14th, 2023

#ifndef BST_H
#define BST_H

#include <string>

class ShelterBST {
private:
    // struct for the pet
    struct Pet {
        std::string name;
        int age;
        Pet(std::string name, int age) {
            this->name = name;
            this->age = age;
        }
    };

    // struct for actual nodes
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

    // insert function that places a node into the tree
    TreeNode * insert(TreeNode * root, Pet * pet);

    // searches the entire tree based on name and returns nullptr if not found
    TreeNode * search(TreeNode * root, std::string name);

    // uses search function and findMax to find a predecessor
    // assumes predecessor has 2 children and is for use in deleteNode
    TreeNode * findPredecessor(TreeNode * root, std::string name);

    // implements traits of search function to find a node's parent
    TreeNode * findParent(TreeNode * root, std::string name);

    // searches right subtree to find max of a tree
    TreeNode * findMax(TreeNode * root);

    // traverses tree to count the amount of nodes
    int findNumNodes(TreeNode * root);

    // traverses tree to find number of nodes that aren't leaf nodes
    int findInternalNodes(TreeNode * root);

    // traverses tree to find number of nodes at a specific level
    int findLevelNodes(TreeNode * root, int level, int currentLevel);

    // traverses tree to find the height of the tree
    int findHeight(TreeNode * root);

    // traverses tree and compares left and right tree for balance
    bool isBalanced(TreeNode * root);

    // swaps pets of treeNodes for use in deleteNode
    void swapPets(TreeNode *& node1, TreeNode *& node2);

    // traverses tree from left->middle->right
    void inorder(TreeNode * root);

    // traverse tree from middle->left->right
    void preorder(TreeNode * root);

    // traverses tree from left->right->middle
    void postorder(TreeNode * root);

    // finds a specific node and deletes a node based on if it
    // has 0, 1, or 2 child and implements findPredecessor,
    // findParent, and swapPets
    TreeNode * deleteNode(TreeNode * root, std::string name);

    // traverses entire tree and deletes each node, returning nullptr
    TreeNode * destroyTree(TreeNode * root);
public:

    // constructor
    ShelterBST();

    // public function that calls insert()
    void insertPet(std::string name, int age);

    // public function that calls search()
    void searchPet(std::string name);

    // public function that calls findParent()
    void getParent(std::string name);

    // public function that calls findPredecessor()
    void getPredecessor(std::string name);

    // public function that calls deleteNode()
    void deleteANode(std::string name);

    // public function that calls findHeight()
    void getHeight();

    // public function that calls isBalanced()
    void getBalance();

    // public function that calls findNumNodes()
    void getNumNodes();

    // public function that calls findInternalNodes()
    void getInternalNodes();

    // public function that calls findLevelNodes()
    void getLevelNodes(int val);

    // public function that calls destroyTree()
    void destroyAllTree();

    // public function that calls inorder()
    void inorderDisplay();

    // public function that calls preorder()
    void preorderDisplay();

    // public function that calls postorder()
    void postorderDisplay();
};

#endif //BST_H
