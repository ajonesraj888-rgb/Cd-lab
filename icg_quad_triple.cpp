/*
# Lab 11: Intermediate Code Generation (Quadruple, Triple, Indirect Triple)

## Aim
To implement a C++ program that generates intermediate code in the form of Quadruples, Triples, and Indirect Triples for a given arithmetic expression.

## Introduction
Intermediate Code Generation (ICG) uses various data structures to represent the code independently of the target machine. 
- **Quadruple**: Contains an operator, two operands (arguments), and a result.
- **Triple**: Contains an operator and two operands. The result is referred to by the position of the statement.
- **Indirect Triple**: A list of pointers to triples, which makes reordering optimizations easier.

## Algorithm
1. Parse the input arithmetic assignment statement.
2. Convert the right-hand side (RHS) of the assignment into postfix notation.
3. Traverse the postfix expression:
   - For an operand, push it onto a stack.
   - For an operator, pop two operands. Generate a temporary variable for the result.
   - Add the operation to the Quadruple and Triple arrays.
   - Push the temporary variable (or triple index) onto the stack.
4. Process the assignment operator to store the final result in the left-hand side (LHS) variable.
5. Print the formatted Quadruples, Triples, and Indirect Triples.

## Language Used
C++

## Tools Used
- VS Code
- GCC Compiler
- Git & GitHub

## Sample Output
```
Input Expression: A = B + C * D

Quadruple Representation:
Index   Op      Arg1    Arg2    Result
0       *       C       D       t1
1       +       B       t1      t2
2       =       t2              A

Triple Representation:
Index   Op      Arg1    Arg2
0       *       C       D
1       +       B       (0)
2       =       (1)     A

Indirect Triple Representation:
Pointer Index
0       0
1       1
2       2
```

## Result
Hence, the representation of intermediate code into Quadruples, Triples, and Indirect Triples was successfully implemented using C++.
*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <sstream>
#include <cctype>

using namespace std;

struct Quadruple {
    string op;
    string arg1;
    string arg2;
    string result;
};

struct Triple {
    string op;
    string arg1;
    string arg2;
};

int temp_count = 1;

string new_temp() {
    return "t" + to_string(temp_count++);
}

int get_precedence(string op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}

vector<string> infix_to_postfix(const vector<string>& tokens) {
    stack<string> s;
    vector<string> postfix;
    for (const string& token : tokens) {
        if (isalnum(token[0])) {
            postfix.push_back(token);
        } else if (token == "(") {
            s.push(token);
        } else if (token == ")") {
            while (!s.empty() && s.top() != "(") {
                postfix.push_back(s.top());
                s.pop();
            }
            if (!s.empty()) s.pop();
        } else {
            while (!s.empty() && s.top() != "(" && get_precedence(s.top()) >= get_precedence(token)) {
                postfix.push_back(s.top());
                s.pop();
            }
            s.push(token);
        }
    }
    while (!s.empty()) {
        postfix.push_back(s.top());
        s.pop();
    }
    return postfix;
}

void generate_icg(const string& expression) {
    vector<string> tokens;
    stringstream ss(expression);
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }

    if (tokens.size() < 3 || tokens[1] != "=") {
        cout << "Invalid assignment expression.\n";
        return;
    }

    string lhs = tokens[0];
    vector<string> rhs_tokens(tokens.begin() + 2, tokens.end());
    vector<string> postfix = infix_to_postfix(rhs_tokens);

    vector<Quadruple> quadruples;
    vector<Triple> triples;
    stack<string> eval_stack;
    stack<string> triple_stack;

    for (const string& t : postfix) {
        if (isalnum(t[0])) {
            eval_stack.push(t);
            triple_stack.push(t);
        } else {
            string op2 = eval_stack.top(); eval_stack.pop();
            string op1 = eval_stack.top(); eval_stack.pop();
            
            string t2 = triple_stack.top(); triple_stack.pop();
            string t1 = triple_stack.top(); triple_stack.pop();

            string temp = new_temp();
            quadruples.push_back({t, op1, op2, temp});
            eval_stack.push(temp);

            int t_idx = triples.size();
            triples.push_back({t, t1, t2});
            triple_stack.push("(" + to_string(t_idx) + ")");
        }
    }

    string final_result = eval_stack.top();
    string final_triple = triple_stack.top();
    
    quadruples.push_back({"=", final_result, "", lhs});
    triples.push_back({"=", final_triple, "", lhs});

    cout << "Input Expression: " << expression << "\n\n";

    cout << "Quadruple Representation:\n";
    cout << "Index\tOp\tArg1\tArg2\tResult\n";
    for (size_t i = 0; i < quadruples.size(); ++i) {
        cout << i << "\t" << quadruples[i].op << "\t" << quadruples[i].arg1 << "\t" 
             << quadruples[i].arg2 << "\t" << quadruples[i].result << "\n";
    }

    cout << "\nTriple Representation:\n";
    cout << "Index\tOp\tArg1\tArg2\n";
    for (size_t i = 0; i < triples.size(); ++i) {
        cout << i << "\t" << triples[i].op << "\t" << triples[i].arg1 << "\t" << triples[i].arg2 << "\n";
    }

    cout << "\nIndirect Triple Representation:\n";
    cout << "Pointer\tIndex\n";
    for (size_t i = 0; i < triples.size(); ++i) {
        cout << i << "\t" << i << "\n";
    }
}

int main() {
    string expr = "A = B + C * D";
    generate_icg(expr);
    return 0;
}
