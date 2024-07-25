#include <iostream>
using namespace std;

struct Node {
    int key;
    struct Node *left, *right;
};

struct Node* newNode(int key) {
    struct Node* node = new Node;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct Node* insert(Node* root, int insertval) {
    if (root == NULL) {
        return newNode(insertval);
    }
    if (root->key > insertval) {
        root->left = insert(root->left, insertval);
    } else if (root->key < insertval) {
        root->right = insert(root->right, insertval);
    }
    return root;
}

bool search(Node* root, int searchval) {
    if (root == NULL) {
        return false;
    }
    if (root->key == searchval) {
        return true;
    } else if (root->key > searchval) {
        return search(root->left, searchval);
    } else {
        return search(root->right, searchval);
    }
}

struct Node* deleteNode(Node* root, int deleteval) {
    if (root == NULL) {
        return NULL;
    }
    if (root->key > deleteval) {
        root->left = deleteNode(root->left, deleteval);
    } else if (root->key < deleteval) {
        root->right = deleteNode(root->right, deleteval);
    } else {
        // Node to be deleted found
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Node* parent = root;
        Node* y = root->right;
        while (y != NULL && y->left != NULL) {
            parent = y;
            y = y->left;
        }

        // Copy the inorder successor's content to this node
        root->key = y->key;

        // Delete the inorder successor
        if (parent->left == y) {
            parent->left = y->right;
        } else {
            parent->right = y->right;
        }

        delete y;
    }
    return root;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;

    struct Node* root = NULL;

    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        root = insert(root, val);
    }

    cout << "15 : " << search(root, 15) << endl;
    cout << "25 : " << search(root, 25) << endl;
    cout << "50 : " << search(root, 50) << endl;

    inorder(root);
    cout << endl;

    int del;
    cin >> del;
    root = deleteNode(root, del);
    cout << "after deleting : " << del << endl;

    inorder(root);
    cout << endl;
    return 0;
}
