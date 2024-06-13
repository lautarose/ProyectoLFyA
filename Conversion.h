#ifndef CONVERSION_H
#define CONVERSION_H

#include <string>
#include <stack>

int getPrecedence(char op);
std::string infixToPostfix(const std::string& infix);

#endif // CONVERSION_H
