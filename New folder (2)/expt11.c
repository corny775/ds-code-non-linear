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
#define MAX 7
enum status
{
    Occupied,
    Empty,
    Deleted
};
struct employee
{
    int id;
    enum status s;
};
struct record
{
    struct employee info;
    struct record *next;
};
struct employee arr1[MAX], arr2[MAX], arr3[MAX];
struct record *arr4[MAX];
void start()
{
    for (int i = 0; i < MAX; i++)
    {
        arr1[i].s = Empty;
        arr2[i].s = Empty;
        arr3[i].s = Empty;
        arr4[i] = NULL;
    }
}
int hash1(int key)
{
    return key % MAX;
}
int hash2(int key)
{
    return key % 5 + 1;
}
void display()
{
    printf("%-16s %-16s %-16s %s\n", "liner", "quadratic", "double hash", "chaining");
    for (int i = 0; i < MAX; i++)
    {
        if (arr1[i].s == Occupied)
            printf("\n[%d] %-12d ", i, arr1[i].id);
        else
            printf("\n[%d] %-13s", i, "empty");
        if (arr2[i].s == Occupied)
            printf("[%d] %-12d ", i, arr2[i].id);
        else
            printf("[%d] %-13s", i, "empty");

        if (arr3[i].s == Occupied)
            printf("[%d] %-12d ", i, arr3[i].id);
        else
            printf("[%d] %-13s", i, "empty");
        struct record *tmp = arr4[i];
        printf("[%d] | %p |->", i, tmp);
        while (tmp != NULL)
        {
            printf("| %d | %p |->", tmp->info.id, tmp->next);
            tmp = tmp->next;
        }
    }
}
int linearHash(struct employee emp)
{
    int i = 0, n;
    printf("\nlinear probing:\n");
    while (i <= MAX)
    {
        n = (hash1(emp.id) + i) % MAX;
        printf("%d=(%d)%%%d + %d\n", n, emp.id, MAX, i);
        if (arr1[n].id == emp.id)
        {
            printf("found\n");
            return n;
        }
        else if (arr1[n].s == Occupied)
        {
            i++;
            continue;
        }
        arr1[n] = emp;
        return n;
    }
    printf("collision detected in linear\n");
    return -1;
}
int quadraticHash(struct employee emp)
{
    int i = 0, n;
    printf("\nquadratic probing:\n");
    while (i <= MAX)
    {
        n = (hash1(emp.id) + i * i) % MAX;
        printf("%d=(%d)%%%d + %d*%d\n", n, emp.id, MAX, i, i);
        if (arr2[n].id == emp.id)
        {
            printf("found\n");
            return n;
        }
        else if (arr2[n].s == Occupied)
        {
            i++;
            continue;
        }
        emp.s = Occupied;
        arr2[n] = emp;
        return n;
    }
    printf("collision detected in quadratic\n");
    return -1;
}
int doubleHash(struct employee emp)
{
    int i = 0, n;
    printf("\ndouble hashing:\n");
    while (i <= MAX)
    {
        n = (hash1(emp.id) + hash2(emp.id) * i) % MAX;
        printf("%d=(%d)%%%d + (%d)%%%d*%d\n", n, emp.id, MAX, emp.id, 5, i);
        if (arr3[n].id == emp.id)
        {
            printf("found\n");
            return n;
        }
        else if (arr3[n].s == Occupied)
        {
            i++;
            continue;
        }
        emp.s = Occupied;
        arr3[n] = emp;
        return n;
    }
    printf("collision detected in double hashing\n");
    return -1;
}
void insertChaining(struct employee emp)
{
    int n;
    n = hash1(emp.id);
    printf("\nseparete chaining:\n");
    printf("%d=(%d)%%%d\n", n, emp.id, MAX);
    struct record *tmp;
    tmp = (struct record *)malloc(sizeof(struct record));
    tmp->info = emp;
    tmp->next = arr4[n];
    arr4[n] = tmp;
}
void insert()
{
    struct employee emp;
    int n1, n2, n3;
    printf("enter value ");
    scanf("%d", &emp.id);
    emp.s = Occupied;
    n1 = linearHash(emp);
    n2 = quadraticHash(emp);
    n3 = doubleHash(emp);
    insertChaining(emp);
    if (n1 > -1)
        arr1[n1] = emp;
    if (n2 > -1)
        arr2[n2] = emp;
    if (n3 > -1)
        arr3[n3] = emp;
    display();
}
void delete()
{
    struct employee emp;
    struct record *tmp, *t;
    int n1, n2, n3, n4;
    printf("enter value ");
    scanf("%d", &emp.id);
    emp.s = Deleted;
    n1 = linearHash(emp);
    n2 = quadraticHash(emp);
    n3 = doubleHash(emp);
    n4 = hash1(emp.id);
    if (n1 > -1)
        arr1[n1] = emp;
    if (n2 > -1)
        arr2[n2] = emp;
    if (n3 > -1)
        arr3[n3] = emp;
    tmp = arr4[n4];
    if (tmp->info.id == emp.id)
    {
        arr4[n4] = tmp->next;
        free(tmp);
        return;
    }
    while (tmp->next != NULL)
    {
        if (tmp->next->info.id == emp.id)
        {
            t = tmp->next;
            tmp->next = t->next;
            free(t);
            return;
        }
        tmp = tmp->next;
    }
}
int main()
{
    footer();
    int n = 1;
    start();
    while (n != 9)
    {
        printf("\n\n1:insert\n2:delete\n3:display hash table\n9:exit\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            insert();
            break;
        case 2:
            delete ();
            break;
        case 3:
            display();
            break;
        }
    }
}