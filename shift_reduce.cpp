/*
# Lab 8: Implementation of Shift-Reduce Parser

## Aim
To implement a Shift-Reduce Parser in C++ that analyzes input strings based on a predefined grammar.

## Introduction
A Shift-Reduce Parser is a type of bottom-up parser used in Compiler Design. It uses a stack to hold grammar symbols and an input buffer to hold the string to be parsed. The parser operates by shifting input symbols onto the stack until a handle is found, which is then reduced to the corresponding non-terminal on the left-hand side of a production.

## Algorithm
1. Initialize a stack with the starting state (0).
2. Append `$` to the end of the input tokens.
3. For each step, read the top of the stack (state) and the current input token.
4. Look up the action in the parsing table:
   - If 'Shift', push the token and the new state onto the stack. Advance the input.
   - If 'Reduce', pop `2 * |RHS|` items from the stack. Look up the `GOTO` table for the new state based on the top state and the LHS non-terminal. Push the LHS and the new state.
   - If 'Accept', parsing is successful.
   - If no entry, report a syntax error.
5. Print the stack, input, and action at each step.

## Language Used
C++

## Tools Used
- VS Code
- GCC Compiler
- Git & GitHub

## Sample Input
```
Input string: id + id * id
```

## Sample Output
```
Stack               Input               Action
0                   id + id * id $      Shift
0 id 5              + id * id $         Reduce by E -> id
0 E 1               + id * id $         Shift
0 E 1 + 6           id * id $           Shift
...
0 E 1               $                   String Accepted!
```

## Result
Hence, the implementation of the Shift-Reduce Parser was completed successfully using C++.
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using namespace std;

struct Action {
    char type; // 'S' for Shift, 'R' for Reduce, 'A' for Accept
    int value; // state for shift, production number for reduce
};

map<pair<int, string>, Action> parsing_table = {
    {{0, "id"}, {'S', 5}}, {{0, "("}, {'S', 4}},
    {{1, "+"}, {'S', 6}}, {{1, "$"}, {'A', 0}},
    {{2, "+"}, {'R', 2}}, {{2, "*"}, {'S', 7}}, {{2, ")"}, {'R', 2}}, {{2, "$"}, {'R', 2}},
    {{3, "+"}, {'R', 4}}, {{3, "*"}, {'R', 4}}, {{3, ")"}, {'R', 4}}, {{3, "$"}, {'R', 4}},
    {{4, "id"}, {'S', 5}}, {{4, "("}, {'S', 4}},
    {{5, "+"}, {'R', 4}}, {{5, "*"}, {'R', 4}}, {{5, ")"}, {'R', 4}}, {{5, "$"}, {'R', 4}},
    {{6, "id"}, {'S', 5}}, {{6, "("}, {'S', 4}},
    {{7, "id"}, {'S', 5}}, {{7, "("}, {'S', 4}},
    {{8, "+"}, {'S', 6}}, {{8, ")"}, {'S', 11}},
    {{9, "+"}, {'R', 1}}, {{9, "*"}, {'S', 7}}, {{9, ")"}, {'R', 1}}, {{9, "$"}, {'R', 1}},
    {{10, "+"}, {'R', 3}}, {{10, "*"}, {'R', 3}}, {{10, ")"}, {'R', 3}}, {{10, "$"}, {'R', 3}}
};

map<pair<int, string>, int> goto_table = {
    {{0, "E"}, 1},
    {{4, "E"}, 8},
    {{6, "E"}, 9},
    {{7, "E"}, 10}
};

struct Production {
    string lhs;
    vector<string> rhs;
};

map<int, Production> productions = {
    {1, {"E", {"E", "+", "E"}}},
    {2, {"E", {"E", "*", "E"}}},
    {3, {"E", {"(", "E", ")"}}},
    {4, {"E", {"id"}}}
};

bool shift_reduce_parser(vector<string> tokens) {
    vector<string> stack;
    stack.push_back("0");
    tokens.push_back("$");
    int i = 0;

    cout << "Stack\t\t\tInput\t\t\tAction\n";
    cout << "--------------------------------------------------------\n";

    while (true) {
        int state = stoi(stack.back());
        string current_token = tokens[i];

        auto it = parsing_table.find({state, current_token});
        if (it == parsing_table.end()) {
            cout << "Error: Invalid syntax\n";
            return false;
        }

        Action action = it->second;

        // Print Stack
        string stack_str = "";
        for (const string& s : stack) stack_str += s + " ";
        // Print Input
        string input_str = "";
        for (size_t j = i; j < tokens.size(); j++) input_str += tokens[j] + " ";

        cout << stack_str << "\t\t" << input_str << "\t\t";

        if (action.type == 'S') {
            stack.push_back(current_token);
            stack.push_back(to_string(action.value));
            i++;
            cout << "Shift\n";
        } else if (action.type == 'R') {
            int prod_num = action.value;
            Production p = productions[prod_num];

            for (size_t j = 0; j < p.rhs.size() * 2; j++) {
                stack.pop_back();
            }

            state = stoi(stack.back());
            stack.push_back(p.lhs);
            stack.push_back(to_string(goto_table[{state, p.lhs}]));

            cout << "Reduce by " << p.lhs << " -> ";
            for (const string& s : p.rhs) cout << s << " ";
            cout << "\n";
        } else if (action.type == 'A') {
            cout << "String Accepted!\n";
            return true;
        }
    }
}

int main() {
    string input_string = "id + id * id";
    vector<string> tokens;
    stringstream ss(input_string);
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }

    shift_reduce_parser(tokens);

    return 0;
}
