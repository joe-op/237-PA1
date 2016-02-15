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
#include <string>
using namespace std;

int charToDigit(char);
// convert a char between '0' and '9' to digit
// return -1 if char is not valid

char digitToChar(int);//jens
// convert an int between 0 and 9 to char

vector<int> stringToVector(string);
// convert a string of digits into a vector of integers
// integers will be stored in reverse: <1s, 10s, 100s, ...>

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

void pause_237(bool);

int main(void) {
	string first_str, second_str;
	vector<int> first, second, result;

	cout << "Please enter two integers:" << endl;
	cin >> first_str;
	cin >> second_str;

	try {
		first = stringToVector(first_str);
		second = stringToVector(second_str);
	}
	catch (invalid_argument& ia) {
		cout << "Invalid entries!" << endl;
		pause_237(true);
		exit(1);
	}

	// TODO if strings are valid, add them

	// TODO print equation
	return 0;

}

// TODO define functions

int charToDigit(char c) {
	int code = c;
	if (code >= 48 && code <= 57) {
		return code - 48;
	} else {
		return -1;
	}
}

vector<int> stringToVector(string str) {
	vector<int> result;
	for (int i = str.length() - 1; i >= 0; i--) {
		int digit = charToDigit(str.at(i));
		if (digit == -1) {
			throw invalid_argument("NAN");
		}
		else {
			result.push_back(digit);
		}
	}
	return result;
}

void pause_237(bool have_newline)
{
	if (have_newline) {
		// Ignore the newline after the user's previous input.
		cin.ignore(200, '\n');
	}

	// Prompt for the user to press ENTER, then wait for a newline.
	cout << endl << "Press ENTER to continue." << endl;
	cin.ignore(200, '\n');
}