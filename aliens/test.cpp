#include <iostream>

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

struct BinaryTree {
    TreeNode* root;

    BinaryTree() {
        root = nullptr;
    }

    void insert(int val) {
        TreeNode* newNode = new TreeNode(val);
        if (root == nullptr) {
            root = newNode;
            return;
        }

        TreeNode* current = root;
        while (true) {
            if (val < current->data) {
                if (current->left == nullptr) {
                    current->left = newNode;
                    break;
                }
                current = current->left;
            } else {
                if (current->right == nullptr) {
                    current->right = newNode;
                    break;
                }
                current = current->right;
            }
        }
    }

    void traverse(TreeNode* node) {
        if (node != nullptr) {
            traverse(node->left);
            std::cout << node->data << " ";
            traverse(node->right);
        }
    }

    void inorder() {
        traverse(root);
    }
};

int main() {
    BinaryTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    tree.inorder();
    return 0;
}
