#include <stdio.h>
#define MAX 50
int PR_NUM = 202311094;
char ROLL_NUM[] = "23B-CO-016";
void footer()
{
    printf("\n______________________________\n");
    printf("PR NUMBER: %d\n", PR_NUM);
    printf("ROLL NUMBER: %s", ROLL_NUM);
    printf("\n-------------------------------\n\n");
}
int LinearSearch(int arr[], int n, int item);
int LinearSearchRecursive(int arr[], int n, int item, int index);
int BinarySearch(int arr[], int size, int item);
int BinarySearchRecursive(int arr[], int low, int up, int item);
int main() {
    footer();
    int i, n, item, arr[MAX], index;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    printf("Enter the elements: \n");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("Enter the item to be searched: ");
    scanf("%d", &item);
    index = LinearSearch(arr, n, item);
    if (index == -1)
        printf("%d not found in array (Linear Search)\n", item);
    else
        printf("%d found at position %d (Linear Search)\n", item, index);
    index = LinearSearchRecursive(arr, n, item, 0);
    if (index == -1)
        printf("%d not found in array (Recursive Linear Search)\n", item);
    else
        printf("%d found at position %d (Recursive Linear Search)\n", item, index);
    printf("Enter the elements (in sorted order) for Binary Search: \n");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    index = BinarySearch(arr, n, item);
    if (index == -1)
        printf("%d not found in array (Binary Search)\n", item);
    else
        printf("%d found at position %d (Binary Search)\n", item, index);
    index = BinarySearchRecursive(arr, 0, n - 1, item);
    if (index == -1)
        printf("%d not found in array (Recursive Binary Search)\n", item);
    else
        printf("%d found at position %d (Recursive Binary Search)\n", item, index);

    return 0;
}
int LinearSearch(int arr[], int n, int item) {
    int i = 0;
    while (i < n && item != arr[i])
        i++;
    if (i < n)
        return i;
    else
        return -1;
}
int LinearSearchRecursive(int arr[], int n, int item, int index) {
    if (index >= n)
        return -1;
    if (arr[index] == item)
        return index;
    return LinearSearchRecursive(arr, n, item, index + 1);
}
int BinarySearch(int arr[], int size, int item) {
    int low = 0, up = size - 1, mid;
    while (low <= up) {
        mid = (low + up) / 2;
        if (item > arr[mid])
            low = mid + 1;
        else if (item < arr[mid])
            up = mid - 1;
        else
            return mid;
    }
    return -1;
}
int BinarySearchRecursive(int arr[], int low, int up, int item) {
   int mid;
if( low > up)
return -1;
mid = (low+up)/2;
if(item > arr[mid])
BinarySearchRecursive(arr, mid+1, up, item);
else if( item < arr[mid] )
BinarySearchRecursive(arr, low, mid-1, item);
else
return mid;
}