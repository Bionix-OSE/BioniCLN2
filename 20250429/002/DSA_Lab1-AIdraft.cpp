/* Prompt: 
Given a mathematical infix expression containing large integers (up to 100 digits) and multiple arithmetic operators (+, -, *, /), the task is to evaluate the expression and return the result. The expression may also include parentheses to group operations. 
This C++ program should handle expressions with multiple operands, correctly respecting the PMDAS order, and does not make use of any built-in data structure or library capable of handling large integers or expressions (in other words we have to write our own implementation of that). */

#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <algorithm>
#include <fstream>
#include <stdexcept>

// Function to remove spaces from the expression
std::string removeSpaces(const std::string &expr) {
	std::string result;
	for (char ch : expr) {
		if (!isspace(ch)) {
			result += ch;
		}
	}
	return result;
}

// Function to compare two large integers represented as strings
int compareLargeIntegers(const std::string &a, const std::string &b) {
	if (a.length() != b.length()) {
		return a.length() < b.length() ? -1 : 1;
	}
	return a.compare(b);
}

// Function to add two large integers represented as strings
std::string addLargeIntegers(const std::string &a, const std::string &b) {
	std::string result;
	int carry = 0, sum = 0;
	int i = a.length() - 1, j = b.length() - 1;

	while (i >= 0 || j >= 0 || carry) {
		int digitA = (i >= 0) ? a[i--] - '0' : 0;
		int digitB = (j >= 0) ? b[j--] - '0' : 0;
		sum = digitA + digitB + carry;
		carry = sum / 10;
		result += (sum % 10) + '0';
	}

	std::reverse(result.begin(), result.end());
	return result;
}

// Function to subtract two large integers represented as strings
std::string subtractLargeIntegers(const std::string &a, const std::string &b) {
	std::string result;
	int borrow = 0, diff = 0;
	int i = a.length() - 1, j = b.length() - 1;

	while (i >= 0 || j >= 0) {
		int digitA = (i >= 0) ? a[i--] - '0' : 0;
		int digitB = (j >= 0) ? b[j--] - '0' : 0;
		diff = digitA - digitB - borrow;
		if (diff < 0) {
			diff += 10;
			borrow = 1;
		} else {
			borrow = 0;
		}
		result += diff + '0';
	}

	while (result.length() > 1 && result.back() == '0') {
		result.pop_back();
	}

	std::reverse(result.begin(), result.end());
	return result;
}

// Function to multiply two large integers represented as strings
std::string multiplyLargeIntegers(const std::string &a, const std::string &b) {
	int n = a.length(), m = b.length();
	std::string result(n + m, '0');

	for (int i = n - 1; i >= 0; --i) {
		int carry = 0;
		for (int j = m - 1; j >= 0; --j) {
			int product = (a[i] - '0') * (b[j] - '0') + (result[i + j + 1] - '0') + carry;
			carry = product / 10;
			result[i + j + 1] = (product % 10) + '0';
		}
		result[i] += carry;
	}

	size_t startPos = result.find_first_not_of('0');
	if (startPos != std::string::npos) {
		return result.substr(startPos);
	}
	return "0";
}

// Function to divide two large integers represented as strings
std::string divideLargeIntegers(const std::string &a, const std::string &b) {
	if (b == "0") {
		throw std::invalid_argument("Division by zero");
	}

	std::string result, remainder = "0";
	for (char digit : a) {
		remainder += digit;
		size_t startPos = remainder.find_first_not_of('0');
		if (startPos != std::string::npos) {
			remainder = remainder.substr(startPos);
		} else {
			remainder = "0";
		}

		int quotient = 0;
		while (compareLargeIntegers(remainder, b) >= 0) {
			remainder = subtractLargeIntegers(remainder, b);
			++quotient;
		}
		result += quotient + '0';
	}

	size_t startPos = result.find_first_not_of('0');
	if (startPos != std::string::npos) {
		return result.substr(startPos);
	}
	return "0";
}

// Function to evaluate a simple expression with two operands and an operator
std::string evaluateSimpleExpression(const std::string &a, const std::string &b, char op) {
	switch (op) {
		case '+': return addLargeIntegers(a, b);
		case '-': return subtractLargeIntegers(a, b);
		case '*': return multiplyLargeIntegers(a, b);
		case '/': return divideLargeIntegers(a, b);
		default: throw std::invalid_argument("Invalid operator");
	}
}

// Function to evaluate an infix expression
std::string evaluateExpression(const std::string &expr) {
	std::stack<std::string> values;
	std::stack<char> operators;

	auto applyOperator = [&]() {
		std::string b = values.top(); values.pop();
		std::string a = values.top(); values.pop();
		char op = operators.top(); operators.pop();
		values.push(evaluateSimpleExpression(a, b, op));
	};

	std::string num;
	for (size_t i = 0; i < expr.length(); ++i) {
		char ch = expr[i];

		if (isdigit(ch)) {
			num += ch;
		} else {
			if (!num.empty()) {
				values.push(num);
				num.clear();
			}

			if (ch == '(') {
				operators.push(ch);
			} else if (ch == ')') {
				while (!operators.empty() && operators.top() != '(') {
					applyOperator();
				}
				operators.pop(); // Remove '('
			} else {
				while (!operators.empty() && operators.top() != '(' &&
					   ((ch == '+' || ch == '-') || (ch == '*' || ch == '/'))) {
					applyOperator();
				}
				operators.push(ch);
			}
		}
	}

	if (!num.empty()) {
		values.push(num);
	}

	while (!operators.empty()) {
		applyOperator();
	}

	return values.top();
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
		return 1;
	}

	std::string inputFile = argv[1];
	std::string outputFile = argv[2];

	std::ifstream inFile(inputFile);
	if (!inFile) {
		std::cerr << "Error: Could not open input file " << inputFile << std::endl;
		return 1;
	}

	std::ofstream outFile(outputFile);
	if (!outFile) {
		std::cerr << "Error: Could not open output file " << outputFile << std::endl;
		return 1;
	}

	std::string expression;
	while (std::getline(inFile, expression)) {
		try {
			expression = removeSpaces(expression);
			std::string result = evaluateExpression(expression);
			outFile << result << std::endl;
		} catch (const std::exception &e) {
			outFile << "Error: " << e.what() << std::endl;
		}
	}

	inFile.close();
	outFile.close();

	return 0;
}