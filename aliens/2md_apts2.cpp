#include <fstream>
using namespace std;

// Author: Johans Justs Eris, je21033
struct TreeNode {
    int alienNumber;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) {
        alienNumber = val;
        left = nullptr;
        right = nullptr;
    }
};

TreeNode* findNode(TreeNode* node, int val) {
    // If the current node is null or has the desired value, return the node
    if (node == nullptr || node->alienNumber == val) {
        return node;
    }
    // Recursively search for the node in the left subtree
    TreeNode* leftNode = findNode(node->left, val);
    if (leftNode != nullptr) {
        return leftNode;
    }
    // Recursively search for the node in the right subtree
    TreeNode* rightNode = findNode(node->right, val);
    if (rightNode != nullptr) {
        return rightNode;
    }
    // If the node is not found in either subtree, return null
    return nullptr;
}

struct BinaryTree {
    TreeNode* root;

    BinaryTree() {
        root = nullptr;
    }

    bool insert(int val, int parentNodeVal, char side, ofstream &output) {
        // Check if the tree is empty
        if (root == nullptr) {
            // If so, the new node will be the root node
            root = new TreeNode(val);
            return true;
        }
           
        if (parentNodeVal == val) {
            // If both parent and child are the same value
            output << "error1" << '\n';
            return false;
        }
        // Find the parent node
        TreeNode* parentNode = findNode(root, parentNodeVal);
        if (parentNode == nullptr) {
            // If the parent node is not found, the new node cannot be inserted
            output << "error2" << '\n';
            return false;
        }

        TreeNode* childNode = findNode(root, val);
        if (childNode != nullptr) {
            //  If the child node already exists, the new node cannot be inserted
            output << "error3" << '\n';
            return false;
        }
    
        // Create the new node
        TreeNode* newNode = new TreeNode(val);
        // Insert the new node as a child of the parent node on the left or right side
        if (side == 'L') {
            if (parentNode->left == nullptr) {
                parentNode->left = newNode;
                return true;
            } else {
                // If the left child of the parent node is not empty, we cannot insert a new node on the left
                output << "error4" << '\n';
                return false;
            }
        } else if (side == 'R') {
            if (parentNode->right == nullptr) {
                parentNode->right = newNode;
                return true;
            } else {
                // If the right child of the parent node is not empty, we cannot insert a new node on the right
                output << "error5" << '\n';
                return false;
            }
        } else {
            // If the provided side character is invalid, we cannot insert the new node
            return false;
        }
    }

    void traverse(TreeNode* node, int* arr, int& index) {
        if (node != nullptr) {
            traverse(node->left, arr, index);
            arr[index] = node->alienNumber;
            index++;
            traverse(node->right, arr, index);
        }
    }

    void inorderToArr(int* arr, int size) {
        int index = 0;
        traverse(root, arr, index);
    }

    void deleteRoot(){
        deleteTree(this->root);
    }

    void deleteTree(TreeNode* node) {
        if (node != nullptr) {
            // Recursively delete the left and right subtrees
            deleteTree(node->left);
            deleteTree(node->right);
            // Delete the current node
            delete node;
        }
    }
};

int main() {
    // Open the files.
    ifstream input("aliens.in");
    ofstream output;

    // Create a buffer, to help with the output. Makes the program faster 
    // and in turn more effiecient.
    const unsigned int length = 1536;
    char buffer[length];
    output.rdbuf()->pubsetbuf(buffer, length);
    output.open("aliens.out");

    int treeSize = 0;
    int cursor = 0;
    char line[14];

    // Root alien number
    int root = 0;

    BinaryTree tree;
    // Read in the number of the root alien.    
    input.getline(line, 14);
    while(line[cursor] != '\0'){
        root = root*10 + line[cursor] - '0';
        cursor++;
    }
    
    tree.insert(root, 0, ' ', output);
    cursor = 0;
    treeSize++;

    char side = ' ';
    int parentNumber = 0;
    int childNumber = 0;
    int targetAlien = 0;
    input.getline(line, 14);
    while (true){
        // Check, if the input file has ended.
        if (line[cursor] == 'F'){
            break;
        }
        if (line[cursor] == '?'){
            cursor+=2;
            while(line[cursor] != '\0'){
                targetAlien = targetAlien*10 + line[cursor] - '0';
                cursor++;
            }
            int* arr = new int[treeSize];
            tree.inorderToArr(arr, treeSize);

            // Atrod index izvēlētajam alien.
            int index = -1;
            for (int i = 0; i < treeSize; i++) {
                if (arr[i] == targetAlien) {
                    index = i;
                    break;
                }
            }

            if (index == -1){
                output << "error0" << '\n';
            }
            else if (index == 0){
                if (treeSize == 1){
                    output << 0 << " " << 0 << '\n';
                }
                else {
                    output << 0 << " " << arr[index+1] << '\n';
                }
            }
            else if (index > 0 && index+1 < treeSize){
                output << arr[index-1] << " " << arr[index+1] << '\n';
            }
            else {
                output << arr[index-1] << " " << 0 << '\n';
            }

            delete [] arr;
        }
        else {
            // input side
            side = line[cursor];
            cursor+=2;
            // input parentNumber          
            while(line[cursor] != ' '){
                parentNumber = parentNumber*10 + line[cursor] - '0';
                cursor++;
            }
            // input childNumber
            cursor++;
            while(line[cursor] != '\0'){
                childNumber = childNumber*10 + line[cursor] - '0';
                cursor++;
            }

            if (tree.insert(childNumber, parentNumber, side, output)){
                treeSize++;
            }

        }
        cursor = 0;
        side = ' ';
        parentNumber = 0;
        childNumber = 0;
        targetAlien = 0;
        input.getline(line, 14);
    }
    tree.deleteRoot();
    return 0;
}