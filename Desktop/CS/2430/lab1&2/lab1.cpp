// Jomikael Ruiz
// lab1.cpp
// March 31st, 2023
// Purpose: Creating a Pascal's Triangle to  
// return the desired binomial coefficient

#include <iostream>
using namespace std;

const char SPACE = ' ';

// creates the Pascal Triangle
int ** bico(int n);
// prints the values of the triangle
void printTriangle(int ** triangle, int rows);
// gets user input for the degree and index
void getInput(int & n, int & i);
// prints the binomial coefficient at index
void printResult(int ** triangle, int n, int i);
// frees up memory and deletes the pointer
void deleteTriangle(int ** triangle, int n);


int main() {
    int n, i;
    int ** pascalTriangle = nullptr;
    getInput(n, i);
    pascalTriangle = bico(n);
    printTriangle(pascalTriangle, n);
    printResult(pascalTriangle, n, i);
    deleteTriangle(pascalTriangle, n);
    return 0;
}

int ** bico(int n) {
    int ** pascal = new int*[n+1];
    for(int i = 0; i <= n; i++) {
        pascal[i] = new int[n+1];
    }
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= i; j++) {
            if(j == i) {
                pascal[i][j] = 1;
            } else if(j == 0) {
                pascal[i][j] = 1;
            } else {
                pascal[i][j] = pascal[i-1][j-1] + pascal[i-1][j];
            }
        }
    }
    return pascal;
}

void printTriangle(int ** triangle, int rows) {
    for(int i = 0; i <= rows; i++) {
        for(int j = 0; j <= i; j++) {
            cout << triangle[i][j] << SPACE;
        }
        cout << endl;
    }
}

void getInput(int & n, int & i) {
    cout << endl << endl;
    cout << "Please input the degree of the binomial: ";
    cin >> n;
    cout << "Please input the index of the coefficient: ";
    cin >> i;
}

void printResult(int ** triangle, int n, int i) {
    cout << "The result is: " << triangle[n][i] << endl << endl;
}

void deleteTriangle(int ** triangle, int n) {
    for(int i = 0; i <= n; i++) {
        delete [] triangle[i];
    }
    delete [] triangle;
}