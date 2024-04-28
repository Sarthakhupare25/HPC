
#include<iostream>
using namespace std;

__global__ void add(int *A, int *B, int *C, int size){
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if(tid < size){
        C[tid] = A[tid] +B[tid];
    }
}

void initialize(int *vector, int n){
    for(int i =0;i < n; i++){
        vector[i] = rand() % 20 +1;
    }
}

void print(int *vector, int size){
    for(int i = 0; i<size;i++){
        cout<<vector[i]<<" ";
    }
    cout<<endl;
}

int main(){
    int *A, *B, *C;
    int n = 4;
    int vectorSize = n;
    int vectorBytes = vectorSize * sizeof(int);

    A = new int[vectorSize];
    B = new int[vectorSize];
    C = new int[vectorSize];

    initialize(A, n);
    initialize(B, n);

    cout<<"A:\n";
    print(A, n);
    cout<<"B:\n";
    print(B, n);

    int *X, *Y, *Z;

    cudaMalloc(&X, vectorBytes);
    cudaMalloc(&Y, vectorBytes);
    cudaMalloc(&Z, vectorBytes);

    cudaMemcpy(X, A, vectorBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(Y, B, vectorBytes, cudaMemcpyHostToDevice);

    int threadperBlock = 256;
    int blocksperGrid = (n + threadperBlock - 1)/ threadperBlock;

    add<<<blocksperGrid, threadperBlock>>>(X, Y, Z, n);

    cudaMemcpy(C, Z, vectorBytes, cudaMemcpyDeviceToHost);

    cout<<"C:\n";
    print(C, n); 
    

    delete[] A;
    delete[] B;
    delete[] C;


    cudaFree(X);
    cudaFree(Y);
    cudaFree(Z);
    return 0;

}
// Commands to run
// nvcc filename.cu
// ./a.out