#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *leftChild;
    struct node *rightChild;
    struct node *root = NULL;
};

void insert(int);
void preorder(struct node*);
void postorder(struct node*);
void inorder(struct node*);

int main()
{
    int i;
    int array[7] = { 27, 14, 35, 10, 19, 31, 42 };
    for(i = 0; i < 7; i++)
    {
        insert(array[i]);
    }
    printf("BINARY TREE Elements are:\n");
    for(i = 0; i < 7; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n\nPREORDER TRAVERSAL: ");
    preorder(root);
    printf("\n\nINORDER TRAVERSAL: ");
    inorder(root);
    printf("\n\nPOSTORDER TRAVERSAL: ");
    postorder(root);
    return 0;
}

void insert(int data)
{
    struct node *tempNode = (struct node*) malloc(sizeof(struct node));
    struct node *current;
    struct node *parent;
    tempNode->data = data;
    tempNode->leftChild = NULL;
    tempNode->rightChild = NULL;

    if(root == NULL) // if tree is empty
    {
        root = tempNode;
    }
    else
    {
        current = root;
        parent = NULL;
        while(1)
        {
            parent = current;
            if(data < parent->data) // go to left of the tree
            {
                current = current->leftChild;
                if(current == NULL) // insert to the left
                {
                    parent->leftChild = tempNode;
                    return;
                }
            }
            else // go to right of the tree
            {
                current = current->rightChild;
                if(current == NULL) // insert to the right
                {
                    parent->rightChild = tempNode;
                    return;
                }
            }
        }
    }
}

void preorder(struct node* root)
{
    if(root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->leftChild);
        preorder(root->rightChild);
    }
}

void inorder(struct node* root)
{
    if(root != NULL)
    {
        inorder(root->leftChild);
        printf("%d ", root->data);
        inorder(root->rightChild);
    }
}

void postorder(struct node* root)
{
    if(root != NULL)
    {
        postorder(root->leftChild);
        postorder(root->rightChild);
        printf("%d ", root->data);
    }
}
