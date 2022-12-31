#include "calculator.h"
#include <string>
#include <sstream>
#include <stack>
#include <cmath>

Calculator::Calculator() : expression(""){}

Calculator::Calculator(std::string expression) : expression(expression){}

void Calculator::setExpression(std::string expression){
    Calculator::expression = expression;
}

std::string Calculator::getExpression(){
    return Calculator::expression;
}

bool Calculator::decimalDigit(std::string token) {
  // Check if the token is a double value by trying to parse it using
  // the stringstream class
  std::stringstream ss(token);
  double value;
  if (ss >> value) {
    return true;
  }
  return false;
}

int Calculator::getPrecedence(std::string ch) {
  if (ch == "+" || ch == "-") {
    return 1;
  } else if (ch == "*" || ch == "/") {
    return 2;
  } else if (ch == "^") {
    return 3;
  } else {
    return -1;
  }
}

bool Calculator::hasLeftAssociativity(std::string ch) {
  if (ch == "+" || ch == "-" || ch == "/" || ch == "*") {
    return true;
  } else {
    return false;
  }
}

void Calculator::infixToPostfix() {
  std::string expression = Calculator::expression;
  // Initialising an empty String
  // (for output) and an empty stack
  std::stack<std::string> stack;

  // Initialize empty string
  std::string output = "";

  // Count the number of opening and closing parenthesis
    int open_count = 0, close_count = 0;
    for (unsigned int i = 0; i < expression.length(); ++i) {
      if (expression[i] == '(') {
        open_count++;
      } else if (expression[i] == ')') {
        close_count++;
      }
    }

    // If the number of opening and closing parenthesis is not equal,
    // return from the function with an error message or throw an exception
    if (open_count != close_count) {
      throw("Error: Mismatched parenthesis in expression");
      return;
    }

  // Iterating over tokens using inbuilt
  // length() function
  for (unsigned int i = 0; i < expression.length(); ++i) {
    // Finding character at 'i'th index
    std::string s(1, expression[i]);

    // If the scanned Token is an
    // operand, add it to output
    if (decimalDigit(s)) {
      std::string number = "";
      while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
        number += expression[i];
        i++;
      }
      output += number + " ";
      i--;
    }

    // handle negative sign '-'
    else if (s == "-" && (i == 0 || !decimalDigit(std::string(1, expression[i - 1])))) {
      output += "0 "; // Add a placeholder zero to the output
      stack.push("-"); // Push the negative sign to the stack as a unary operator
    }

    // If the scanned Token is an '('
    // push it to the stack
    else if (s == "(") {
      stack.push(s);
    }

    // If the scanned Token is an ')' pop and append
    // it to output from the stack until an '(' is
    // encountered
    else if (s == ")") {
      while (!stack.empty() && stack.top() != "(") {
        output += stack.top() + " ";
        stack.pop();
      }

      stack.pop();
    }

    // If an operator is encountered then taken the
    // further action based on the precedence of the
    // operator
    else {
      while (
        !stack.empty() &&
        getPrecedence(s) <=
        getPrecedence(stack.top()) &&
        hasLeftAssociativity(s)) {
        // fetch the top element(token)

        output += stack.top() + " ";
        stack.pop();
      }
      stack.push(s);
    }
  }

  // pop all the remaining operators from
  // the stack and append them to output
  while (!stack.empty()) {
    if (stack.top() == "(") {
      return;
    }
    output += stack.top() + " ";
    stack.pop();
  }
  Calculator::expression = output;
}

double Calculator::calculatePostfix() {
  std::string input = Calculator::expression;
  std::stack<double> operands;
  std::stringstream ss(input);
  std::string token;

  // Check if the input string is a valid postfix expression
  int numOperands = 0;
  int numOperators = 0;
  while (ss >> token) {
    if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {
      numOperators++;
    } else {
      numOperands++;
    }
  }
  if (numOperands != numOperators + 1) {
    // Throw an exception if the input expression is not valid
    throw std::invalid_argument("Invalid postfix expression: Mismatch between operands and operators");
  }

  // Reset the stringstream
  ss.clear();
  ss.str(input);

  while (ss >> token) {
    if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {
      // Pop the top two operands from the stack
      if (operands.empty()) {
        // Throw an exception if the stack is empty
        throw std::invalid_argument("Invalid postfix expression: Not enough operands");
      }
      double operand2 = operands.top();
      operands.pop();
      if (operands.empty()) {
        // Throw an exception if the stack is empty
        throw std::invalid_argument("Invalid postfix expression: Not enough operands");
      }
      double operand1 = operands.top();
      operands.pop();

      double result;
      if (token == "+") {
        result = operand1 + operand2;
      } else if (token == "-") {
        result = operand1 - operand2;
      } else if (token == "*") {
        result = operand1 * operand2;
      } else if (token == "/") {
        result = operand1 / operand2;
      } else if (token == "^") {
        result = std::pow(operand1, operand2);
      }

      // Push the result back onto the stack
      operands.push(result);
    } else {
      // If the token is not an operator, it must be an operand
      // Convert it to a double and push it onto the stack
      try {
        double operand = stod(token);
        operands.push(operand);
      } catch (const std::invalid_argument& e) {
        // Throw an exception if the string cannot be converted to a double
        throw std::invalid_argument("Invalid postfix expression: Invalid operand");
      }
    }
  }

  // At the end, the stack should contain only the result of the expression
  if (operands.size() == 1) {
      return operands.top();
      } else {
      // Throw an exception if the stack does not contain exactly one operand
      throw std::invalid_argument("Invalid postfix expression: Too many operands");
      }
      }

double Calculator::calculate(){
    double result = 0;
    Calculator::infixToPostfix();
    result = Calculator::calculatePostfix();
    return result;
}

