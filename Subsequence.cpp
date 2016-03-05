//
//  Subsequence.cpp
//  Lab8
//
//  Created by Jun Yuan on 2016-03-02.
//  Copyright © 2016 Jun Yuan. All rights reserved.
//  This program finds the starting index, the value, and number of the longest repeating integer subsequence with O(n) efficiency

#include <iostream>
#include <vector>
using namespace std;

// prints the starting index(1 based index according to assignment), the value, and the number of longest repeating subsequce of input vector
// prints the first sequence if there are ties
template <typename T>
void printLongestSubsequence(const vector<T>& v) {
    int maxSequence = 1;
    int currentSequence = 1;
    int index = 1;
    T value = v.at(0);
    // Linear time, scales proportional to vector size
    for (int i = 1; i < v.size(); i++) {
        if (v.at(i -1) == v.at(i)) {
            currentSequence++;
            if (currentSequence > maxSequence) { // change to >= to print the last sequence if there are ties
                maxSequence = currentSequence;
                value = v.at(i - maxSequence + 2);
                index = i - currentSequence + 2;
            }
        } else {
            currentSequence = 1;
        }
    }
    cout << "Your series of numbers ending with 0 is: ";
    for (unsigned i=0; i<v.size() ; i++)
    cout << ' ' << v[i];
    cout << '\n';
    cout << "The longest same number sequence starts at index " << index << " with " << maxSequence << " values of " << value << endl;;
}

int main(int argc, const char * argv[]) {
    vector<int> v;
    cout << "Enter numbers seperated by space with 0 as the terminating number: " << endl;
    int input;
    while (cin >> input) {
        v.push_back (input);
        if (v.back() == 0) {
            break;
        }
    }
    printLongestSubsequence(v);
    return 0;
}

