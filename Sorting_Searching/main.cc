#include <iostream>
#include <vector>
#include <algorithm> // For std::copy
#include <iterator>  // For std::ostream_iterator

using namespace std;

// QuickSort Algorithm
void quickSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pivot = arr[high]; // Choosing the last element as pivot
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            if (arr[j] < pivot)
            {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// MergeSort Algorithm
void merge(vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Binary Search Algorithm
int binarySearch(const vector<int> &arr, int target)
{
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid; // Target found
        else if (arr[mid] < target)
            left = mid + 1; // Search in the right half
        else
            right = mid - 1; // Search in the left half
    }
    return -1; // Target not found
}

int main()
{
    vector<int> items = {34, 7, 23, 32, 5, 62};

    // Sort using QuickSort
    cout << "Original array: ";
    copy(items.begin(), items.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    quickSort(items, 0, items.size() - 1);
    cout << "Sorted array using QuickSort: ";
    copy(items.begin(), items.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    // Reset and sort using MergeSort
    items = {34, 7, 23, 32, 5, 62};
    mergeSort(items, 0, items.size() - 1);
    cout << "Sorted array using MergeSort: ";
    copy(items.begin(), items.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    // Searching for an item
    int target = 23;
    int result = binarySearch(items, target);

    if (result != -1)
        cout << "Element " << target << " found at index: " << result << endl;
    else
        cout << "Element " << target << " not found." << endl;

    return 0;
}