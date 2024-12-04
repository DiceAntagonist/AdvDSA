#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int randomizedSelect(int[], int, int, int);
int randomizedPartition(int[], int, int);
int partition(int[], int, int);

int randomizedSelect(int arr[], int p, int r, int k) {
    if (p == r) {
        return arr[p];
    }

    int q = randomizedPartition(arr, p, r); 
    int left = q - p + 1; 
    
    if (k == left) {
        return arr[q]; // Found the k-th smallest element
    } else if (k < left) {
        return randomizedSelect(arr, p, q - 1, k); 
    } else {
        return randomizedSelect(arr, q + 1, r, k - left); // Recurse on the right
    }
}

int randomizedPartition(int arr[], int p, int r) {
    int i = p + rand() % (r - p + 1); 
    swap(arr[i], arr[r]); 
    return partition(arr, p, r);
}

int partition(int arr[], int p, int r) {
    int pivot = arr[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[r]);
    return i + 1;
}

int main() {
    srand(time(0)); 

    int n, k;
    cout << "Enter the number of elements: ";
    cin >> n;

    int arr[n];
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Enter the value of k (1-based index): ";
    cin >> k;

    if (k < 1 || k > n) {
        cout << "Invalid value of k!" << endl;
        return 1;
    }

    int kthSmallest = randomizedSelect(arr, 0, n - 1, k);
    cout << "The " << k << "-th smallest element is: " << kthSmallest << endl;

    return 0;
}
