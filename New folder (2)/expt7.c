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
#define MAX_VERTICES 100
struct Edge
{
    int dest;
    struct Edge *next;
};
struct Vertex
{
    int info;
    struct Edge *firstEdge;
};
struct Vertex *vertices[MAX_VERTICES];
int adjMatrix[MAX_VERTICES][MAX_VERTICES];
int vertexCount = 0;
void insertVertex(int info)
{
    if (vertexCount >= MAX_VERTICES)
    {
        printf("Maximum vertices limit reached.\n");
        return;
    }
    struct Vertex *newVertex = malloc(sizeof(struct Vertex));
    newVertex->info = info;
    newVertex->firstEdge = NULL;
    vertices[vertexCount++] = newVertex;
}
void insertEdge(int origin, int destin)
{
    if (origin >= vertexCount || destin >= vertexCount || origin < 0 || destin < 0)
    {
        printf("Invalid vertex index.\n");
        return;
    }
    struct Edge *newEdge = malloc(sizeof(struct Edge));
    newEdge->dest = destin;
    newEdge->next = vertices[origin]->firstEdge;
    vertices[origin]->firstEdge = newEdge;
    adjMatrix[origin][destin] = 1;
}
void displayAdjacencyMatrix()
{
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < vertexCount; i++)
    {
        for (int j = 0; j < vertexCount; j++)
        {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}
void displayAdjacencyList()
{
    printf("Adjacency List:\n");
    for (int i = 0; i < vertexCount; i++)
    {
        printf("%d -> ", vertices[i]->info);
        struct Edge *edge = vertices[i]->firstEdge;
        while (edge != NULL)
        {
            printf("%d ", vertices[edge->dest]->info);
            edge = edge->next;
        }
        printf("\n");
    }
}
int main()
{
    footer();
    int choice, u, v;
    while (1)
    {
        printf("1. Insert Vertex\n");
        printf("2. Insert Edge\n");
        printf("3. Display Adjacency Matrix\n");
        printf("4. Display Adjacency List\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter vertex info: ");
            scanf("%d", &u);
            insertVertex(u);
            break;
        case 2:
            printf("Enter edge (origin destin): ");
            scanf("%d %d", &u, &v);
            insertEdge(u, v);
            break;
        case 3:
            displayAdjacencyMatrix();
            break;
        case 4:
            displayAdjacencyList();
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice.\n");
            break;
        }
    }
    return 0;
}