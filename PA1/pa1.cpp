/*
 * CS237 Programming Assignment 1
 * Jens Myklebust & Joe Opseth
 * 18 February 2016
 *
 * Read two integers from the user as strings.
 * Convert the integers to vectors and add them.
 * Convert all three integers back to strings and
 * display the equation.
 */

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int charToDigit(char);
// convert a char between '0' and '9' to digit
// return -1 if char is not valid

char digitToChar(int);
// convert an int between 0 and 9 to char

vector<int> stringToVector(string);
// convert a string of digits into a vector of integers
// integers will be stored in reverse: <1s, 10s, 100s, ...> apple

string vectorToString(const vector<int> &first);
// convert vector to a string of its integer

vector<int> add(const vector<int> &first, const vector<int> &second);
/* 
 * add two vectors and return the result.
 * vectors and the result must contain only integers between 0 and 9
 * vectors are interpreted as numbers in reverse; e.g. <3, 4, 8, 2> <=> 2843,
 * so addition will be performed on the first elements, then the second elements,
 * etc. with ones carried to the next element
 */

bool verifyString(string);
// verify that a string contains an unsigned integer

int main(void) {
	string first, second;
	vector<int> first, second, result;

	// TODO get strings from user

	// TODO verify strings

	// TODO if strings are valid, add them

	// TODO print equation
	return 0;

}

// TODO define functions