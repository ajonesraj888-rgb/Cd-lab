/*
# Lab 10: Intermediate Code Generation (Postfix and Prefix)

## Aim
To implement a C++ program that converts infix arithmetic expressions into Postfix (Reverse Polish Notation) and Prefix (Polish Notation) forms.

## Introduction
Intermediate Code Generation is an important phase in the compilation process. Postfix and Prefix notations are parenthesis-free representations of arithmetic expressions, which makes them easier for machines to evaluate compared to traditional infix notation.

## Algorithm
1. Infix to Postfix:
   - Read the infix expression token by token.
   - If the token is an operand, add it to the output.
   - If the token is '(', push it to the stack.
   - If the token is ')', pop from stack to output until '(' is encountered.
   - If the token is an operator, pop operators from the stack to the output until the stack is empty or the top operator has less precedence. Then push the token.
   - Finally, pop any remaining operators from the stack to the output.
2. Infix to Prefix:
   - Reverse the infix expression (swap '(' with ')' and vice versa).
   - Convert the reversed expression to postfix.
   - Reverse the resulting postfix expression to get the prefix expression.

## Language Used
C++

## Tools Used
- VS Code
- GCC Compiler
- Git & GitHub

## Sample Input
```
Infix Expression: ( A + B ) * C - D
```

## Sample Output
```
Postfix Expression: A B + C * D -
Prefix Expression: - * + A B C D
```

## Result
Hence, the C++ program for intermediate code generation (Postfix and Prefix representations) was implemented and verified successfully.
*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

int get_precedence(string op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0;
}

bool is_operator(string token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
}

string infix_to_postfix(const string& expression) {
    stack<string> s;
    vector<string> output;
    stringstream ss(expression);
    string token;

    while (ss >> token) {
        if (isalnum(token[0])) {
            output.push_back(token);
        } else if (token == "(") {
            s.push(token);
        } else if (token == ")") {
            while (!s.empty() && s.top() != "(") {
                output.push_back(s.top());
                s.pop();
            }
            if (!s.empty() && s.top() == "(") {
                s.pop();
            }
        } else if (is_operator(token)) {
            while (!s.empty() && s.top() != "(" && get_precedence(s.top()) >= get_precedence(token)) {
                output.push_back(s.top());
                s.pop();
            }
            s.push(token);
        }
    }

    while (!s.empty()) {
        output.push_back(s.top());
        s.pop();
    }

    string result = "";
    for (size_t i = 0; i < output.size(); ++i) {
        result += output[i] + (i < output.size() - 1 ? " " : "");
    }
    return result;
}

string infix_to_prefix(const string& expression) {
    vector<string> tokens;
    stringstream ss(expression);
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }

    reverse(tokens.begin(), tokens.end());

    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i] == "(") tokens[i] = ")";
        else if (tokens[i] == ")") tokens[i] = "(";
    }

    string reversed_expr = "";
    for (size_t i = 0; i < tokens.size(); ++i) {
        reversed_expr += tokens[i] + (i < tokens.size() - 1 ? " " : "");
    }

    string postfix = infix_to_postfix(reversed_expr);

    vector<string> postfix_tokens;
    stringstream pss(postfix);
    while (pss >> token) {
        postfix_tokens.push_back(token);
    }

    reverse(postfix_tokens.begin(), postfix_tokens.end());

    string result = "";
    for (size_t i = 0; i < postfix_tokens.size(); ++i) {
        result += postfix_tokens[i] + (i < postfix_tokens.size() - 1 ? " " : "");
    }
    return result;
}
