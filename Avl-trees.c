#include <stdio.h> 
#include <stdlib.h> 

struct Node  
{ 
    int key; 
    struct Node *left, *right; 
    int height; 
}; 

int height(struct Node *N) { return N ? N->height : 0; } 
int max(int a, int b) { return (a > b) ? a : b; } 
int getBalance(struct Node *N) { return N ? height(N->left) - height(N->right) : 0; } 

struct Node* newNode(int key) // Create new node 
{ 
    struct Node* node = (struct Node*)malloc(sizeof(struct Node)); 
    node->key = key; 
    node->left = node->right = NULL; 
    node->height = 1; 
    return node; 
} 

struct Node* rightRotate(struct Node* y)  
{ 
    struct Node* x = y->left; 
    struct Node* T2 = x->right; 
    x->right = y; 
    y->left = T2; 
    y->height = max(height(y->left), height(y->right)) + 1; 
    x->height = max(height(x->left), height(x->right)) + 1; 
    return x; 
} 

struct Node* leftRotate(struct Node* x) 
{ 
    struct Node* y = x->right; 
    struct Node* T2 = y->left; 
    y->left = x; 
    x->right = T2; 
    x->height = max(height(x->left), height(x->right)) + 1; 
    y->height = max(height(y->left), height(y->right)) + 1; 
    return y; 
} 

struct Node* insert(struct Node* node, int key)  
{ 
    if (!node) return newNode(key); 
    if (key < node->key) 
        node->left = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key); 
    else 
        return node; // Duplicate keys not allowed 

    node->height = 1 + max(height(node->left), height(node->right)); // Update height 
    int balance = getBalance(node);    // Get balance factor 

    if (balance > 1 && key < node->left->key)    // Left Left Case 
        return rightRotate(node); 
    if (balance < -1 && key > node->right->key) // Right Right Case 
        return leftRotate(node); 
    if (balance > 1 && key > node->left->key)    // Left Right Case 
    { 
        node->left = leftRotate(node->left); 
        return rightRotate(node); 
    } 
    if (balance < -1 && key < node->right->key) // Right Left Case 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
    return node; 
} 

struct Node* minValueNode(struct Node* node) // Find node with minimum value (for deletion) 
{ 
    while (node && node->left) 
        node = node->left; 
    return node; 
} 

struct Node* deleteNode(struct Node* root, int key) // Delete a key 
{ 
    if (!root)  
        return root; 
    if (key < root->key) 
        root->left = deleteNode(root->left, key); 
    else if (key > root->key) 
        root->right = deleteNode(root->right, key); 
    else 
    { 
        if (!root->left || !root->right)        // Node to be deleted found 
        { 
            struct Node* temp = root->left ? root->left : root->right; 
            if (!temp) 
            { 
                temp = root; 
                root = NULL; 
            } 
            else 
                *root = *temp; 
            free(temp); 
        } 
        else 
        { 
            struct Node* temp = minValueNode(root->right); 
            root->key = temp->key; 
            root->right = deleteNode(root->right, temp->key); 
        } 
    } 

    if (!root)  
        return root; 

    root->height = 1 + max(height(root->left), height(root->right)); // Update height 
    int balance = getBalance(root); // Get balance factor 

    if (balance > 1 && getBalance(root->left) >= 0) // Left Left Case 
        return rightRotate(root);   
    if (balance > 1 && getBalance(root->left) < 0) // Left Right Case 
    { 
        root->left = leftRotate(root->left); 
        return rightRotate(root); 
    } 
    if (balance < -1 && getBalance(root->right) <= 0)    // Right Right Case 
        return leftRotate(root); 
    if (balance < -1 && getBalance(root->right) > 0) // Right Left Case 
    { 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    } 
    return root; 
} 

struct Node* search(struct Node* root, int key) // Search for a key 
{ 
    if (!root || root->key == key) 
        return root; 
    if (key < root->key) 
        return search(root->left, key); 
    return search(root->right, key); 
} 

void printPreOrder(struct Node* root) // Pre-order traversal 
{ 
    if (root)  
    { 
        printf("%d ", root->key); 
        printPreOrder(root->left); 
        printPreOrder(root->right); 
    } 
} 

int main()  
{ 
    struct Node* root = NULL; 
    root = insert(root, 2);  // Insertions 
    root = insert(root, 1); 
    root = insert(root, 7); 
    root = insert(root, 4); 
    root = insert(root, 5); 
    root = insert(root, 3); 
    root = insert(root, 8); 

    printf("AVL Tree (Pre-order): "); 
    printPreOrder(root); 

    int searchKey = 4; // Search 
    struct Node* found = search(root, searchKey); 
    printf("\n\nSearch for %d: %s\n", searchKey, found ? "Found" : "Not Found"); 

    root = deleteNode(root, 3); // Deletion 
    printf("\nAfter deleting 3: "); 
    printPreOrder(root); 

    searchKey = 3; // Search again 
    found = search(root, searchKey); 
    printf("\n\nSearch for %d after deletion: %s\n", searchKey, found ? "Found" : "Not Found"); 

    return 0; 
}
