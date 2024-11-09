#include <stdio.h>
#include <stdlib.h>
int PR_NUM = 202311094;
char ROLL_NUM[] = "23B-CO-016";
void footer()
{
    printf("\n______________________________\n");
    printf("PR NUMBER: %d\n", PR_NUM);
    printf("ROLL NUMBER: %s", ROLL_NUM);
    printf("\n-------------------------------\n\n");
}
struct treenode
{
    int info;
    struct treenode *lchild;
    struct treenode *rchild;
};
struct treenode *insert(struct treenode *root, int key)
{
    struct treenode *newNode = (struct treenode *)malloc(sizeof(struct treenode));
    newNode->info = key;
    newNode->lchild = newNode->rchild = NULL;
    if (root == NULL)
    {
        return newNode;
    }
    struct treenode *parent = NULL;
    struct treenode *current = root;
    while (current != NULL)
    {
        parent = current;
        if (key < current->info)
        {
            current = current->lchild;
        }
        else if (key > current->info)
        {
            current = current->rchild;
        }
        else
        {
            printf("Duplicate key\n");
            free(newNode);
            return root;
        }
    }
    if (key < parent->info)
    {
        parent->lchild = newNode;
    }
    else
    {
        parent->rchild = newNode;
    }
    return root;
}
struct treenode *search(struct treenode *root, int key)
{
    struct treenode *current = root;
    while (current != NULL)
    {
        if (key == current->info)
        {
            return current;
        }
        else if (key < current->info)
        {
            current = current->lchild;
        }
        else
        {
            current = current->rchild;
        }
    }
    return NULL;
}
struct treenode *findMin(struct treenode *root)
{
    struct treenode *current = root;
    while (current && current->lchild != NULL)
    {
        current = current->lchild;
    }
    return current;
}
struct treenode *findMax(struct treenode *root)
{
    struct treenode *current = root;
    while (current && current->rchild != NULL)
    {
        current = current->rchild;
    }
    return current;
}
struct treenode *deleteNode(struct treenode *root, int key)
{
    struct treenode *parent = NULL;
    struct treenode *current = root;
    while (current != NULL && current->info != key)
    {
        parent = current;
        if (key < current->info)
        {
            current = current->lchild;
        }
        else
        {
            current = current->rchild;
        }
    }
    if (current == NULL)
    {
        printf("%d not found in the tree.\n", key);
        return root;
    }
    if (current->lchild == NULL)
    {
        if (current == root)
        {
            root = current->rchild;
        }
        else if (parent->lchild == current)
        {
            parent->lchild = current->rchild;
        }
        else
        {
            parent->rchild = current->rchild;
        }
    }
    else if (current->rchild == NULL)
    {
        if (current == root)
        {
            root = current->lchild;
        }
        else if (parent->lchild == current)
        {
            parent->lchild = current->lchild;
        }
        else
        {
            parent->rchild = current->lchild;
        }
    }
    else
    {
        struct treenode *successor = current->rchild;
        struct treenode *successorParent = current;
        while (successor->lchild != NULL)
        {
            successorParent = successor;
            successor = successor->lchild;
        }
        current->info = successor->info;
        if (successorParent->lchild == successor)
        {
            successorParent->lchild = successor->rchild;
        }
        else
        {
            successorParent->rchild = successor->rchild;
        }

        current = successor;
    }
    free(current);
    return root;
}
void inorder(struct treenode *root)
{
    struct treenode *stack[100];
    int top = -1;
    struct treenode *current = root;
    while (current != NULL || top != -1)
    {
        while (current != NULL)
        {
            stack[++top] = current;
            current = current->lchild;
        }
        current = stack[top--];
        printf("%d ", current->info);
        current = current->rchild;
    }
}
void preorder(struct treenode *root)
{
    if (root == NULL)
        return;
    struct treenode *stack[100];
    int top = -1;
    stack[++top] = root;
    while (top != -1)
    {
        struct treenode *current = stack[top--];
        printf("%d ", current->info);
        if (current->rchild != NULL)
            stack[++top] = current->rchild;
        if (current->lchild != NULL)
            stack[++top] = current->lchild;
    }
}
void postorder(struct treenode *root)
{
    if (root == NULL)
        return;
    struct treenode *stack1[100], *stack2[100];
    int top1 = -1, top2 = -1;
    stack1[++top1] = root;
    while (top1 != -1)
    {
        struct treenode *current = stack1[top1--];
        stack2[++top2] = current;
        if (current->lchild != NULL)
            stack1[++top1] = current->lchild;
        if (current->rchild != NULL)
            stack1[++top1] = current->rchild;
    }
    while (top2 != -1)
    {
        printf("%d ", stack2[top2--]->info);
    }
}
int main()
{
    footer();
    struct treenode *root = NULL;
    int choice, key;
    while (1)
    {
        printf("\n1. Insert\n2. Delete\n3. Search\n4. Inorder Traversal\n5. Preorder Traversal\n6. Postorder Traversal\n7. Find Min\n8. Find Max\n9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &key);
            root = insert(root, key);
            break;
        case 2:
            printf("Enter value to delete: ");
            scanf("%d", &key);
            root = deleteNode(root, key);
            break;
        case 3:
            printf("Enter value to search: ");
            scanf("%d", &key);
            if (search(root, key))
            {
                printf("%d found in the tree.\n", key);
            }
            else
            {
                printf("%d not found in the tree.\n", key);
            }
            break;
        case 4:
            printf("Inorder Traversal: ");
            inorder(root);
            printf("\n");
            break;
        case 5:
            printf("Preorder Traversal: ");
            preorder(root);
            printf("\n");
            break;
        case 6:
            printf("Postorder Traversal: ");
            postorder(root);
            printf("\n");
            break;
        case 7:
        {
            struct treenode *minNode = findMin(root);
            if (minNode)
            {
                printf("Minimum value in the tree: %d\n", minNode->info);
            }
            else
            {
                printf("Tree is empty.\n");
            }
        }
        break;
        case 8:
        {
            struct treenode *maxNode = findMax(root);
            if (maxNode)
            {
                printf("Maximum value in the tree: %d\n", maxNode->info);
            }
            else
            {
                printf("Tree is empty.\n");
            }
        }
        break;
        case 9:
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}