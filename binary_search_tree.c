#include <stdio.h> 
#include <stdlib.h> 

struct node  
{ 
    int key; 
    struct node *left, *right; 
}; 

struct node *newNode(int item)   // Create a node 
{ 
    struct node *temp = (struct node *)malloc(sizeof(struct node)); 
    temp->key = item; 
    temp->left = temp->right = NULL; 
    return temp; 
} 

struct node *searchNode(struct node *, int) ; 
void inorder(struct node *); 
struct node *insert(struct node *, int); 
struct node *minValueNode(struct node *); 
struct node *deleteNode(struct node *, int); 

int main()  
{ 
    struct node *root = NULL; 
    root = insert(root, 8); 
    root = insert(root, 3); 
    root = insert(root, 1); 
    root = insert(root, 6); 
    root = insert(root, 7); 
    root = insert(root, 10); 
    root = insert(root, 14); 
    root = insert(root, 4); 
    printf("After inserting:\n"); 
    printf("Elements in the BINARY SEARCH TREE in their INORDER form: "); 
    inorder(root); 
    printf("\n\nAfter deleting 10\n"); 
    root = deleteNode(root, 10); 
    inorder(root); 
    printf("\n\nSearching for 7....."); 
    searchNode(root,7); 
    printf("\n\nSearching for 4....."); 
    searchNode(root,4); 
    printf("\n\nAfter deleting 6\n"); 
    root = deleteNode(root, 6); 
    inorder(root); 
    return 0;  
} 

void inorder(struct node *root)   // Inorder Traversal 
{ 
    if (root != NULL) 
    { 
        inorder(root->left); 
        printf("%d  ", root->key); 
        inorder(root->right); 
    } 
} 

struct node *insert(struct node *node, int key)  // Insert a node 
{ 
    if (node == NULL)  
        return newNode(key);   // Return a new node if the tree is empty 
    if (key < node->key) 
        node->left = insert(node->left, key); 
    else 
        node->right = insert(node->right, key); 
    return node; 
} 

struct node *minValueNode(struct node *node)  // Find the inorder successor  
{ 
    struct node *current = node; 
    while (current && current->left != NULL)  // Find the leftmost leaf 
        current = current->left; 
    return current; 
} 

struct node *deleteNode(struct node *root, int key)  // Deleting a node 
{ 
    if (root == NULL)  
        return root; 
    if (key < root->key) 
        root->left = deleteNode(root->left, key); 
    else if (key > root->key) 
        root->right = deleteNode(root->right, key); 
    else  
    { 
        if (root->left == NULL)   // If the node is with only one child or no child 
        { 
            struct node *temp = root->right; 
            free(root); 
            return temp; 
        }  
        else if (root->right == NULL)  
        { 
            struct node *temp = root->left; 
            free(root); 
            return temp; 
        } 
        struct node *temp = minValueNode(root->right);  // If the node has two children 
        root->key = temp->key; // Place the inorder successor in position of the node to be deleted 
        root->right = deleteNode(root->right, temp->key);  // Delete the inorder successor 
    } 
    return root; 
} 

struct node *searchNode(struct node *root, int key)  
{ 
    if (root == NULL)  
        return NULL; 
    if (key == root->key)  
        printf("\nElement %d found in the BST",root->key); 
    if (key< root->key) 
        return searchNode(root->left,key); 
    if (key > root->key ) 
        return searchNode(root->right,key); 
}
