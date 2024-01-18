#include <iostream>

using namespace std;

void merge(int* arr, int start, int mid, int end) {
    int i = 0;
    int j = 0;
    int k = start;  // Initialize k with the starting index
    
    int size1 = mid - start + 1;
    int size2 = end - mid;

    int array1[size1];
    int array2[size2];

    // Copy data to temporary arrays array1[] and array2[]
    for (i = 0; i < size1; i++)
        array1[i] = arr[start + i];
    for (j = 0; j < size2; j++)
        array2[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;

    while (i < size1 && j < size2) {
        if (array1[i] <= array2[j]) {
            arr[k] = array1[i];
            i++;
        } else {
            arr[k] = array2[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of array1[], if there are any
    while (i < size1) {
        arr[k] = array1[i];
        i++;
        k++;
    }

    // Copy the remaining elements of array2[], if there are any
    while (j < size2) {
        arr[k] = array2[j];
        j++;
        k++;
    }
}

void mergeSort(int* arr, int start, int end) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

int main() {
    int size = 6;
    int arr[] = {12,23,10,45,31,22};
    mergeSort(arr, 0, size - 1);

    cout << "Sorted Array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}