// Jomikael Ruiz
// lab2.cpp
// March 31st, 2023
// Purpose: Creating a Pascal's Triangle to
// return the desired binomial coefficient

#include <iostream>
#include <chrono>
using namespace std::chrono;

const char SPACE = ' ';

// creates the Pascal Triangle
int ** iterativePascal(int n, int i);
// prints the values of the triangle
void printTriangle(int ** triangle, int rows);
// gets user input for the degree and index
void getInput(int & n, int & i);
// prints the binomial coefficient at index
void printResult(int ** triangle, int n, int i);
// frees up memory and deletes the pointer
void deleteTriangle(int ** triangle, int n);
// function that calls recursiveBico() to fill Pascal's triangle
int ** recursivePascal(int degree, int index);
// recursive function that finds the value of pascal's triangle
int recursiveBico(int degree, int index);


int main() {
    int degree, index;
    getInput(degree, index);
    auto start = high_resolution_clock::now();
    int ** iPascal = iterativePascal(degree, index);
//    int ** rPascal = recursivePascal(degree,index);
    auto stop = high_resolution_clock::now();
    auto duration = stop - start;
    auto duration_ns = duration_cast<nanoseconds>(duration);
    std:: cout << duration_ns.count() << std::endl;
    std::cout << "Recursive Pascal's" << std::endl;
//    printTriangle(rPascal, degree);
    std::cout << std::endl << "Iterative Pascal's" << std::endl;
    printTriangle(iPascal, degree);
//    printResult(rPascal, degree, index);
    deleteTriangle(iPascal, degree);
//    deleteTriangle(rPascal, degree);
    return 0;
}

int ** iterativePascal(int n, int i) {
    int ** pascal = new int*[n+1];
    for(int index = 0; index <= n; index++) {
        pascal[index] = new int[n+1];
    }
    for(int index = 0; index <= n; index++) {
        for(int j = 0; j <= index; j++) {
            if(j == index) {
                pascal[index][j] = 1;
            } else if(j == 0) {
                pascal[index][j] = 1;
            } else {
                pascal[index][j] = pascal[index-1][j-1] + pascal[index-1][j];
            }
        }
    }
    return pascal;
}

int recursiveBico(int degree, int index) {
    if(degree == index) return 1;
    if(index == 0) return 1;
    if(degree == 0) return 1;
    return recursiveBico(degree - 1, index - 1) + recursiveBico(degree - 1, index);
}

int ** recursivePascal(int degree, int index) {
    int ** pascal = new int*[degree+1];
    for(int i = 0; i <= degree; i++) {
        pascal[i] = new int[degree+1];
    }
    for(int i = 0; i <= degree; i++) {
        for(int j = 0; j <= i; j++) {
            pascal[i][j] = recursiveBico(i,j);
        }
    }
    return pascal;
}

void printTriangle(int ** triangle, int rows) {
    for(int i = 0; i <= rows; i++) {
        for(int j = 0; j <= i; j++) {
            std::cout << triangle[i][j] << SPACE;
        }
        std::cout << std::endl;
    }
}

void getInput(int & n, int & i) {
    std::cout << std::endl << std::endl;
    std::cout << "Please input the degree of the binomial: ";
    std::cin >> n;
    std::cout << "Please input the index of the coefficient: ";
    std::cin >> i;
}

void printResult(int ** triangle, int n, int i) {
    std::cout << "The result is: " << triangle[n][i] << std::endl << std::endl;
}

void deleteTriangle(int ** triangle, int n) {
    for(int i = 0; i <= n; i++) {
        delete [] triangle[i];
    }
    delete [] triangle;
}
