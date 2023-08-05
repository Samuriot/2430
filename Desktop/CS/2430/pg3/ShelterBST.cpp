// Jomikael Ruiz
// April 14th, 2023
// BST.cpp

#include <iostream>
#include "ShelterBST.h"
using namespace std;


ShelterBST::TreeNode * ShelterBST::insert(TreeNode * root, Pet * pet) {
    // base case to reach leaf node
    if(!root) {
        root = new TreeNode(pet);
    }
    // search left tree to find where to insert
    else if(pet->name < root->pet->name) {
        root->left = insert(root->left, pet);
    }
    // search right tree to find where to insert
    else if(pet->name > root->pet->name){
        root->right = insert(root->right, pet);
    }
    // return root
    return root;
}

ShelterBST::TreeNode * ShelterBST::search(TreeNode * root, string name) {
    // base case to see if search is unsuccessful
    if(!root) {
        return nullptr;
    }
    // search left subtree
    else if(name < root->pet->name) {
        return search(root->left, name);
    }
    // search right subtree
    else if(name > root->pet->name) {
        return search(root->right, name);
    }
    // returns found node
    return root;
}

ShelterBST::TreeNode * ShelterBST::findMax(TreeNode * root) {
    // base case to see if tree is empty
    if(!root) {
        return nullptr;
    }
    // base case if max value is found
    else if(!root->right) {
        return root;
    }
    // traverse right-most subtree
    else {
        return findMax(root->right);
    }
}

ShelterBST::TreeNode * ShelterBST::findParent(TreeNode * root, string name) {
    // base case to see if root has parent or is empty
    if(!root || root->pet->name == name) {
        return nullptr;
    }
    // base case if left child is equal to name
    if(root->left && root->left->pet->name == name) {
        return root;
    }
    // base case if right child is equal to name
    if(root->right && root->right->pet->name == name) {
        return root;
    }
    // checks which direction to traverse tree
    if(name < root->pet->name) {
        // traverse left tree
        return findParent(root->left, name);
    } else {
        // traverse right tree
        return findParent(root->right, name);
    }
    return root;
}

ShelterBST::TreeNode * ShelterBST::findPredecessor(TreeNode * root, string name) {
    // if root is nullptr, return nullptr
    if(!root) {
        return nullptr;
    } else {
        // find node
        TreeNode * temp = search(root,name);
        // search for max in left subtree to follow algorithm
        return findMax(temp->left);
    }
}

int ShelterBST::findNumNodes(TreeNode * root) {
    // base case
    if(!root) {
        return 0;
    }
    // recursively calls function to go through whole tree
    return 1 + findNumNodes(root->left) + findNumNodes(root->right);
}

int ShelterBST::findInternalNodes(TreeNode * root) {
    // base case
    if(!root) {
        return 0;
    }
    // base case to make sure node isn't a leaf node
    else if(!root->left && !root->right) {
        return 0;
    }
    // recursively calls function to go through tree
    return 1 + findInternalNodes(root->left) + findInternalNodes(root->right);
}

// assumes currentLevel is a valid level in the tree
int ShelterBST::findLevelNodes(TreeNode * root, int level, int currentLevel) {
    // base case to stop infinite call
    if(!root) {
        return 0;
    }
    // checks if level is reached, then returns 1
    else if(currentLevel == level) {
        return 1;
    } else {
        // traverses both side of tree until level is found
        return findLevelNodes(root->left, level, currentLevel+1) + findLevelNodes(root->right, level, currentLevel+1);
    }
}

int ShelterBST::findHeight(TreeNode * root) {
    if(!root) {
        return 0;
    } else {
        // find the height of both left and right trees recursively
        int leftHeight = 1 + findHeight(root->left);
        int rightHeight = 1 + findHeight(root->right);
        // return the bigger height
        if(leftHeight > rightHeight) {
            return leftHeight;
        } else {
            return rightHeight;
        }
    }

}

bool ShelterBST::isBalanced(TreeNode * root) {
    // base case
    if(!root) {
        return true;
    } else {
        // traverses tree to see height of left and right tree
        int leftHeight = findHeight(root->left);
        int rightHeight = findHeight(root->right);
        // checks if the difference is greater than 1
        if(leftHeight > rightHeight) {
            if((leftHeight - rightHeight) > 1) {
                return false;
            }
            return true;
        } else {
            if((rightHeight - leftHeight) > 1) {
                return false;
            }
            return true;
        }
    }
}

void ShelterBST::inorder(TreeNode * root) {
    // base case
    if(!root) {
        return;
    }
    // traversing tree left -> middle -> right
    inorder(root->left);
    cout << "NAME: " << root->pet->name << "\tAGE: " << root->pet->age << endl;
    inorder(root->right);
}

void ShelterBST::preorder(TreeNode * root) {
    // base case
    if(!root) {
        return;
    }
    // traversing tree middle -> left -> right
    cout << "NAME: " << root->pet->name << "\tAGE: " << root->pet->age << endl;
    preorder(root->left);
    preorder(root->right);
}

void ShelterBST::postorder(TreeNode * root) {
    // base case
    if(!root) {
        return;
    }
    // traversing tree left -> right -> middle
    postorder(root->left);
    postorder(root->right);
    cout << "NAME: " << root->pet->name << "\tAGE: " << root->pet->age << endl;
}

void ShelterBST::swapPets(TreeNode *& node1, TreeNode *& node2) {
    // swaps pets for deleteNode function
    Pet * temp = node1->pet;
    node1->pet = node2->pet;
    node2->pet = temp;
}

ShelterBST::TreeNode * ShelterBST::deleteNode(TreeNode * root, string name) {
    // temp variables
    TreeNode * temp = nullptr;
    TreeNode * parent = nullptr;
    TreeNode * predecessor = nullptr;
    // base case
    if(!root) {
        return nullptr;
    }
    // search tree for value to be deleted
    else if(root->pet->name < name) {
        return deleteNode(root->right, name);
    } else if(root->pet->name > name) {
        return deleteNode(root->left, name);
    }
    // once found, updates links within the tree to successfully delete
    else {
        // once found, find the parent
        parent = findParent(this->root, name);
        // case if root is the actual tree root and replaces with predecessor
        if(!parent) {
            predecessor = findPredecessor(this->root, name);
            parent = findParent(this->root, predecessor->pet->name);
            swapPets(root, predecessor);
            parent->right = nullptr;
            return predecessor;
        }
        // if node has 2 children
        if(root->left && root->right) {
            predecessor = findPredecessor(this->root, name);
            swapPets(root, predecessor);
            root->left = nullptr;
            return predecessor;
        }
        // if node has 1 child and it is a right child
        else if(root->right && !root->left) {
            temp = root;
            if(parent->pet->name > temp->pet->name) {
                parent->left = temp->right;
            } else if(parent->pet->name < temp->pet->name) {
                parent->right = temp->right;
            }
        }
        // if node has 1 child and it is a left child
        else if(root->left && !root->right) {
            temp = root;
            if(parent->pet->name > temp->pet->name) {
                parent->left = temp->left;
            } else if(parent->pet->name < temp->pet->name) {
                parent->right = temp->left;
            }
        }
        // if node has no children
        else {
            if(parent->pet->name > root->pet->name) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        }
    }
    return root;
}

ShelterBST::TreeNode * ShelterBST::destroyTree(TreeNode * root) {
    // traverses left tree to completely delete
    if(root->left) {
        destroyTree(root->left);
    }
    // traverses right tree to delete
    else if(root->right) {
        destroyTree(root->right);
    }
    // deletes middle
    else {
        delete root;
    }
    // returns nullptr
    return nullptr;
}

ShelterBST::ShelterBST() {
    root = nullptr;
}

void ShelterBST::insertPet(string name, int age) {
    root = insert(root, new Pet(name, age));
}

void ShelterBST::searchPet(string name) {
    TreeNode * result = search(root, name);
    if(!result) {
        cout << "Error, Pet not found";
    } else {
        cout << "NAME: " << result->pet->name << "\tAGE: " << result->pet->age << endl;
    }
}

void ShelterBST::getParent(string name) {
    TreeNode * result = findParent(root, name);
    if(!result) {
        cout << "Error, Pet not found";
    } else {
        cout << "NAME: " << result->pet->name << "\tAGE: " << result->pet->age << endl;
    }
}

void ShelterBST::getPredecessor(string name) {
    TreeNode * result = findPredecessor(root, name);
    if(!result) {
        cout << "Error, Pet not found";
    } else {
        cout << "NAME: " << result->pet->name << "\tAGE: " << result->pet->age << endl;
    }
}

void ShelterBST::deleteANode(string name) {
    TreeNode * result = deleteNode(root, name);
    if(!result) {
        cout << "Error, Pet not found";
    } else {
        cout << endl << "Deleted Node: ";
        cout << "NAME: " << result->pet->name << "\tAGE: " << result->pet->age << endl;
    }
    delete result;
}

void ShelterBST::getHeight() {
    int height = findHeight(root);
    cout << "Tree has a height of " << height - 1 << "." << endl;
}

void ShelterBST::getNumNodes() {
    int nodes = findNumNodes(root);
    cout << "Tree has " << nodes << " nodes." << endl;
}

void ShelterBST::getInternalNodes() {
    int nodes = findInternalNodes(root);
    cout << "Tree has " << nodes << " internal nodes." << endl;
}

void ShelterBST::getBalance() {
    bool balance = isBalanced(root);
    if(!balance) {
        cout << "No, the tree is out of balance." << endl;
    } else {
        cout << "Yes, the tree is in balance" << endl;
    }
}

void ShelterBST::destroyAllTree() {
    destroyTree(root);
}

void ShelterBST::getLevelNodes(int val) {
    int nodes = findLevelNodes(root, val, 0);
    cout << "Tree has " << nodes << " internal nodes." << endl;
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
