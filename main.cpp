#include <iostream>
#include<string>
#include<sstream>
#include<cmath>

// Author: Desean Newcomb
// assignment: Calculator



/*
 * Function: print_error
 * Description: Prints an error message explaining that the user supplied
 * 		an invalid arithmetic expression.
 */
void print_error() {
	// DO NOT MODIFY THIS FUNCTION, OR ELSE YOU RISK BREAKING THE GRADING
	// SCRIPT.
	std::cout << "That isn't a valid arithmetic expression." << std::endl;
}

/*
 * Function: prompt_for_arithmetic_expression
 * Description: Prompts the user for an arithmetic expression and returns
 * 		whatever text they supply, whether that text represents a valid
 * 		arithmetic expression or not (validity should be checked elsewhere;
 * 		checking validity is not this particular function's responsibility).
 * Returns: An entire line of text supplied by the user via the terminal when
 * 		prompted for an arithmetic expression
 */
std::string prompt_for_arithmetic_expression() {
	// DO NOT MODIFY THE BELOW PRINT STATEMENT, OR ELSE YOU RISK BREAKING THE
	// GRADING SCRIPT
	std::cout << "Enter a valid arithmetic expression: ";
	std::string expression;
	while (true) {
		std::getline(std::cin, expression);
		if (!expression.empty()) {
			return expression;
		} else {
			std::cout << "That isn't a valid arithmetic expression.";
		}
	}
}


	// TODO Complete this function so that it reads the user's line of text
	// and returns it

/*
 * Function: prompt_for_retry
 * Description: Asks the user whether they'd like to enter another arithmetic
 * 		expression and returns their entire line-of-text response
 * Returns: An entire line of text supplied by the user via the terminal when
 * 		asked if they'd like to enter another arithmetic expression. If this
 * 		function returns the string "Y", then that means the user would like
 * 		to enter another arithmetic expression.
 */
std::string prompt_for_retry() {
	// DO NOT MODIFY THE BELOW PRINT STATEMENT, OR ELSE YOU RISK BREAKING THE
	// GRADING SCRIPT
	std::cout << "Would you like to enter another expression? Enter Y for "
		"yes: ";
	std::string response;
	std::getline(std::cin, response);
	return response;

	// TODO Complete this function so that it reads the user's line of text
	// and returns it
}

/*
 * Function: print_history_header
 * Description: Prints the header that precedes the history of values to be
 * 		printed at the end of the program.
 */
void print_history_header() {
	// DO NOT MODIFY THIS FUNCTION, OR ELSE YOU RISK BREAKING THE GRADING
	// SCRIPT. YOU SHOULD CALL THIS FUNCTION FROM WITHIN A LARGER FUNCTION
	// WHOSE RESPONSIBILITY IS TO PRINT THE ENTIRE HISTORY.
	std::cout << "History of computed values:" << std::endl;
}

/*
 * Function: is_number
 * Description: Determines whether a given string holds a valid numeric value
 * Returns: True if the given string holds a valid numeric value, or false
 * 		otherwise. If this function returns true, it's safe to use std::stod()
 * 		on the string to convert it to a number (double) afterwards. Otherwise,
 * 		the given string does not contain a valid numeric value, and attempting
 * 		to use std::stod() on the string may crash your program.
 */
bool is_number(std::string str) {
	// A valid number must contain at least one digit and at most one
	// decimal point
	int num_digits = 0;
	int num_points = 0;
	for (int i = 0; i < str.length(); i++) {
		bool is_point = str.at(i) == '.';
		// A negative sign is a dash at the beginning of the string
		bool is_negative_sign = str.at(i) == '-' && i == 0;
		bool is_number = str.at(i) >= '0' && str.at(i) <= '9';

		if (is_point) {
			// If the character is a decimal point, increment
			// the number of points found, and return false if
			// it's greater than 1
			num_points++;
			if (num_points > 1) {
				return false;
			}
		}
		if (is_number) {
			// If the character is a digit, increment the number of
			// digits found
			num_digits++;
		}

		// If the character isn't any of the three valid possibilities,
		// return false, immediately ending the function
		if (!is_point && !is_negative_sign && !is_number) {
			return false;
		}
	}

	// Return true only if at least one digit was found
	return num_digits > 0;
}

bool is_operator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

double evaluate_expression(const std::string& expression) {
	std::istringstream iss(expression);
	double result = 0.0;
	char op = '+';
	double operand = 0.0;

	while (iss >> operand) {
		if (op == '+')
			result += operand;
		else if (op == '-')
			result -= operand;
		else if (op == '*')
			result *= operand;
		else if (op == '/')
			result /= operand;
		else if (op == '^')
			result = std::pow(result, operand);

		if (!(iss >> op)) 
			break;
	}

	return result;
}

double process_expression(const std::string& expression) {
	std::ostringstream oss;
	char prevChar = ' ';

	for (char currentChar : expression) {
		if (currentChar == ' ') {
			continue;
		} else if (!isdigit(currentChar) && currentChar != '.') {
			if (prevChar != ' ' && prevChar != ')') {
				oss << ' ';
			}
			oss << currentChar;
			oss << ' ';
		} else {
			oss << currentChar;
		}
		prevChar = currentChar;
	}

	std::string processed_expression = oss.str();
	if (processed_expression.empty()) {
		print_error();
		return 0.0;
	}

	for (size_t i = 1; i < processed_expression.size(); ++i) {
		if (is_operator(processed_expression[i]) && is_operator(processed_expression[i - 1])) {
			print_error();
			return 0.0;
		}
	}

	double result = evaluate_expression(processed_expression);
	return result;
}


int main() {
	const int MAX_EXPRESSIONS = 100;
	double expressionResults[MAX_EXPRESSIONS];
	int numExpressions = 0;
	std::string userInput;
	char repeat;

	do {
		std::string expression = prompt_for_arithmetic_expression();
		double result = process_expression(expression);
		if (result != 0.0) {
			expressionResults[numExpressions++] = result;
		std::cout << result << std::endl;
		}

		std::string retry = prompt_for_retry();
		repeat = (retry.size() > 0 && std::toupper(retry[0]) == 'Y') ? 'Y' : 'N';
	} while (repeat == 'Y');

	print_history_header();
	for (int i = 0; i < numExpressions; ++i) {
		std::cout << expressionResults[i] << std::endl;
	}

	return 0;
}
