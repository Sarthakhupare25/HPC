#include <bits/stdc++.h>
#include <omp.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

void bubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

}

void parallelbubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
#pragma omp for 
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }


}

void generateRandomNumbers(vector<int> &arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i]=rand() % 1000;
    }
}

void Merge(int l,int r,int mid,vector<int> &arr){
    int start=l,end=mid+1;
    vector<int> temp;
    while(start<=mid && end<=r){
        if(arr[start]<arr[end]){
            temp.push_back(arr[start]);
            start++;
        }else{
            temp.push_back(arr[end]);
            end++;
        }
    }
    while(start<=mid){
        temp.push_back(arr[start]);
        start++;
    }
    while(end<=r){
        temp.push_back(arr[end]);
        end++;
    }
    for(int i=l;i<=r;i++){
        arr[i]=temp[i-l];
    }
}
void MergeSort(int l,int r,vector<int> &arr){
    if(l<r){
        int mid=(l+r)/2;
        MergeSort(l,mid,arr);
        MergeSort(mid+1,r,arr);

        Merge(l,r,mid,arr);
    }
}

void ParallelMergeSort(int l,int r,vector<int> &arr){
    if(l<r){
        int mid=(l+r)/2;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                ParallelMergeSort(l,mid,arr);
            }
            #pragma omp section
            {
                ParallelMergeSort(mid+1,r,arr);
            }

        }
        Merge(l,r,mid,arr);
    }
}
int main()
{
    cout << "Enter the number of elements you want in the array: ";
    int n;
    cin >> n;
    vector<int> arr(n);
    generateRandomNumbers(arr, n);

    auto start = high_resolution_clock::now();
    bubbleSort(arr);
    auto end = high_resolution_clock::now();
    auto result1 = end - start;
    cout << "Time for sequential bubble sort is : " << result1.count() << endl;

    start = high_resolution_clock::now();
    parallelbubbleSort(arr);
    end = high_resolution_clock::now();
    auto result2 = end - start;
    cout << "Time for parallel bubble sort is : " << result2.count() << endl;

    start = high_resolution_clock::now();
    MergeSort(0,n-1,arr);
    end = high_resolution_clock::now();
    auto result3 = end - start;
    cout << "Time for Merge sort is : " << result3.count() << endl;
    generateRandomNumbers(arr,n);

    start = high_resolution_clock::now();
    ParallelMergeSort(0,n-1,arr);
    end = high_resolution_clock::now();
    auto result4 = end - start;
    cout << "Time for parallel Merge sort is : " << result4.count() << endl;

    return 0;
}