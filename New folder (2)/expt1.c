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
#define MAX 100
struct listnode
{
    int info;
    struct listnode *next;
};
struct treenode
{
    int info;
    struct treenode *lchild;
    struct treenode *rchild;
};
struct treenode *stack[MAX];
int top = -1;
void push_stack(struct treenode *item)
{
    if (top == MAX - 1)
    {
        printf("Stack overflow.......\n");
        return;
    }
    top = top + 1;
    stack[top] = item;
}
struct treenode *pop_stack()
{
    struct treenode *item;
    if (top == -1)
    {
        printf("Stack underflow.......\n");
        exit(1);
    }
    item = stack[top];
    top = top - 1;
    return item;
}
int stack_empty()
{
    return (top == -1);
}
struct listnode *addatbeg(struct listnode *start, int data)
{
    struct listnode *temp = (struct listnode *)malloc(sizeof(struct listnode));
    temp->info = data;
    temp->next = start;
    return temp;
}
struct listnode *addatend(struct listnode *start, int data)
{
    struct listnode *temp = (struct listnode *)malloc(sizeof(struct listnode));
    temp->info = data;
    temp->next = NULL;
    if (start == NULL)
    {
        return temp;
    }
    struct listnode *p = start;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = temp;
    return start;
}
struct listnode *createll(struct listnode *start)
{
    int n, data, i;
    printf("Enter the number of nodes to be inserted: ");
    scanf("%d", &n);
    start = NULL;
    if (n == 0)
    {
        return start;
    }
    printf("Enter the first data: ");
    scanf("%d", &data);
    start = addatbeg(start, data);
    for (i = 1; i < n; i++)
    {
        printf("Enter the remaining data: ");
        scanf("%d", &data);
        start = addatend(start, data);
    }
    return start;
}
struct treenode *construct(struct listnode *postptr, struct listnode *inptr, int num)
{
    struct treenode *temp;
    struct listnode *p;
    int i, j;
    if (num == 0)
        return NULL;
    p = postptr;
    for (i = 0; i < num - 1; i++)
    {
        p = p->next;
    }
    temp = (struct treenode *)malloc(sizeof(struct treenode));
    temp->info = p->info;
    temp->lchild = NULL;
    temp->rchild = NULL;
    if (num == 1)
    {
        return temp;
    }
    struct listnode *q = inptr;
    for (i = 0; q != NULL && q->info != p->info; i++)
    {
        q = q->next;
    }
    temp->lchild = construct(postptr, inptr, i);
    for (j = 0; j < i; j++)
    {
        postptr = postptr->next;
    }
    temp->rchild = construct(postptr, q->next, num - i - 1);
    return temp;
}
void display(struct listnode *start)
{
    struct listnode *p = start;
    while (p != NULL)
    {
        printf("%d ", p->info);
        p = p->next;
    }
    printf("\n");
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
int countNodes(struct listnode *start)
{
    int count = 0;
    struct listnode *p = start;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }
    return count;
}
int tree_height(struct treenode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        int left_height = tree_height(root->lchild);
        int right_height = tree_height(root->rchild);
        return (left_height >= right_height) ? left_height + 1 : right_height + 1;
    }
}
void displaylevelorder(struct treenode *root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
    {
        printf("%d ", root->info);
    }
    else if (level > 1)
    {
        displaylevelorder(root->lchild, level - 1);
        displaylevelorder(root->rchild, level - 1);
    }
}
void levelorder(struct treenode *root)
{
    int i;
    int h = tree_height(root);
    for (i = 1; i <= h; i++)
    {
        displaylevelorder(root, i);
        printf("\n");
    }
}
void preorder(struct treenode *ptr)
{
    if (ptr == NULL)
        return;
    printf("%d ", ptr->info);
    preorder(ptr->lchild);
    preorder(ptr->rchild);
}
void inorder(struct treenode *ptr)
{
    if (ptr == NULL)
        return;
    inorder(ptr->lchild);
    printf("%d ", ptr->info);
    inorder(ptr->rchild);
}
void postorder(struct treenode *ptr)
{
    if (ptr == NULL)
        return;
    postorder(ptr->lchild);
    postorder(ptr->rchild);
    printf("%d ", ptr->info);
}
int main()
{
    footer();
    struct listnode *in_order = NULL;
    struct listnode *post_order = NULL;
    struct treenode *tree = NULL;
    printf("Creating In-Order List:\n");
    in_order = createll(in_order);
    printf("Creating Post-Order List:\n");
    post_order = createll(post_order);
    printf("In-Order List: ");
    display(in_order);
    printf("Post-Order List: ");
    display(post_order);
    int numNodes = countNodes(post_order);
    tree = construct(post_order, in_order, numNodes);
    printf("Constructed Tree (In-Order Traversal): ");
    displayTree(tree);
    printf("\n");
    int h = tree_height(tree);
    printf("The height of the tree: %d\n", h);
    printf("Level-Order Traversal:\n");
    levelorder(tree);
    printf("Pre-Order Traversal (Recursive):\n");
    preorder(tree);
    printf("\n");
    printf("In-Order Traversal (Recursive):\n");
    inorder(tree);
    printf("\n");
    printf("Post-Order Traversal (Recursive):\n");
    postorder(tree);
    printf("\n");
    return 0;
}