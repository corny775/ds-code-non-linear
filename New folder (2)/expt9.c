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
#define INITIAL 1
#define VISITED 2
#define FINISHED 3
int n;
int adj[MAX][MAX];
int state[MAX];
int time;
int d[MAX];
int f[MAX];
void displayAdjacencyMatrix();
void create_graph();
void DF_Traversal();
void DFS(int v);
void BFS(int start);
void display();
void recursiveDFS(int v);
int main()
{
    footer();
    create_graph();
    int choice, start;
    while (1)
    {
        printf("\n1. Perform BFS\n");
        printf("2. Perform DFS\n");
        printf("3. Perform Recursive DFS\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter starting vertex for BFS: ");
            scanf("%d", &start);
            BFS(start);
            break;
        case 2:
            printf("Enter starting vertex for DFS: ");
            scanf("%d", &start);
            DF_Traversal();
            break;
        case 3:
            printf("Enter starting vertex for Recursive DFS: ");
            scanf("%d", &start);

            for (int i = 0; i < n; i++)
                state[i] = INITIAL;
            time = 0;
            recursiveDFS(start);
            printf("\n");
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice.\n");
            break;
        }
    }
    return 0;
}
void create_graph()
{
    int max_edges, origin, destin;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            adj[i][j] = 0;
        }
    }
    max_edges = n * (n - 1);
    for (int i = 1; i <= max_edges; i++)
    {
        printf("Enter edge %d ( -1 -1 to quit ): ", i);
        scanf("%d %d", &origin, &destin);
        if ((origin == -1) && (destin == -1))
            break;
        if (origin >= n || destin >= n || origin < 0 || destin < 0)
        {
            printf("Invalid vertex!\n");
            i--;
        }
        else
        {
            adj[origin][destin] = 1;
        }
    }
    displayAdjacencyMatrix();
}
void displayAdjacencyMatrix()
{
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }
}
void DF_Traversal()
{
    int v;
    for (v = 0; v < n; v++)
        state[v] = INITIAL;
    printf("Enter starting vertex for Depth First Search: ");
    scanf("%d", &v);
    DFS(v);
    for (v = 0; v < n; v++)
    {
        if (state[v] == INITIAL)
        {
            DFS(v);
        }
    }
    for (v = 0; v < n; v++)
    {
        printf("Vertex %d, Discovery Time: %d, Finishing Time: %d\n", v, d[v], f[v]);
    }
}
void DFS(int v)
{
    state[v] = VISITED;
    time++;
    d[v] = time;
    printf("%d ", v);
    for (int i = 0; i < n; i++)
    {
        if (adj[v][i] == 1 && state[i] == INITIAL)
        {
            DFS(i);
        }
    }
    state[v] = FINISHED;
    f[v] = ++time;
}
void BFS(int start)
{
    int queue[MAX], front = -1, rear = -1;
    int v;
    for (int i = 0; i < n; i++)
        state[i] = INITIAL;
    queue[++rear] = start;
    state[start] = VISITED;
    printf("BFS Traversal: ");
    while (front != rear)
    {
        front++;
        v = queue[front];
        printf("%d ", v);
        for (int i = 0; i < n; i++)
        {
            if (adj[v][i] == 1 && state[i] == INITIAL)
            {
                queue[++rear] = i;
                state[i] = VISITED;
            }
        }
    }
    printf("\n");
}
void recursiveDFS(int v)
{
    state[v] = VISITED;
    time++;
    d[v] = time;
    printf("%d ", v);
    for (int i = 0; i < n; i++)
    {
        if (adj[v][i] == 1 && state[i] == INITIAL)
        {
            recursiveDFS(i);
        }
    }
    state[v] = FINISHED;
    f[v] = ++time;
}