#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define slen 100
int PR_NUM = 202311094;
char ROLL_NUM[] = "23B-CO-016";
void footer()
{
    printf("\n______________________________\n");
    printf("PR NUMBER: %d\n", PR_NUM);
    printf("ROLL NUMBER: %s", ROLL_NUM);
    printf("\n-------------------------------\n\n");
}
void bubble_sort(char arr[][slen], int n);
void insertion_sort(char arr[][slen], int n);
void selection_sort(char arr[][slen], int n);
void shell_sort(char arr[][slen], int n);
void merge_sort(char arr[][slen], int low, int high);
void merge(char arr[][slen], int low, int mid, int high);
void heap_sort(char arr[][slen], int n);
void heapify(char arr[][slen], int n, int i);
void quick_sort(char arr[][slen], int low, int high);
int partition(char arr[][slen], int low, int high);
void display(char arr[][slen], int n);
int main()
{
    footer();
    int n, choice;
    char arr[MAX][slen];
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++)
    {
        printf("Enter element %d: ", i + 1);
        fgets(arr[i], slen, stdin);
        arr[i][strcspn(arr[i], "\n")] = 0;
    }
    while (1)
    {
        printf("Choose sorting algorithm:\n");
        printf("1. Bubble Sort\n2. Insertion Sort\n3. Selection Sort\n");
        printf("4. Shell Sort\n5. Merge Sort\n6. Heap Sort\n7. Quick Sort\n");
        printf("Enter your choice (1-7) and 8 to exit: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            bubble_sort(arr, n);
            break;
        case 2:
            insertion_sort(arr, n);
            break;
        case 3:
            selection_sort(arr, n);
            break;
        case 4:
            shell_sort(arr, n);
            break;
        case 5:
            merge_sort(arr, 0, n - 1);
            break;
        case 6:
            heap_sort(arr, n);
            break;
        case 7:
            quick_sort(arr, 0, n - 1);
            break;
        case 8:
            exit(0);
        default:
            printf("Invalid choice\n");
            continue;
        }
        printf("Sorted list is:\n");
        display(arr, n);
    }
    return 0;
}
void bubble_sort(char arr[][slen], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (strcmp(arr[j], arr[j + 1]) > 0)
            {
                char temp[slen];
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j + 1]);
                strcpy(arr[j + 1], temp);
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
}
void insertion_sort(char arr[][slen], int n)
{
    for (int i = 1; i < n; i++)
    {
        char key[slen];
        strcpy(key, arr[i]);
        int j = i - 1;
        while (j >= 0 && strcmp(arr[j], key) > 0)
        {
            strcpy(arr[j + 1], arr[j]);
            j--;
        }
        strcpy(arr[j + 1], key);
    }
}
void selection_sort(char arr[][slen], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (strcmp(arr[j], arr[min_idx]) < 0)
                min_idx = j;
        if (min_idx != i)
        {
            char temp[slen];
            strcpy(temp, arr[i]);
            strcpy(arr[i], arr[min_idx]);
            strcpy(arr[min_idx], temp);
        }
    }
}
void shell_sort(char arr[][slen], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            char temp[slen];
            strcpy(temp, arr[i]);
            int j = i;
            while (j >= gap && strcmp(arr[j - gap], temp) > 0)
            {
                strcpy(arr[j], arr[j - gap]);
                j -= gap;
            }
            strcpy(arr[j], temp);
        }
    }
}
void merge_sort(char arr[][slen], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}
void merge(char arr[][slen], int low, int mid, int high)
{
    int i = low, j = mid + 1, k = low;
    char temp[MAX][slen];
    while (i <= mid && j <= high)
    {
        if (strcmp(arr[i], arr[j]) <= 0)
            strcpy(temp[k++], arr[i++]);
        else
            strcpy(temp[k++], arr[j++]);
    }
    while (i <= mid)
        strcpy(temp[k++], arr[i++]);
    while (j <= high)
        strcpy(temp[k++], arr[j++]);
    for (i = low; i <= high; i++)
        strcpy(arr[i], temp[i]);
}
void heap_sort(char arr[][slen], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--)
    {
        char temp[slen];
        strcpy(temp, arr[0]);
        strcpy(arr[0], arr[i]);
        strcpy(arr[i], temp);
        heapify(arr, i, 0);
    }
}
void heapify(char arr[][slen], int n, int i)
{
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < n && strcmp(arr[left], arr[largest]) > 0)
        largest = left;
    if (right < n && strcmp(arr[right], arr[largest]) > 0)
        largest = right;
    if (largest != i)
    {
        char temp[slen];
        strcpy(temp, arr[i]);
        strcpy(arr[i], arr[largest]);
        strcpy(arr[largest], temp);
        heapify(arr, n, largest);
    }
}
void quick_sort(char arr[][slen], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}
int partition(char arr[][slen], int low, int high)
{
    char pivot[slen];
    strcpy(pivot, arr[high]);
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (strcmp(arr[j], pivot) <= 0)
        {
            i++;
            char temp[slen];
            strcpy(temp, arr[i]);
            strcpy(arr[i], arr[j]);
            strcpy(arr[j], temp);
        }
    }
    char temp[slen];
    strcpy(temp, arr[i + 1]);
    strcpy(arr[i + 1], arr[high]);
    strcpy(arr[high], temp);
    return i + 1;
}
void display(char arr[][slen], int n)
{
    for (int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
}