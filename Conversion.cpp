#include "Conversion.h"

int getPrecedence(char op) {
    switch(op) {
        case '*': return 3;
        case '.': return 2;
        case '+': return 1;
        default: return 0;
    }
}

std::string infixToPostfix(const std::string& infix) {
    std::stack<char> stack;
    std::string postfix = "";

    for (char ch : infix) {
        if (ch == '(') {
            stack.push(ch);
        } else if (ch == ')') {
            while (!stack.empty() && stack.top() != '(') {
                postfix += stack.top();
                stack.pop();
            }
            stack.pop();
        } else if (ch == '*' || ch == '.' || ch == '+') {
            while (!stack.empty() && getPrecedence(stack.top()) >= getPrecedence(ch)) {
                postfix += stack.top();
                stack.pop();
            }
            stack.push(ch);
        } else {
            postfix += ch;
        }
    }

    while (!stack.empty()) {
        postfix += stack.top();
        stack.pop();
    }

    return postfix;
}
