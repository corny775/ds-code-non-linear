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
void bubble_sort(int arr[], int n);
void insertion_sort(int arr[], int n);
void selection_sort(int arr[], int n);
void shell_sort(int arr[], int n);
void merge_sort(int arr[], int low, int high);
void merge(int arr[], int low, int mid, int high);
void heap_sort(int arr[], int n);
void heapify(int arr[], int n, int i);
void quick_sort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void display(int arr[], int n);
int main()
{
    footer();
    int i, n, arr[MAX], choice;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    printf("Choose sorting algorithm:\n");
    printf("1. Bubble Sort\n2. Insertion Sort\n3. Selection Sort\n");
    printf("4. Shell Sort\n5. Merge Sort\n6. Heap Sort\n7. Quick Sort\n");
    printf("Enter your choice (1-7) and 8 to exit: ");
    scanf("%d", &choice);
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
        printf("Invalid choice!\n");
        return 0;
    }
    printf("Sorted list in descending order is:\n");
    display(arr, n);
    return 0;
}
void bubble_sort(int arr[], int n)
{
    int i, j, temp, swapped;
    for (i = 0; i < n - 1; i++)
    {
        swapped = 0;
        for (j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
}
void insertion_sort(int arr[], int n)
{
    int i, j, key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] < key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
void selection_sort(int arr[], int n)
{
    int i, j, max_idx, temp;
    for (i = 0; i < n - 1; i++)
    {
        max_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] > arr[max_idx])
                max_idx = j;
        if (max_idx != i)
        {
            temp = arr[i];
            arr[i] = arr[max_idx];
            arr[max_idx] = temp;
        }
    }
}
void shell_sort(int arr[], int n)
{
    int gap, i, j, temp;
    for (gap = n / 2; gap > 0; gap /= 2)
    {
        for (i = gap; i < n; i++)
        {
            temp = arr[i];
            for (j = i; j >= gap && arr[j - gap] < temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}
void merge_sort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}
void merge(int arr[], int low, int mid, int high)
{
    int i = low, j = mid + 1, k = low;
    int temp[MAX];
    while (i <= mid && j <= high)
    {
        if (arr[i] >= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= high)
        temp[k++] = arr[j++];
    for (i = low; i <= high; i++)
        arr[i] = temp[i];
}
void heap_sort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}
void heapify(int arr[], int n, int i)
{
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}
void quick_sort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}
int partition(int arr[], int low, int high)
{
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] >= pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}
void display(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}