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
    stack[++top] = item;
}
struct treenode *pop_stack()
{
    if (top == -1)
    {
        printf("Stack underflow.......\n");
        exit(1);
    }
    return stack[top--];
}
int stack_empty()
{
    return (top == -1);
}
struct treenode *queue[MAX];
int front = -1, rear = -1;
void insert_queue(struct treenode *item)
{
    if (rear == MAX - 1)
    {
        printf("Queue overflow.......\n");
        return;
    }
    if (front == -1)
    {
        front = 0;
    }
    queue[++rear] = item;
}
struct treenode *del_queue()
{
    if (front == -1 || front > rear)
    {
        printf("Queue underflow.......\n");
        exit(1);
    }
    return queue[front++];
}
int queue_empty()
{
    return (front == -1 || front > rear);
}
void nrec_preorder(struct treenode *root)
{
    if (root == NULL)
    {
        printf("Tree is empty\n");
        return;
    }
    push_stack(root);
    while (!stack_empty())
    {
        struct treenode *ptr = pop_stack();
        printf("%d ", ptr->info);
        if (ptr->rchild != NULL)
        {
            push_stack(ptr->rchild);
        }
        if (ptr->lchild != NULL)
        {
            push_stack(ptr->lchild);
        }
    }
    printf("\n");
}
void nrec_inorder(struct treenode *root)
{
    struct treenode *ptr = root;
    if (ptr == NULL)
    {
        printf("Tree is empty\n");
        return;
    }
    while (1)
    {
        while (ptr != NULL)
        {
            push_stack(ptr);
            ptr = ptr->lchild;
        }
        if (stack_empty())
        {
            break;
        }
        ptr = pop_stack();
        printf("%d ", ptr->info);
        ptr = ptr->rchild;
    }
    printf("\n");
}
void nrec_postorder(struct treenode *root)
{
    struct treenode *ptr = root;
    struct treenode *lastVisited = NULL;
    if (ptr == NULL)
    {
        printf("Tree is empty\n");
        return;
    }
    do
    {
        while (ptr != NULL)
        {
            push_stack(ptr);
            ptr = ptr->lchild;
        }
        while (ptr == NULL && !stack_empty())
        {
            ptr = stack[top];
            if (ptr->rchild == NULL || ptr->rchild == lastVisited)
            {
                printf("%d ", ptr->info);
                pop_stack();
                lastVisited = ptr;
                ptr = NULL;
            }
            else
            {
                ptr = ptr->rchild;
            }
        }
    } while (!stack_empty());
    printf("\n");
}
void level_trav(struct treenode *root)
{
    struct treenode *ptr = root;
    if (ptr == NULL)
    {
        printf("Tree is empty\n");
        return;
    }
    insert_queue(ptr);
    while (!queue_empty())
    {
        ptr = del_queue();
        printf("%d ", ptr->info);
        if (ptr->lchild != NULL)
        {
            insert_queue(ptr->lchild);
        }
        if (ptr->rchild != NULL)
        {
            insert_queue(ptr->rchild);
        }
    }
    printf("\n");
}
int height_nrec(struct treenode *root)
{
    if (root == NULL)
        return 0;
    struct treenode *temp = root;
    struct treenode *stack[MAX];
    int top = -1, height = 0;
    push_stack(temp);
    int currentHeight = 0;
    while (!stack_empty())
    {
        temp = pop_stack();
        currentHeight++;
        if (temp->lchild != NULL)
        {
            push_stack(temp->lchild);
        }
        if (temp->rchild != NULL)
        {
            push_stack(temp->rchild);
        }
        if (temp->lchild == NULL && temp->rchild == NULL)
        {
            if (currentHeight > height)
            {
                height = currentHeight;
            }
        }
        currentHeight--;
    }
    return height;
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
struct treenode *construct_tree(struct listnode *inorder, struct listnode *preorder, int num)
{
    if (num == 0)
        return NULL;
    struct treenode *node = (struct treenode *)malloc(sizeof(struct treenode));
    node->info = preorder->info;
    node->lchild = node->rchild = NULL;
    if (num == 1)
        return node;
    struct listnode *inPtr = inorder;
    int index = 0;
    while (inPtr != NULL && inPtr->info != preorder->info)
    {
        inPtr = inPtr->next;
        index++;
    }
    node->lchild = construct_tree(inorder, preorder->next, index);
    node->rchild = construct_tree(inPtr->next, preorder->next, num - index - 1);
    return node;
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
int main()
{
    footer();
    struct listnode *inorder = NULL;
    struct listnode *preorder = NULL;
    struct treenode *tree = NULL;
    printf("Creating In-Order List:\n");
    inorder = createll(inorder);
    printf("Creating Pre-Order List:\n");
    preorder = createll(preorder);
    printf("In-Order List: ");
    display(inorder);
    printf("Pre-Order List: ");
    display(preorder);
    int numNodes = countNodes(preorder);
    tree = construct_tree(inorder, preorder, numNodes);
    printf("Non-Recursive Pre-Order Traversal:\n");
    nrec_preorder(tree);
    printf("Non-Recursive In-Order Traversal:\n");
    nrec_inorder(tree);
    printf("Non-Recursive Post-Order Traversal:\n");
    nrec_postorder(tree);
    printf("Non-Recursive Level-Order Traversal:\n");
    level_trav(tree);
    int height = height_nrec(tree);
    printf("Height of the tree: %d\n", height);
    return 0;
}