#include <iostream>
#include <cstdlib>

using namespace std;

void quicksort(int[], int, int);
int rpartition(int[], int, int);
int partition(int[], int, int);

int partitioncount = 0;
int comparisoncount = 0;

void quicksort (int arr[], int p, int r){
    int q;
    if (p<r){
        q = rpartition(arr, p, r);
        quicksort(arr, q-1, r);
        quicksort(arr, q+1, r);
    }
    
  
    
};

int rpartition (int arr[], int p, int r){
    partitioncount++;
    int i = p + rand()%(r-p+1);
    swap(arr[i], arr[r]);
    return partition (arr, p, r);
};

int partition (int arr[], int p, int r){
    int pivot = arr[r];
    int i = p - 1;
    for(int j =1; j < r; j++){
        comparisoncount++;
        if(arr[j]<pivot){
            i++;
            swap(arr[j], arr[i]);
           
        }
    }
    
    swap(arr[i+1], arr[r]);
    return i+1;
}

int main(){
    int arr[6];
    cout<<"Enter numbers";
    for(int i = 0; i<6; i++){
        cin>>arr[i];
    }
    int p = 0;
    int r = 5;
    
    quicksort(arr, p, r);
      for(int i = p; i<r; i++){
    cout<<" "<<arr[i];}
}



