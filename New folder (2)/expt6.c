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
struct node
{
    int info;
    struct node *lchild;
    struct node *rchild;
    int balance;
};
struct node *insert(struct node *pptr, int ikey, int *taller);
struct node *del(struct node *pptr, int dkey);
void display(struct node *ptr, int level);
struct node *rotateLeft(struct node *pptr);
struct node *rotateRight(struct node *pptr);
struct node *insert_LeftBalance(struct node *pptr);
struct node *insert_RightBalance(struct node *pptr);
struct node *del_LeftBalance(struct node *pptr, int *shorter);
struct node *del_RightBalance(struct node *pptr, int *shorter);
struct node *del_left_check(struct node *pptr, int *shorter);
struct node *del_right_check(struct node *pptr, int *shorter);
struct node *insert_left_check(struct node *pptr, int *taller);
struct node *insert_right_check(struct node *pptr, int *taller);
struct node *rotateLeft(struct node *pptr)
{
    struct node *aptr = pptr->rchild;
    pptr->rchild = aptr->lchild;
    aptr->lchild = pptr;
    return aptr;
}
struct node *rotateRight(struct node *pptr)
{
    struct node *aptr = pptr->lchild;
    pptr->lchild = aptr->rchild;
    aptr->rchild = pptr;
    return aptr;
}
struct node *insert_LeftBalance(struct node *pptr)
{
    struct node *aptr = pptr->lchild, *bptr;
    if (aptr->balance == 1)
    {
        pptr->balance = 0;
        aptr->balance = 0;
        pptr = rotateRight(pptr);
    }
    else
    {
        bptr = aptr->rchild;
        switch (bptr->balance)
        {
        case -1:
            pptr->balance = 0;
            aptr->balance = 1;
            break;
        case 1:
            pptr->balance = -1;
            aptr->balance = 0;
            break;
        case 0:
            pptr->balance = 0;
            aptr->balance = 0;
            break;
        }
        bptr->balance = 0;
        pptr->lchild = rotateLeft(aptr);
        pptr = rotateRight(pptr);
    }
    return pptr;
}
struct node *insert_RightBalance(struct node *pptr)
{
    struct node *aptr = pptr->rchild, *bptr;
    if (aptr->balance == -1)
    {
        pptr->balance = 0;
        aptr->balance = 0;
        pptr = rotateLeft(pptr);
    }
    else
    {
        bptr = aptr->lchild;
        switch (bptr->balance)
        {
        case -1:
            pptr->balance = 1;
            aptr->balance = 0;
            break;
        case 1:
            pptr->balance = 0;
            aptr->balance = -1;
            break;
        case 0:
            pptr->balance = 0;
            aptr->balance = 0;
            break;
        }
        bptr->balance = 0;
        pptr->rchild = rotateRight(aptr);
        pptr = rotateLeft(pptr);
    }
    return pptr;
}
struct node *insert_left_check(struct node *pptr, int *taller)
{
    switch (pptr->balance)
    {
    case 0:
        pptr->balance = 1;
        break;
    case -1:
        pptr->balance = 0;
        *taller = 0;
        break;
    case 1:
        pptr = insert_LeftBalance(pptr);
        *taller = 0;
        break;
    }
    return pptr;
}
struct node *insert_right_check(struct node *pptr, int *taller)
{
    switch (pptr->balance)
    {
    case 0:
        pptr->balance = -1;
        break;
    case 1:
        pptr->balance = 0;
        *taller = 0;
        break;
    case -1:
        pptr = insert_RightBalance(pptr);
        *taller = 0;
        break;
    }
    return pptr;
}
struct node *insert(struct node *pptr, int ikey, int *taller)
{
    if (pptr == NULL)
    {
        pptr = (struct node *)malloc(sizeof(struct node));
        if (pptr == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        pptr->info = ikey;
        pptr->lchild = NULL;
        pptr->rchild = NULL;
        pptr->balance = 0;
        *taller = 1;
        printf("Inserted %d\n", ikey);
    }
    else if (ikey < pptr->info)
    {
        pptr->lchild = insert(pptr->lchild, ikey, taller);
        if (*taller)
            pptr = insert_left_check(pptr, taller);
    }
    else if (ikey > pptr->info)
    {
        pptr->rchild = insert(pptr->rchild, ikey, taller);
        if (*taller)
            pptr = insert_right_check(pptr, taller);
    }
    else
    {
        printf("Duplicate key not allowed.\n");
        *taller = 0;
    }
    return pptr;
}
struct node *del_LeftBalance(struct node *pptr, int *shorter)
{
    struct node *aptr = pptr->lchild, *bptr;
    if (aptr->balance == 0)
    {
        pptr->balance = 1;
        aptr->balance = -1;
        *shorter = 0;
        pptr = rotateRight(pptr);
    }
    else if (aptr->balance == 1)
    {
        pptr->balance = 0;
        aptr->balance = 0;
        pptr = rotateRight(pptr);
    }
    else
    {
        bptr = aptr->rchild;
        switch (bptr->balance)
        {
        case 0:
            pptr->balance = 0;
            aptr->balance = 0;
            break;
        case 1:
            pptr->balance = -1;
            aptr->balance = 0;
            break;
        case -1:
            pptr->balance = 0;
            aptr->balance = 1;
            break;
        }
        bptr->balance = 0;
        pptr->lchild = rotateLeft(aptr);
        pptr = rotateRight(pptr);
    }
    return pptr;
}
struct node *del_RightBalance(struct node *pptr, int *shorter)
{
    struct node *aptr = pptr->rchild, *bptr;
    if (aptr->balance == 0)
    {
        pptr->balance = -1;
        aptr->balance = 1;
        *shorter = 0;
        pptr = rotateLeft(pptr);
    }
    else if (aptr->balance == -1)
    {
        pptr->balance = 0;
        aptr->balance = 0;
        pptr = rotateLeft(pptr);
    }
    else
    {
        bptr = aptr->lchild;
        switch (bptr->balance)
        {
        case 0:
            pptr->balance = 0;
            aptr->balance = 0;
            break;
        case -1:
            pptr->balance = 1;
            aptr->balance = 0;
            break;
        case 1:
            pptr->balance = 0;
            aptr->balance = -1;
            break;
        }
        bptr->balance = 0;
        pptr->rchild = rotateRight(aptr);
        pptr = rotateLeft(pptr);
    }
    return pptr;
}
struct node *del(struct node *pptr, int dkey)
{
    static int shorter;
    struct node *tmp, *succ;
    if (pptr == NULL)
    {
        printf("Key not found\n");
        shorter = 0;
        return pptr;
    }
    if (dkey < pptr->info)
    {
        pptr->lchild = del(pptr->lchild, dkey);
        if (shorter)
            pptr = del_left_check(pptr, &shorter);
    }
    else if (dkey > pptr->info)
    {
        pptr->rchild = del(pptr->rchild, dkey);
        if (shorter)
            pptr = del_right_check(pptr, &shorter);
    }
    else
    {
        if (pptr->lchild != NULL && pptr->rchild != NULL)
        {
            succ = pptr->rchild;
            while (succ->lchild != NULL)
                succ = succ->lchild;
            pptr->info = succ->info;
            pptr->rchild = del(pptr->rchild, succ->info);
            if (shorter)
                pptr = del_RightBalance(pptr, &shorter);
        }
        else
        {
            tmp = pptr;
            if (pptr->lchild == NULL)
                pptr = pptr->rchild;
            else if (pptr->rchild == NULL)
                pptr = pptr->lchild;
            free(tmp);
            shorter = 1;
        }
    }
    return pptr;
}
struct node *del_left_check(struct node *pptr, int *shorter)
{
    switch (pptr->balance)
    {
    case 1:
        pptr->balance = 0;
        break;
    case 0:
        pptr->balance = -1;
        *shorter = 0;
        break;
    case -1:
        pptr = del_LeftBalance(pptr, shorter);
        break;
    }
    return pptr;
}
struct node *del_right_check(struct node *pptr, int *shorter)
{
    switch (pptr->balance)
    {
    case -1:
        pptr->balance = 0;
        break;
    case 0:
        pptr->balance = 1;
        *shorter = 0;
        break;
    case 1:
        pptr = del_RightBalance(pptr, shorter);
        break;
    }
    return pptr;
}
void display(struct node *ptr, int level)
{
    if (ptr != NULL)
    {
        display(ptr->rchild, level + 1);
        for (int i = 0; i < level; i++)
        {
            printf("   ");
        }
        printf("%d\n", ptr->info);

        display(ptr->lchild, level + 1);
    }
    else if (level == 0)
    {
        printf("The tree is empty.\n");
    }
}
int main()
{
    footer();
    struct node *root = NULL;
    int choice, key;
    while (1)
    {
        printf("\nAVL Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter key to insert: ");
            scanf("%d", &key);
            int taller = 0;
            root = insert(root, key, &taller);
            break;
        case 2:
            printf("Enter key to delete: ");
            scanf("%d", &key);
            root = del(root, key);
            break;
        case 3:
            printf("AVL Tree Structure:\n");
            display(root, 0);
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice.\n");
        }
    }
    return 0;
}