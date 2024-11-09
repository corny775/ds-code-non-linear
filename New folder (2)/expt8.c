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
struct Edge
{
    int dest;
    struct Edge *next;
};
struct Vertex
{
    int info;
    struct Edge *firstEdge;
    struct Vertex *nextVertex;
};
struct Vertex *start = NULL;
void insertVertex(int u);
void insertEdge(int origin, int destin);
void deleteEdge(int origin, int destin);
void deleteVertex(int u);
struct Vertex *findVertex(int u);
void displayGraph();
int main()
{
    footer();
    int choice, u, origin, destin;
    while (1)
    {
        printf("1. Insert a Vertex\n");
        printf("2. Insert an Edge\n");
        printf("3. Delete a Vertex\n");
        printf("4. Delete an Edge\n");
        printf("5. Display Graph\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter a vertex to be inserted: ");
            scanf("%d", &u);
            insertVertex(u);
            break;
        case 2:
            printf("Enter an edge to be inserted (origin destination): ");
            scanf("%d %d", &origin, &destin);
            insertEdge(origin, destin);
            break;
        case 3:
            printf("Enter a vertex to be deleted: ");
            scanf("%d", &u);
            deleteVertex(u);
            break;
        case 4:
            printf("Enter an edge to be deleted (origin destination): ");
            scanf("%d %d", &origin, &destin);
            deleteEdge(origin, destin);
            break;
        case 5:
            displayGraph();
            break;
        case 6:
            exit(0);
        default:
            printf("Wrong choice\n");
            break;
        }
    }
    return 0;
}
void insertVertex(int u)
{
    struct Vertex *newVertex = malloc(sizeof(struct Vertex));
    newVertex->info = u;
    newVertex->firstEdge = NULL;
    newVertex->nextVertex = NULL;
    if (start == NULL)
    {
        start = newVertex;
    }
    else
    {
        struct Vertex *temp = start;
        while (temp->nextVertex != NULL)
        {
            temp = temp->nextVertex;
        }
        temp->nextVertex = newVertex;
    }
}
void insertEdge(int origin, int destin)
{
    struct Vertex *locOrigin = findVertex(origin);
    struct Vertex *locDestin = findVertex(destin);
    if (locOrigin == NULL || locDestin == NULL)
    {
        printf("Invalid edge: One or both vertices not found.\n");
        return;
    }
    struct Edge *newEdge = malloc(sizeof(struct Edge));
    newEdge->dest = destin;
    newEdge->next = locOrigin->firstEdge;
    locOrigin->firstEdge = newEdge;
}
struct Vertex *findVertex(int u)
{
    struct Vertex *temp = start;
    while (temp != NULL)
    {
        if (temp->info == u)
        {
            return temp;
        }
        temp = temp->nextVertex;
    }
    return NULL;
}
void deleteEdge(int origin, int destin)
{
    struct Vertex *locOrigin = findVertex(origin);
    if (locOrigin == NULL)
    {
        printf("Origin vertex not found.\n");
        return;
    }
    struct Edge *current = locOrigin->firstEdge;
    struct Edge *prev = NULL;
    while (current != NULL)
    {
        if (current->dest == destin)
        {
            if (prev == NULL)
            {
                locOrigin->firstEdge = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current);
            printf("Edge (%d, %d) deleted.\n", origin, destin);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Edge (%d, %d) not found.\n", origin, destin);
}
void deleteVertex(int u)
{
    struct Vertex *temp = start;
    struct Vertex *prev = NULL;
    struct Vertex *curr = start;
    while (curr != NULL)
    {
        deleteEdge(curr->info, u);
        curr = curr->nextVertex;
    }
    while (temp != NULL)
    {
        if (temp->info == u)
        {
            if (prev == NULL)
            {
                start = temp->nextVertex;
            }
            else
            {
                prev->nextVertex = temp->nextVertex;
            }
            break;
        }
        prev = temp;
        temp = temp->nextVertex;
    }
    if (temp == NULL)
    {
        printf("Vertex %d not found.\n", u);
        return;
    }
    struct Edge *edge = temp->firstEdge;
    while (edge != NULL)
    {
        struct Edge *toDelete = edge;
        edge = edge->next;
        free(toDelete);
    }
    free(temp);
}
void displayGraph()
{
    struct Vertex *temp = start;
    if (temp == NULL)
    {
        printf("The graph is empty.\n");
        return;
    }
    printf("Graph (Adjacency List):\n");
    while (temp != NULL)
    {
        printf("%d -> ", temp->info);
        struct Edge *edge = temp->firstEdge;
        while (edge != NULL)
        {
            printf("%d ", edge->dest);
            edge = edge->next;
        }
        printf("\n");
        temp = temp->nextVertex;
    }
}