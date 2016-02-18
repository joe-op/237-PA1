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
#include <vector>
#include <string>
using namespace std;

// convert a char between '0' and '9' to digit
// return -1 if char is not valid
int charToDigit(char);

// convert an int between 0 and 9 to char
char digitToChar(int);

// convert a string of digits into a vector of integers
// integers will be stored in reverse: <1s, 10s, 100s, ...>
vector<int> stringToVector(string);

// convert vector to a string of its integer
string vectorToString(const vector<int> &first);

/*
* add two vectors and return the result.
* vectors and the result must contain only integers between 0 and 9
* vectors are interpreted as numbers in reverse; e.g. <3, 4, 8, 2> <=> 2843,
* so addition will be performed on the first elements, then the second elements,
* etc. with ones carried to the next element
*/
vector<int> add(const vector<int> &first, const vector<int> &second);

/*
 * Find the difference between two integers.
 * Returns a positive result.
 */
vector<int> diff(const vector<int> &first, const vector<int> &second);

/*
 * Compare the numbers in two vectors.
 * Return 1 if the first is larger, -1 if the first is smaller,
 * 0 if they are the same.
 */
int compare(const vector<int> &first, const vector<int> &second);

// Remove leading zeroes from a vector
// (Since integer is reversed, leading zeroes are at the end)
void remove_zeroes(vector<int> &num);

// verify that a string contains an unsigned integer
bool verify_string(string);

// get a number of integer strings
vector<string> get_strings(int);

void pause_237(bool);

int main(void) {
	vector<string> strings;
	string first_display, second_display, result_display, diff_display, diff_sign;
	vector<int> first, second, result, diff_result;
	bool first_larger;

	// read and verify strings
	strings = get_strings(2);

    

	try {
		first = stringToVector(strings[0]);
		second = stringToVector(strings[1]);
	}
	catch (invalid_argument& ia) {
		cout << "Invalid entries!" << endl << ia.what() << endl;
		pause_237(true);
		exit(1);
	}

	result = add(first, second);
	first_display = vectorToString(first);
	second_display = vectorToString(second);
	result_display = vectorToString(result);

	cout << first_display << " + " << second_display << " = " << result_display << endl;

	// subtract second number from first number
	first_larger = (compare(first, second) >= 0);
	diff_result = diff(first, second);
	diff_display = vectorToString(diff_result);
	if (first_larger)
		diff_sign = "";
	else
		diff_sign = "-";

	cout << first_display << " - " << second_display << " = " << diff_sign << diff_display << endl;

	pause_237(true);

	
	return 0;

}



int charToDigit(char c) {
	int code = c;
	if (code >= 48 && code <= 57) {
		return code - 48;
	} else {
		return -1;
	}
}

char digitToChar(int digit) {
	if (digit >= 0 && digit <= 9) {
		char c = digit + 48;
		return c;
	}
	else {
		throw invalid_argument("Cannot make char from non-digit integer");
	}
}

bool verify_string(string str) {
	bool valid = true;
	unsigned int i = 0;
	while (valid && i < str.length()) {
		int code = str.at(i);
		valid = (code >= 48 && code <= 57);
		i++;
	}
	return valid;
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

string vectorToString(const vector<int> &first) {
	string result = "";
	for (int i = first.size() - 1; i >= 0; i--) {
		try {
			result += digitToChar(first[i]);
		}
		catch (invalid_argument &ia) {
			cout << "Invalid argument: " << ia.what() << endl;
			pause_237(true);
			exit(1);
		}
	}
	return result;
}

vector<string> get_strings(int num) {
	string input;
	vector<string> strings;

	cout << "Please enter " << num << " positive integer(s):\n";
	int i = 0;
	while (i < num) {
		cout << "Integer " << i + 1 << ": ";
		cin >> input;
		if (verify_string(input)) {
			i++;
			strings.push_back(input);
		}
		else {
			cout << "Not a valid integer!" << endl;
			pause_237(true);
		}
	}
    return strings;	
}

void remove_zeroes(vector<int> &num) {
	int i = num.size() - 1;
	while (i >= 0 && num[i] == 0) {
		num.pop_back();
	    i--;
	}
}

int compare(const vector<int> &first, const vector<int> &second) {
	if (first.size() > second.size()) {
		return 1;
	}
	else if (second.size() > first.size()) {
		return -1;
	}
	else {
		for (int i = first.size() - 1; i >= 0; i--) {
			if (first[i] > second[i]) {
				return 1;
			}
			else if (second[i] > first[i]) {
				return -1;
			}
		}
		return 0;
	}

}

vector<int> diff(const vector<int> &first, const vector<int> &second) {
	vector<int> result;
	int carry, max, min, diff_sum;
	const vector<int> *largePtr, *smallPtr;
	if (compare(first, second) > 0) {
		largePtr = &first;
		smallPtr = &second;
	}
	else {
		largePtr = &second;
		smallPtr = &first;
	}
	
	carry = 0;
	max = (*largePtr).size();
	min = (*smallPtr).size();
	for (int i = 0; i < max; i++) {
		if (i < min) {
			diff_sum = (*largePtr)[i] + carry - (*smallPtr)[i];
		}
		else {
			diff_sum = (*largePtr)[i] + carry;
		}
		carry = 0;
		if (diff_sum < 0) {
			diff_sum = diff_sum + 10;
			carry = -1;
		}
		result.push_back(diff_sum);
	}
	remove_zeroes(result);
	return result;
}


vector<int> add(const vector<int> &first, const vector<int> &second) {
	vector<int> result;
	int	carry, max, min, sum;
	const vector<int> *largePtr, *smallPtr;
	if (first.size() > second.size()) {
		largePtr = &first;
		smallPtr = &second;
	}
	else {
		largePtr = &second;
		smallPtr = &first;
	}
	carry = 0;
	max = (*largePtr).size();
	min = (*smallPtr).size();
	for (int i = 0; i < max; i++) {
		if (i < min) {
			sum = first[i] + second[i] + carry;
		}
		else {
			sum = (*largePtr)[i] + carry;
		}
		carry = 0;
		if (sum > 9) {
			sum = sum - 10;
			carry = 1;
		}
		result.push_back(sum);
	}
	if (carry == 1)
		result.push_back(1);

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