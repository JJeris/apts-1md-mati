#include <fstream>
using namespace std;
// Author: Johans Justs Eris, je21033

struct TreeNode {
    // An element, that represents a node in a binary tree.
    bool exists = false; // If a node exists
    int leftChildNode = -1; // The leftchild of a node
    int rightChildNode = -1; // The rightchild of a node
    int prevNode = -1; // The prev inorder node
    int nextNode = -1; // The next inorder node
};

bool evalInput(int parentNumber, int childNumber, char side, TreeNode treeNodeArray[], ofstream &output){
    // evalInput function, that evaluates, if an error should be outputed to the output file, or, if
    // a node should be added to the "tree".
    // args: parentNumber that is the value of the parent node
    //       childNumber that is the value of the child node
    //       side that is either 'L' or 'R' character
    //       treeNodeArray which is the binary tree represented in an array
    //       output which is the output filen

    if (parentNumber == childNumber){
        // If both parent and child are the same value.
        output << "error1" << '\n';
        return false;
    }
    else if(treeNodeArray[parentNumber].exists == false){
        // If the parent node is not found, the new node cannot be inserted
        output << "error2" << '\n';
        return false;
    }
    else if (treeNodeArray[childNumber].exists != false){
        // If the child node already exists, the new node cannot be inserted
        output << "error3" << '\n';
        return false;
    }
    else {
        if(side == 'L'){
            if (treeNodeArray[parentNumber].leftChildNode != -1){
                // If the left child of the parent node is not empty, we cannot insert a new node on the left
                output << "error4" << '\n';
                return false;
            }
            else {
                // If no error was detected, return true - the node can be added to the array
                return true;
            }
        }
        else { //if (side == 'R')
            if (treeNodeArray[parentNumber].rightChildNode != -1){
                // If the right child of the parent node is not empty, we cannot insert a new node on the right
                output << "error5" << '\n';
                return false;
            }
            else {
                // If no error was detected, return true - the node can be added to the array
                return true;
            }
        }
    }
}


int main(){
    // Open the files.
    ifstream input("aliens.in");
    ofstream output;

    // Create a buffer, to help with the output. Makes the program faster - more effiecient.
    const unsigned int length = 1536;
    char buffer[length];
    output.rdbuf()->pubsetbuf(buffer, length);
    output.open("aliens.out");

    int cursor = 0;
    char line[14];
    // Tree root variable
    int root = 0;

    // An array containing the marsians that represetns a modified binary tree
    TreeNode treeNodeArray[10001];

    // Define the root element
    input.getline(line, 14);
    while(line[cursor] != '\0'){
        root = root*10 + line[cursor] - '0';
        cursor++;
    }

    // Set the exists value of the at the root index to true, showing that the node exists.
    treeNodeArray[root].exists = true;

    // Define variables for the while loop.
    int parentNumber = 0;
    int childNumber = 0;
    int targetAlien = 0;
    int temp = -1;
    cursor = 0;

    input.getline(line, 14);
    while (true){
        // Check, if the input file has ended.
        if (line[cursor] == 'F'){
            break;
        }
        // Check if we have to find the favorite relatives to a node
        if (line[cursor] == '?'){
            cursor+=2;

            // Input the targetAlien
            while(line[cursor] != '\0'){
                targetAlien = targetAlien*10 + line[cursor] - '0';
                cursor++;
            }
            if(treeNodeArray[targetAlien].exists == false){
                // targetAlien is not present in the tree
                output << "error0" << '\n';
            }
            else {
                // If the node has no previous node and no next node
                if(treeNodeArray[targetAlien].prevNode == -1 && treeNodeArray[targetAlien].nextNode == -1){
                output << "0 0" << '\n';
                }
                // If the node has no previous node, but has a next node
                else if(treeNodeArray[targetAlien].prevNode == -1){
                    output << "0 " << treeNodeArray[targetAlien].nextNode << '\n'; 
                }
                // If the node has a previous node, but has no next node
                else if(treeNodeArray[targetAlien].nextNode == -1){
                    output << treeNodeArray[targetAlien].prevNode << " 0" << '\n';
                }
                // If the node has a previous node and a next node
                else {
                    output << treeNodeArray[targetAlien].prevNode << " " << treeNodeArray[targetAlien].nextNode << '\n';
                }
            }
        }

        // Else we check to see, if we can add the provided node to the Left or Right side
        else if (line[cursor] == 'L'){
            cursor+=2;
            // Input the parentNumber          
            while(line[cursor] != ' '){
                parentNumber = parentNumber*10 + line[cursor] - '0';
                cursor++;
            }
            // Input the childNumber
            cursor++;
            while(line[cursor] != '\0'){
                childNumber = childNumber*10 + line[cursor] - '0';
                cursor++;
            }
    
            // Evalutes the presented node to be inputed. If returns false, it also outputs the appropriate error
            if (evalInput(parentNumber, childNumber, 'L', treeNodeArray, output) == true){
                
                // Specify that the node exists
                treeNodeArray[childNumber].exists = true;
                
                // Set the parents leftchild to the childNumber
                treeNodeArray[parentNumber].leftChildNode = childNumber;

                // The added nodes previous node becomes the parents previous node
                treeNodeArray[childNumber].prevNode = treeNodeArray[parentNumber].prevNode;

                // The child nodes next node becomes the parent (root) node
                treeNodeArray[childNumber].nextNode = parentNumber;

                temp = treeNodeArray[parentNumber].prevNode;

                // The parents previous node now becomes the child node.
                treeNodeArray[parentNumber].prevNode = childNumber;

                // The previous node, if it existed, has its next node set to the child value
                if (temp != -1){
                    treeNodeArray[temp].nextNode = childNumber;
                }
            }
        }
        else if (line[cursor] == 'R'){
            cursor+=2;
            // Input the parentNumber          
            while(line[cursor] != ' '){
                parentNumber = parentNumber*10 + line[cursor] - '0';
                cursor++;
            }
            // Input the childNumber
            cursor++;
            while(line[cursor] != '\0'){
                childNumber = childNumber*10 + line[cursor] - '0';
                cursor++;
            }
            // Evalutes the presented node to be inputed. If returns false, it also outputs the appropriate error
            if (evalInput(parentNumber, childNumber, 'R', treeNodeArray, output) == true){

                // Specify that the node exists
                treeNodeArray[childNumber].exists = true;

                // Set the parents rightchild to the childNumber
                treeNodeArray[parentNumber].rightChildNode = childNumber;

                // The childs node previous node is set to the parent value
                treeNodeArray[childNumber].prevNode = parentNumber;

                // The childs node next node is set to the parents node next node
                treeNodeArray[childNumber].nextNode = treeNodeArray[parentNumber].nextNode;

                temp = treeNodeArray[parentNumber].nextNode;

                // The parents next node now becomes the child node.
                treeNodeArray[parentNumber].nextNode = childNumber;

                // The next node, if it existed, has its previous node set to the child value
                if (temp != -1){
                    treeNodeArray[temp].prevNode = childNumber;
                }
            }
        }

        // Reset all values
        cursor = 0;
        parentNumber = 0;
        childNumber = 0;
        targetAlien = 0;

        // Input the next line
        input.getline(line, 14);
    }
}