#include <bits/stdc++.h>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

int sequentialMin(vector<int> &arr)
{
    int min_val = arr[0];
    for (int i = 1; i < arr.size(); i++)
    {
        if (arr[i] < min_val)
        {
            min_val = arr[i];
        }
    }
    return min_val;
}

int sequentialMax(vector<int> &arr)
{
    int max_val = arr[0];
    for (int i = 1; i < arr.size(); i++)
    {
        if (arr[i] > max_val)
        {
            max_val = arr[i];
        }
    }
    return max_val;
}

int sequentialSum(vector<int> &arr)
{
    int sum = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    return sum;
}

double sequentialAverage(vector<int> &arr)
{
    return (double)sequentialSum(arr) / (double)arr.size();
}

int ParallelMin(vector<int> &arr)
{
    int minvalue = arr[0];
#pragma omp parallel for reduction(min : minvalue)
    for (int i = 1; i < arr.size(); i++)
    {
        if (minvalue > arr[i])
        {
            minvalue = arr[i];
        }
    }

    return minvalue;
}

int ParallelMax(vector<int> &arr)
{
    int maxvalue = arr[0];
#pragma omp parallel for reduction(max : maxvalue)

    for (int i = 1; i < arr.size(); i++)
    {
        if (maxvalue < arr[i])
        {
            maxvalue = arr[i];
        }
    }
    return maxvalue;
}

int ParallelSum(vector<int> &arr)
{
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    return sum;
}
double ParallelAverage(vector<int> &arr)
{
    return (double)ParallelSum(arr) / (double)arr.size();
}
void generateRandomNumbers(vector<int> &arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
    }
}

int main()
{
    cout << "Enter the number of elements you want in the array : ";
    int n;
    cin >> n;
    vector<int> arr(n);
    generateRandomNumbers(arr, n);

    auto start = high_resolution_clock::now();
    cout << sequentialMax(arr) << " ";
    auto end = high_resolution_clock::now();
    auto result = end - start;
    cout << "Time for sequential Max  " << result.count() << endl;

    start = high_resolution_clock::now();
    cout << ParallelMax(arr) << " ";
    end = high_resolution_clock::now();
    auto result1 = end - start;
    cout << "Time for Parallel Max " << result1.count() << endl;

    start = high_resolution_clock::now();
    cout << sequentialMin(arr) << " ";
    end = high_resolution_clock::now();
    auto result2 = end - start;
    cout << "Time for sequential Min " << result2.count() << endl;

    start = high_resolution_clock::now();
    cout << ParallelMin(arr) << " ";
    end = high_resolution_clock::now();
    auto result3 = end - start;
    cout << "Time for Parallel Min " << result3.count() << endl;

    start = high_resolution_clock::now();
    cout << sequentialSum(arr) << " ";
    end = high_resolution_clock::now();
    auto result4 = end - start;
    cout << "Time for sequential sum " << result4.count() << endl;

    start = high_resolution_clock::now();
    cout << ParallelSum(arr) << " ";
    end = high_resolution_clock::now();
    auto result5 = end - start;
    cout << "Time for Parallel sum " << result5.count() << endl;

    start = high_resolution_clock::now();
    cout << sequentialAverage(arr) << " ";
    end = high_resolution_clock::now();
    auto result6 = end - start;
    cout << "Time for sequential Average " << result6.count() << endl;

    start = high_resolution_clock::now();
    cout << ParallelAverage(arr) << " ";
    end = high_resolution_clock::now();
    auto result7 = end - start;
    cout << "Time for Parallel Average " << result7.count() << endl;
}