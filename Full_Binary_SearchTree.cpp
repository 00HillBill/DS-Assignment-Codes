#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = right = nullptr;
    }
};

Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    return root;
}

void inOrder(Node* root) {
    if (root != nullptr) {
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }
}

void preOrder(Node* root) {
    if (root != nullptr) {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(Node* root) {
    if (root != nullptr) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->data << " ";
    }
}

bool search(Node* root, int value) {
    if (root == nullptr) return false;
    if (root->data == value) return true;
    if (value < root->data) return search(root->left, value);
    return search(root->right, value);
}

Node* findMin(Node* root) {
    while (root && root->left != nullptr) {
        root = root->left;
    }
    return root;
}

Node* findMax(Node* root) {
    while (root && root->right != nullptr) {
        root = root->right;
    }
    return root;
}

Node* deleteNode(Node* root, int value) {
    if (root == nullptr) return root;
    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

Node* update(Node* root, int oldValue, int newValue) {
    root = insert(root, newValue);
    root = deleteNode(root, oldValue);
    return root;
}

// void insertLast(Node* root, int value) {
//     if (root == nullptr) return;
//     queue<Node*> q;
//     q.push(root);
//     while (!q.empty()) {
//         Node* temp = q.front();
//         q.pop();
//         if (temp->left == nullptr) {
//             temp->left = new Node(value);
//             return;
//         } else {
//             q.push(temp->left);
//         }
//         if (temp->right == nullptr) {
//             temp->right = new Node(value);
//             return;
//         } else {
//             q.push(temp->right);
//         }
//     }
// }

Node* findSecondMax(Node* root) {
    Node* parent = nullptr;
    Node* current = root;
    while (current && current->right != nullptr) {
        parent = current;
        current = current->right;
    }
    if (current && current->left != nullptr) {
        return findMax(current->left);
    }
    return parent;
}

Node* deleteSecondMax(Node* root) {
    Node* secondMax = findSecondMax(root);
    if (secondMax) {
        root = deleteNode(root, secondMax->data);
    }
    return root;
}

// int countNodes(Node* root) {
//     if (root == nullptr) return 0;
//     return 1 + countNodes(root->left) + countNodes(root->right);
// }

// int sumNodes(Node* root) {
//     if (root == nullptr) return 0;
//     return root->data + sumNodes(root->left) + sumNodes(root->right);
// }

// double findMedian(Node* root) {
//     int totalNodes = countNodes(root);
//     int totalSum = sumNodes(root);
//     return static_cast<double>(totalSum) / totalNodes;
// }

int main() {
    Node* root = nullptr;
    int choice, value, oldValue, newValue;

    do {
        cout << "\n--- Binary Search Tree Menu ---\n";
        cout << "1. Insert\n";
        cout << "2. In-order Traversal (Sorted)\n";
        cout << "3. Pre-order Traversal\n";
        cout << "4. Post-order Traversal\n";
        cout << "5. Search\n";
        cout << "6. Find Minimum\n";
        cout << "7. Find Maximum\n";
        cout << "8. Update\n";
        cout << "9. Delete\n";
        // cout << "10. Insert Last Node\n";
        cout << "11. Delete Second Maximum\n";
        // cout << "12. Find Median\n";
        cout << "13. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if(choice == 1) {
            cout << "Enter value to insert: ";
            cin >> value;
            root = insert(root, value);
        } 
        else if (choice == 2) {
            cout << "In-order Traversal: ";
            inOrder(root);
            cout << endl;
        } 
        else if (choice == 3) {
            cout << "Pre-order Traversal: ";
            preOrder(root);
            cout << endl;
        } 
        else if (choice == 4) {
            cout << "Post-order Traversal: ";
            postOrder(root);
            cout << endl;
        } 
        else if (choice == 5) {
            cout << "Enter value to search: ";
            cin >> value;
            if (search(root, value)) {
                cout << value << " found in the tree.\n";
            } else {
                cout << value << " not found in the tree.\n";
            }
        } 
        else if (choice == 6) {
            if (root != nullptr) {
                cout << "Minimum value: " << findMin(root)->data << endl;
            } else {
                cout << "Tree is empty.\n";
            }
        } 
        else if (choice == 7) {
            if (root != nullptr) {
                cout << "Maximum value: " << findMax(root)->data << endl;
            } else {
                cout << "Tree is empty.\n";
            }
        } 
        else if (choice == 8) {
            cout << "Enter value to update: ";
            cin >> oldValue;
            cout << "Enter new value: ";
            cin >> newValue;
            if (search(root, oldValue)) {
                root = update(root, oldValue, newValue);
                cout << "Value updated.\n";
            } else {
                cout << oldValue << " not found in the tree.\n";
            }
        } 
        else if (choice == 9) {
            cout << "Enter value to delete: ";
            cin >> value;
            root = deleteNode(root, value);
            cout << "Value deleted (if it was present).\n";
        } 
        // else if (choice == 10) {
        //     cout << "Enter value to insert as last node: ";
        //     cin >> value;
        //     insertLast(root, value);
        // } 
        else if (choice == 11) {
            root = deleteSecondMax(root);
            cout << "Second maximum value deleted.\n";
        } 
        // else if (choice == 12) {
        //     if (root != nullptr) {
        //         cout << "Median of the nodes: " << findMedian(root) << endl;
        //     } else {
        //         cout << "Tree is empty.\n";
        //     }
        // } 
        else if (choice == 13) {
            cout << "Exiting...\n";
        } 
        else {
            cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 13);

    return 0;
}
