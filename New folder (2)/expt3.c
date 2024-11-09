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
struct treenode *insert(struct treenode *ptr, int key)
{
    if (ptr == NULL)
    {
        ptr = (struct treenode *)malloc(sizeof(struct treenode));
        ptr->info = key;
        ptr->lchild = NULL;
        ptr->rchild = NULL;
    }
    else if (key < ptr->info)
    {
        ptr->lchild = insert(ptr->lchild, key);
    }
    else if (key > ptr->info)
    {
        ptr->rchild = insert(ptr->rchild, key);
    }
    else
    {
        printf("Duplicate key\n");
    }
    return ptr;
}
struct treenode *search(struct treenode *ptr, int key)
{
    if (ptr == NULL || ptr->info == key)
        return ptr;
    if (key < ptr->info)
        return search(ptr->lchild, key);
    return search(ptr->rchild, key);
}
struct treenode *del(struct treenode *ptr, int dkey)
{
    if (ptr == NULL)
    {
        printf("%d not present in the tree\n", dkey);
        return ptr;
    }
    if (dkey < ptr->info)
        ptr->lchild = del(ptr->lchild, dkey);
    else if (dkey > ptr->info)
        ptr->rchild = del(ptr->rchild, dkey);
    else
    {
        if (ptr->lchild != NULL && ptr->rchild != NULL)
        {
            struct treenode *succ = ptr->rchild;
            while (succ->lchild != NULL)
                succ = succ->lchild;
            ptr->info = succ->info;
            ptr->rchild = del(ptr->rchild, succ->info);
        }
        else
        {
            struct treenode *tmp = ptr;
            ptr = (ptr->lchild != NULL) ? ptr->lchild : ptr->rchild;
            free(tmp);
        }
    }
    return ptr;
}
struct treenode *min_key(struct treenode *ptr)
{
    if (ptr == NULL)
        return NULL;
    else if (ptr->lchild == NULL)
        return ptr;
    else
        return min_key(ptr->lchild);
}
struct treenode *max_key(struct treenode *ptr)
{
    if (ptr == NULL)
        return NULL;
    else if (ptr->rchild == NULL)
        return ptr;
    else
        return max_key(ptr->rchild);
}
void displayTree(struct treenode *root)
{
    if (root != NULL)
    {
        displayTree(root->lchild);
        printf("%d ", root->info);
        displayTree(root->rchild);
    }
}
int main()
{
    footer();
    struct treenode *tree = NULL;
    int choice, value;
    while (1)
    {
        printf("1. Insert\n2. Delete\n3. Search\n4. Display\n5. Find Min\n6. Find Max\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            tree = insert(tree, value);
            break;
        case 2:
            printf("Enter value to delete: ");
            scanf("%d", &value);
            tree = del(tree, value);
            break;
        case 3:
            printf("Enter value to search: ");
            scanf("%d", &value);
            struct treenode *found = search(tree, value);
            if (found)
            {
                printf("%d found in the tree.\n", value);
            }
            else
            {
                printf("%d not found in the tree.\n", value);
            }
            break;
        case 4:
            printf("Tree (In-Order Traversal): ");
            displayTree(tree);
            printf("\n");
            break;
        case 5:
        {
            struct treenode *minNode = min_key(tree);
            if (minNode)
            {
                printf("Minimum value in tree: %d\n", minNode->info);
            }
            else
            {
                printf("Tree is empty.\n");
            }
        }
        break;
        case 6:
        {
            struct treenode *maxNode = max_key(tree);
            if (maxNode)
            {
                printf("Maximum value in tree: %d\n", maxNode->info);
            }
            else
            {
                printf("Tree is empty.\n");
            }
        }
        break;
        case 7:
            exit(0);
        default:
            printf("Invalid choice.\n");
        }
    }
    return 0;
}