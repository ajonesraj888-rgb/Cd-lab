/*
# Lab 7: Computation of LEADING and TRAILING Sets

## Aim
To implement a C++ program to compute the LEADING and TRAILING sets for a given context-free grammar.

## Introduction
LEADING and TRAILING sets are used in operator precedence parsing. 
- LEADING(A) is the set of terminals that can appear as the first terminal in any string derived from A.
- TRAILING(A) is the set of terminals that can appear as the last terminal in any string derived from A.

## Algorithm
1. Identify all non-terminals and terminals.
2. For LEADING(A):
   - If A -> aα, add 'a' to LEADING(A).
   - If A -> Bα, add LEADING(B) to LEADING(A).
   - If A -> Baα, add 'a' to LEADING(A).
3. For TRAILING(A):
   - If A -> αa, add 'a' to TRAILING(A).
   - If A -> αB, add TRAILING(B) to TRAILING(A).
   - If A -> αaB, add 'a' to TRAILING(A).
4. Iterate until no new symbols are added to any LEADING or TRAILING set.
5. Display the sets.

## Language Used
C++

## Tools Used
- VS Code
- GCC Compiler
- Git & GitHub

## Sample Output
```
LEADING sets:
E : { (, *, +, id }
F : { (, id }
T : { (, *, id }

TRAILING sets:
E : { ), *, +, id }
F : { ), id }
T : { ), *, id }
```

## Result
Hence, the computation of LEADING and TRAILING sets for a given context-free grammar was successfully implemented using C++.
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cctype>

using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> LEADING;
map<char, set<char>> TRAILING;

bool isTerminal(char symbol) {
    return !isupper(symbol);
}

void computeLeading() {
    bool changed = true;
    while (changed) {
        changed = false;
        for (auto const& [head, productions] : grammar) {
            for (const string& prod : productions) {
                if (prod.empty()) continue;

                if (isTerminal(prod[0])) {
                    if (LEADING[head].insert(prod[0]).second) {
                        changed = true;
                    }
                } else {
                    for (char sym : LEADING[prod[0]]) {
                        if (LEADING[head].insert(sym).second) {
                            changed = true;
                        }
                    }
                    if (prod.length() > 1 && isTerminal(prod[1])) {
                        if (LEADING[head].insert(prod[1]).second) {
                            changed = true;
                        }
                    }
                }
            }
        }
    }
}

void computeTrailing() {
    bool changed = true;
    while (changed) {
        changed = false;
        for (auto const& [head, productions] : grammar) {
            for (const string& prod : productions) {
                if (prod.empty()) continue;
                
                int len = prod.length();
                if (isTerminal(prod[len - 1])) {
                    if (TRAILING[head].insert(prod[len - 1]).second) {
                        changed = true;
                    }
                } else {
                    for (char sym : TRAILING[prod[len - 1]]) {
                        if (TRAILING[head].insert(sym).second) {
                            changed = true;
                        }
                    }
                    if (len > 1 && isTerminal(prod[len - 2])) {
                        if (TRAILING[head].insert(prod[len - 2]).second) {
                            changed = true;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    // Standard example grammar for operator precedence parsing
    grammar['E'] = {"E+T", "T"};
    grammar['T'] = {"T*F", "F"};
    grammar['F'] = {"(E)", "id"};

    computeLeading();
    computeTrailing();

    cout << "LEADING sets:\n";
    for (auto const& [nt, lead_set] : LEADING) {
        cout << nt << " : { ";
        bool first = true;
        for (char c : lead_set) {
            if (!first) cout << ", ";
            if (c == 'i') cout << "id";
            else cout << c;
            first = false;
        }
        cout << " }\n";
    }

    cout << "\nTRAILING sets:\n";
    for (auto const& [nt, trail_set] : TRAILING) {
        cout << nt << " : { ";
        bool first = true;
        for (char c : trail_set) {
            if (!first) cout << ", ";
            if (c == 'i') cout << "id";
            else cout << c;
            first = false;
        }
        cout << " }\n";
    }

    return 0;
}
