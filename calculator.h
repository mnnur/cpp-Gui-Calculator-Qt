#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>

class Calculator
{
private:
    // Mathematical expression to calculate
    std::string expression = "";

    // Check if exspression is double value
    bool decimalDigit(std::string token);

    // Operator having higher precedence value will be returned
    int getPrecedence(std::string ch);

    // Determine if Operator has Left or Right associativity
    bool hasLeftAssociativity(std::string ch);

    // Method converts  given infix to postfix expression
    void infixToPostfix();

    // Calculate Postix Mathematical expression
    double calculatePostfix();

public:
    Calculator();
    Calculator(std::string expression);
    void setExpression(std::string expression);
    std::string getExpression();
    double calculate();

};

#endif // CALCULATOR_H
