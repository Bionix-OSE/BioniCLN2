/* VGU CSE23 - DSA 2025 - Lab 1 (Failed) */

#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <algorithm>
#include <fstream>
#include <stdexcept>

// *********** PART 1 START ***********
class li { // Li = Large Integer
	private:
		// Function to compare two large integers represented as strings
		int compare(const std::string &a, const std::string &b) {
			if (a.length() != b.length()) {
				return a.length() < b.length() ? -1 : 1;
			}
			return a.compare(b);
		}

		// All the arithmetic stuffs
		// +
		std::string add(const std::string &a, const std::string &b) {
			std::string result;
			int carry = 0, sum = 0;
			int i = a.length() - 1, j = b.length() - 1;
		
			while (i >= 0 || j >= 0 || carry) {
				int A = (i >= 0) ? a[i--] - '0' : 0;
				int B = (j >= 0) ? b[j--] - '0' : 0;
				sum = A + B + carry;
				carry = sum / 10;
				result += (sum % 10) + '0';
			}
			std::reverse(result.begin(), result.end());
			return result;
		}
		// -
		std::string sub(const std::string &a, const std::string &b) {
			if (compare(a, b) < 0) {
				return "-" + sub(b, a);
			}
			std::string result;
			int borrow = 0, diff = 0;
			int i = a.length() - 1, j = b.length() - 1;
		
			while (i >= 0 || j >= 0) {
				int A = (i >= 0) ? a[i--] - '0' : 0;
				int B = (j >= 0) ? b[j--] - '0' : 0;
				diff = A - B - borrow;
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
		// *
		std::string mult(const std::string &a, const std::string &b) {
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
		// div
		std::string div(const std::string &a, const std::string &b) {
			if (b == "0") {
				throw std::invalid_argument("You can't divide by zero. Messed up somewhere?");
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
				while (compare(remainder, b) >= 0) {
					remainder = sub(remainder, b);
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
// *********** PART 1 END ***********

// *********** PART 2 START ***********
		// Basic evaluation of a simple expression with two operands and an operator
		std::string s_eval(const std::string &a, const std::string &b, char op) {
			switch (op) {
				case '+': return add(a, b);
				case '-': return sub(a, b);
				case '*': return mult(a, b);
				case '/': return div(a, b);
				default: throw std::invalid_argument(""); // Should also be catched by the try-catch block wrapped around process()
			}
		}

	public:
		// The real deal
		std::string trim(const std::string &expr) {
			std::string result;
			for (char ch : expr) {
				if (!isspace(ch)) {result += ch;}
			}
			return result;
		}
		std::string evaluate(const std::string &expr) {
			std::stack<std::string> values;
			std::stack<char> operators;
		
			auto process = [&]() {
				if (values.size() < 2 || operators.empty()) {throw std::invalid_argument("");}
				std::string b = values.top(); values.pop();
				std::string a = values.top(); values.pop();
				char op = operators.top(); operators.pop();
				values.push(s_eval(a, b, op));
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
							try {process();} catch (const std::exception &e) {
								return "Malformed or empty expression.";
							}
						}
						operators.pop();
					} else {
						while (!operators.empty() && operators.top() != '(' && ((ch == '+' || ch == '-') || (ch == '*' || ch == '/'))) {
							try {process();} catch (const std::exception &e) {
								return "Malformed or empty expression.";
							}
						}
						operators.push(ch);
					}
				}
			}
		
			if (!num.empty()) {
				values.push(num);
			}
			while (!operators.empty()) {
				try {process();} catch (const std::exception &e) {
					return "Malformed or empty expression.";
				}
			}
			
			if (values.size() == 1) {
				return values.top();
			} else {
				return "Malformed or empty expression.";
			}
		}
};
// *********** PART 2 END ***********

// *********** PART 3 START ***********
int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
		return 1;
	}
	std::string inputFile = argv[1];
	std::string outputFile = argv[2];

	// IO handling
	std::ifstream inFile(inputFile);
	if (!inFile) {
		std::cerr << "ERROR: Could not open " << inputFile << std::endl;
		return 1;
	}
	std::ofstream outFile(outputFile);
	if (!outFile) {
		std::cerr << "ERROR: Could not write to " << outputFile << std::endl;
		return 1;
	}

	// Main processor
	std::string expression;
	li li;
	while (std::getline(inFile, expression)) {
		try {
			expression = li.trim(expression);
			std::string result = li.evaluate(expression);
			std::cout << result << std::endl; outFile << result << std::endl;
		} catch (const std::exception &e) {
			std::cerr << "ERROR (we couldn't handle this one): " << e.what() << std::endl;
			outFile << "ERROR (we couldn't handle this one): " << e.what() << std::endl;
		}
	}

	outFile << std::endl;
	inFile.close();
	outFile.close();
	return 0;
}
// *********** PART 3 END ***********
