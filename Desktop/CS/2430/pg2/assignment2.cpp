// Jomikael Ruiz
// assignment2.cpp
// April 5th, 2023
// Purpose:

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

const int REMANUJAN_ONE = 6;
const int REMANUJAN_TWO = 2;
const int END_CASE = -1;
const int CONTINUE = 1;

int mysterySequence(int n);
int tennisBalls(int height);
string decToBase2(int num);
bool isDivisibleBy7(int num);
double remanujan(int depth, int first, int second);
int displayMenu();
int evaluateResult(int input);
void runTests();


int main() {
    int input = CONTINUE;
    while(input > 0) {
        input = displayMenu();
        input = evaluateResult(input);
    }
    return 0;
}

int mysterySequence(int n) {
    if(n <= 0) {
        return 2;
    } else if (n == 1) {
        return 3;
    } else {
        return mysterySequence(n-1) * mysterySequence(n-2);
    }
}

int tennisBalls(int height) {
    if(height <= 0) {
        return 0;
    }
    else if(height == 1) {
        return 1;
    } else {
        return height*height + tennisBalls(height-1);
    }
}

string decToBase2(int num) {
    if(num == 0) {
        return "0";
    } else if(num == 1) {
        return "1";
    } else {
        return decToBase2(num/2) + to_string(num % 2);
    }
}

bool isDivisibleBy7(int num) {
    if(num < 100 && num % 7 == 0) {
        return true;
    } else if(num < 100) {
        return false;
    } else {
        return isDivisibleBy7((num / 10) - (2 * (num % 10)));
    }
}

double remanujan(int depth, int first, int second) {
    if(depth == 0) {
        return 0;
    }
    return sqrt(first + second * remanujan(depth - 1, first + 1, second + 1));
}

void runTests() {
    int temp;
    double tempDouble;
    string tempString;
    cout << "Here are the results from testing mysterySequence:" << endl;
    temp = mysterySequence(0);
    cout << "n = 0: " << temp << endl;
    temp = mysterySequence(1);
    cout << "n = 1: " << temp << endl;
    temp = mysterySequence(4);
    cout << "n = 4: " << temp << endl;
    temp = mysterySequence(7);
    cout << "n = 7: " << temp << endl << endl;

    cout << "Here are the results from testing tennisBalls:" << endl;
    temp = tennisBalls(0);
    cout << "n = 0: " << temp << endl;
    temp = tennisBalls(1);
    cout << "n = 1: " << temp << endl;
    temp = tennisBalls(3);
    cout << "n = 3: " << temp << endl;
    temp = tennisBalls(10);
    cout << "n = 10: " << temp << endl << endl;

    cout << "Here are the results from testing decToBase2:" << endl;
    tempString = decToBase2(0);
    cout << "n = 0: " << tempString << endl;
    tempString = decToBase2(1);
    cout << "n = 1: " << tempString << endl;
    tempString = decToBase2(13);
    cout << "n = 13: " << tempString << endl;
    tempString = decToBase2(32);
    cout << "n = 32: " << tempString << endl;
    tempString = decToBase2(321);
    cout << "n = 321: " << tempString << endl << endl;

    cout << "Here are the results from testing isDivisibleBy7 (0 = false, 1 = true):" << endl;
    temp = isDivisibleBy7(1);
    cout << "n = 1: " << temp << endl;
    temp = isDivisibleBy7(7);
    cout << "n = 7: " << temp << endl;
    temp = isDivisibleBy7(31);
    cout << "n = 31: " << temp << endl;
    temp = isDivisibleBy7(1073);
    cout << "n = 1073: " << temp << endl;
    temp = isDivisibleBy7(1729);
    cout << "n = 1729: " << temp << endl << endl;

    cout << "Here are the results from testing Remanujan:" << endl;
    tempDouble = remanujan(1, REMANUJAN_ONE, REMANUJAN_TWO);
    cout << "n = 1: " << tempDouble << endl;
    tempDouble = remanujan(3, REMANUJAN_ONE, REMANUJAN_TWO);
    cout << "n = 3: " << tempDouble << endl;
    tempDouble = remanujan(10, REMANUJAN_ONE, REMANUJAN_TWO);
    cout << "n = 10: " << tempDouble << endl;
    tempDouble = remanujan(100, REMANUJAN_ONE, REMANUJAN_TWO);
    cout << "n = infinity: " << tempDouble << endl << endl;

}

int displayMenu() {
    int input;
    cout << "Welcome to the recursion assignment. What would you like to test?" << endl;
    cout << "1.\t mysterySequence" << endl;
    cout << "2.\t tennisBalls" << endl;
    cout << "3.\t decToBase2" << endl;
    cout << "4.\t isDivisibleBy7" << endl;
    cout << "5.\t remanujan" << endl;
    cout << "6.\t run Tests" << endl;
    cout << "7.\t Exit" << endl;
    cin >> input;
    return input;
}

int evaluateResult(int input) {
    int tempInput, result;
    string resultString;
    bool resultBool;
    double resultDouble;
    switch(input) {
        case 1:
            cout << "Mystery Sequence. Please enter n to compute the nth number in sequence: " << endl;
            cin >> tempInput;
            result = mysterySequence(tempInput);
            cout << "The " << tempInput << "th number in mystery sequence is 108" << endl;
            break;
        case 2:
            cout << "Tennis Balls. Please enter the height of the pyramid: " << endl;
            cin >> tempInput;
            result = tennisBalls(tempInput);
            cout << "A pyramid with " << tempInput << " levels holds " << result << " tennis balls." << endl;
            break;
        case 3:
            cout << "Decimal to Base 2. Please input any number to be converted: " << endl;
            cin >> tempInput;
            resultString = decToBase2(tempInput);
            cout << tempInput << " in Binary Base 2 is " << resultString << endl;
            break;
        case 4:
            cout << "isDivisibleBy7. Please input any number to check its divisiblity: " << endl;
            cin >> tempInput;
            resultBool = isDivisibleBy7(tempInput);
            if(resultBool) {
                cout << tempInput << " is divisible by 7" << endl;
            } else {
                cout << tempInput << " is not divisible by 7" << endl;
            }
            break;
        case 5:
            cout << "Remanujan. Enter integer depth: " << endl;
            cin >> tempInput;
            resultDouble = remanujan(tempInput, REMANUJAN_ONE, REMANUJAN_TWO);
            cout << "Result at depth 7: " << resultDouble << endl;
            resultDouble = remanujan(100, REMANUJAN_ONE, REMANUJAN_TWO);
            cout << "Result at infinite depth: " << resultDouble << endl;
            break;
        case 6:
            runTests();
            break;
        case 7:
            return END_CASE;
    }
    return CONTINUE;
}