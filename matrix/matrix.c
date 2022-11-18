#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
int MAX;

//Got help from Ujjwal Adhikari


void fillMatrix(int matrix[MAX][MAX]) {
    for(int i = 0; i<MAX; i++) {
        for(int j = 0; j<MAX; j++) {
            matrix[i][j] = rand()%10+1;
        }
    }
}

void printMatrix(int matrix[MAX][MAX]) {
    for(int i = 0; i<MAX; i++) {
        for(int j = 0; j<MAX; j++) {
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}



// Fetches the appropriate coordinates from the argument, and sets
// the cell of matSumResult at the coordinates to the sum of the
// values at the coordinates of matA and matB.


// Fetches the appropriate coordinates from the argument, and sets
// the cell of matSumResult at the coordinates to the difference of the
// values at the coordinates of matA and matB.


// Fetches the appropriate coordinates from the argument, and sets
// the cell of matSumResult at the coordinates to the inner product
// of matA and matB.


// Spawn a thread to fill each cell in each result matrix.
// How many threads will you spawn?
int main() {
    srand(time(0));  // Do Not Remove. Just ignore and continue below.
    
    // 0. Get the matrix size from the command line and assign it to MAX
    char input[3];
    printf("Enter the size of matrix: ");
    fgets(input, 3, stdin);
    MAX = atoi(input);

    int matA[MAX][MAX]; 
    int matB[MAX][MAX]; 

    int matSumResult[MAX][MAX];
    int matDiffResult[MAX][MAX]; 
    int matProductResult[MAX][MAX]; 

    struct args_t{
    int (*matA)[MAX];
    int (*matB)[MAX];
    int (*matC)[MAX];
    int row;

  };
    
    // 1. Fill the matrices (matA and matB) with random values.
    fillMatrix(matA);
    fillMatrix(matB);


    
    // 2. Print the initial matrices.
    printf("Matrix A:\n");
    printMatrix(matA);
    printf("Matrix B:\n");
    printMatrix(matB);
    
    // 3. Create pthread_t objects for our threads.
    pthread_t threads[MAX];
    struct args_t args[MAX];

    

    
    // 4. Create a thread for each cell of each matrix operation.
    void* computeSum(void* args) { // pass in the number of the ith thread
        struct args_t* arg = (struct args_t*) args;
        int position = arg->row * MAX;
        for (int i=0; i<MAX; i++){
          int result = arg->matA[0][i+position] + arg->matB[0][i+position];
          arg->matC[0][i+position] = result;

        }
    }

    // 
    // You'll need to pass in the coordinates of the cell you want the thread
    // to compute.
    // 
    // One way to do this is to malloc memory for the thread number i, populate the coordinates
    // into that space, and pass that address to the thread. The thread will use that number to calcuate 
    // its portion of the matrix. The thread will then have to free that space when it's done with what's in that memory.
    for (int i=0; i<MAX; i++){
      args[i].matA = matA;
      args[i].matB = matB;
      args[i].matC = matSumResult;
      args[i].row = i;
      pthread_create(&threads[i], NULL, &computeSum, (void*) &args[i]);
      // 5. Wait for all threads to finish.
      pthread_join(threads[i], NULL);
  }

    
    void* computeDiff(void* args) { // pass in the number of the ith thread
        struct args_t* arg = (struct args_t*) args;
        int position = arg->row * MAX;
        for (int i=0; i<MAX; i++){
          int result = arg->matA[0][i+position] - arg->matB[0][i+position];
          arg->matC[0][i+position] = result;

        }
    }

    // 
    // You'll need to pass in the coordinates of the cell you want the thread
    // to compute.
    // 
    // One way to do this is to malloc memory for the thread number i, populate the coordinates
    // into that space, and pass that address to the thread. The thread will use that number to calcuate 
    // its portion of the matrix. The thread will then have to free that space when it's done with what's in that memory.
    for (int i=0; i<MAX; i++){
      args[i].matA = matA;
      args[i].matB = matB;
      args[i].matC = matDiffResult;
      args[i].row = i;
      pthread_create(&threads[i], NULL, &computeDiff, (void*) &args[i]);
      // 5. Wait for all threads to finish.
      pthread_join(threads[i], NULL);
  }

    void* computeProduct(void* args) { // pass in the number of the ith thread
        struct args_t* arg = (struct args_t*) args;
        int position = arg->row * MAX;
        for (int i=0; i<MAX; i++){
          int result = arg->matA[0][i+position] * arg->matB[0][i+position];
          arg->matC[0][i+position] = result;

        }
    }

    // 
    // You'll need to pass in the coordinates of the cell you want the thread
    // to compute.
    // 
    // One way to do this is to malloc memory for the thread number i, populate the coordinates
    // into that space, and pass that address to the thread. The thread will use that number to calcuate 
    // its portion of the matrix. The thread will then have to free that space when it's done with what's in that memory.
    for (int i=0; i<MAX; i++){
      args[i].matA = matA;
      args[i].matB = matB;
      args[i].matC = matProductResult;
      args[i].row = i;
      pthread_create(&threads[i], NULL, &computeProduct, (void*) &args[i]);
      // 5. Wait for all threads to finish.
      pthread_join(threads[i], NULL);
  }
    
    
    // 6. Print the results.
    printf("Results:\n");
    printf("Sum:\n");
    printMatrix(matSumResult);
    printf("Difference:\n");
    printMatrix(matDiffResult);
    printf("Product:\n");
    printMatrix(matProductResult);
    return 0;
  
}