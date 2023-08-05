// Jomikael Ruiz
// lab5.cpp
// May 19th, 2023
// Purpose: Testing and implementation of sorting algorithms
// specifically: heap, merge, quick sort functinos

#include <iostream>
#include <chrono>
using namespace std;

// printing arrays for testing
void printArray(int * A, int n) {
    for(int i = 0; i < n; i++) {
        cout << A[i] << endl;
    }
}

// swapping function to swap array values
void swap(int & one, int & two) {
    int temp = one;
    one = two;
    two = temp;
}

// percolate up to form a heap
void percolateUp(int * A, int i) {
    int parentIndex = (i - 1) / 2;
    if(i == 0) {
        return;
    }
    if(A[i] > A[parentIndex]) {
        return;
    } else {
        swap(A[i], A[parentIndex]);
        percolateUp(A, parentIndex);
    }
}

// takes in an array and percolates up after each insertion
void insertHeap(int * A, int n) {
    int * temp = new int[n];
    for(int i = 0; i < n; i++) {
        temp[i] = A[i];
        percolateUp(temp, i);
    }
    for(int i = 0; i < n; i++) {
        A[i] = temp[i];
    }
    delete [] temp;
}

// takes in an array and rebalances the heap starting at index 1
void percolateDown(int * A, int index, int size) {
    int leftIndex = ((2*index) + 1);
    int rightIndex = ((2*index) + 2);
    if(leftIndex >= size) {
        return;
    }
    if(rightIndex >= size && A[index] < A[leftIndex]) {
        return;
    }
    if(A[index] < A[leftIndex] && A[index] < A[rightIndex]) {
        return;
    } else {
        if(A[index] > A[leftIndex] && A[leftIndex] < A[rightIndex]) {
            swap(A[index], A[leftIndex]);
            percolateDown(A, leftIndex, size);
        } else {
            swap(A[index], A[rightIndex]);
            percolateDown(A, rightIndex, size);
        }
    }
}

// deleteMin that removes the root of a heap and rebalances the tree
int deleteMin(int * A, int n) {
    int temp = A[0];
    swap(A[0], A[n-1]);
    percolateDown(A, 0, n-1);
    return temp;
}

// calls deleteMin to sort an array of N elements 
void heapSort(int * A, int n) {
    insertHeap(A, n);
    int * tempHeap = new int[n];
    for(int i = 0; i < n; i++) {
        tempHeap[i] = deleteMin(A,n-i);
    }
    for(int i = 0; i < n; i++) {
        A[i] = tempHeap[i];
    }
}

// merge function that merges together and sorts two sections of an array
void merge(int * A, int p, int q, int r) {
    // creation of new array and temp vars
    int * array = new int[r-p+1];
    int pCount = p;
    int qCount = q+1;
    int arrCount = 0;
    // while loop that makes sure p and q dont go over their maxs
    while(pCount <= q && qCount <= r) {
        // if statement tree to see if p or q is greater and inserts into arr
        // then increments their respective count variables
        if(A[pCount] < A[qCount]) {
            array[arrCount] = A[pCount];
            pCount++;
            arrCount++;
        } else if(A[qCount] < A[pCount]){
            array[arrCount] = A[qCount];
            qCount++;
            arrCount++;
        } else {
            array[arrCount] = A[qCount];
            arrCount++;
            array[arrCount] = A[pCount];
            arrCount++;
            qCount++;
            pCount++;
        }
    }
    // if p goes over boundary, insert rest of q into array
    if(pCount > q) {
        while(qCount <= r) {
            array[arrCount] = A[qCount];
            arrCount++;
            qCount++;
        }
    } 
    // else insert rest of p
    else if(qCount > r) {
        while(pCount <= q) {
            array[arrCount] = A[pCount];
            arrCount++;
            pCount++;
        }
    }
    arrCount = 0;
    // inserts new array into the parameter array
    for(int i = p; i <= r; i++) {
        A[i] = array[arrCount];
        arrCount++;
    }
    // deallocation
    delete [] array;
}

// calls merge and sorts out all sections of the array using 
// the merge algorithm
void mergeSort(int * A, int i, int j) {
    if(i < j) {
        int mid = (i+j)/2;
        mergeSort(A, i , mid);
        mergeSort(A, mid+1, j);
        merge(A,i,mid,j);
    } else {
        return;
    }
}

// mergeSort function that takes in only array and size
void mergeSort(int * A, int n) {
    mergeSort(A, 0, n-1);
}

// partition function for quicksort that sorts out array into S1, S2 based on pivot
int partition(int * A, int i, int j) {
    int p = A[i];
    int m = i;
    for(int k = i+1; k <= j; k++) {
        // if a value is less than pivot, adds value to S1
        if(A[k] <= p) {
            m++;
            swap(A[k], A[m]);
        }
    }
    // places the pivot in the correct place and return its index
    swap(A[m], A[i]);
    return m;
}

// obtains a random index for the pivot position then calls partition
int randomized_partition(int * a, int i, int j) {
    int pos = i + rand() % (j-i+1);
    swap(a[i], a[pos]);
    return partition(a, i, j);
}

// quickSort function that organizes an array based on the partition function
// and obtains a random pivot from randomized_partition
void quickSort(int * A, int i, int j) {
    if(i < j) {
        int pivotIndex = randomized_partition(A, i, j);
        quickSort(A, i, pivotIndex-1);
        quickSort(A, pivotIndex+1, j);
    }
}

// quicksort function that takes in an array and size and calls other quickSort
void quickSort(int * A, int n) {
    quickSort(A, 0, n-1);
}

// measureSort function that takes in a function pointer and measures the time
// it takes to run each sorting function against each other
void measureSort(void(*sortingFunction)(int *, int)) {
    int size[] = {10, 100, 1000, 10000, 100000};
    for(int i = 0; i < 5; i++) {
        int * array = new int[size[i]];
        for(int j = 0; j < size[i]; j++) {
            array[j] = rand() % 100000;
        }
        if(size[i] == 10) {
            cout << "Random Array: " << endl;
            printArray(array, size[i]);
        }
        auto start = std::chrono::high_resolution_clock ::now();
        sortingFunction(array, size[i]);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = stop - start;
        auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
        if(size[i] == 10) {
            cout << "Sorted Array: " << endl;
            printArray(array, size[i]);
        }
        cout << "Array Size " << size[i] << " duration ";
        cout << duration_ns.count() << " ns." << endl;
    }
}

int main() {
    void(*sortingFunction)(int *, int);

    cout << endl << "HEAP SORT" << endl;
    sortingFunction = &heapSort;
    measureSort(sortingFunction);

    cout << endl << "MERGE SORT" << endl;
    sortingFunction = &mergeSort;
    measureSort(sortingFunction);

    cout << endl << "QUICK SORT" << endl;
    sortingFunction = &quickSort;
    measureSort(sortingFunction);

    return 0;
}
