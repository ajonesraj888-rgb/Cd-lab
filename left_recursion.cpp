 Lab 4: Elimination of Left Recursion

## Aim
To implement a C++ program to eliminate left recursion from a given context-free grammar.

## Introduction
Left recursion occurs in a grammar when a non-terminal appears as the leftmost symbol in its own production. Left-recursive grammars are not suitable for top-down parsing techniques such as recursive descent parsing. Therefore, left recursion must be removed to make the grammar suitable for parsing.

## Algorithm
1. Read the non-terminal symbol.
2. Read the number of productions.
3. Separate the productions into:
   - Left-recursive productions (A → Aα)
   - Non-left-recursive productions (A → β)
4. Rewrite the grammar using a new non-terminal to remove left recursion.
5. Display the modified grammar.

## Language Used
C++

## Tools Used
- VS Code
- GCC Compiler
- Git & GitHub

## Sample Input
```
Enter non-terminal: A
Enter number of productions: 3
Enter productions (without non-terminal on left):
A
BC
```

## Sample Output
```
After eliminating left recursion:
A -> BC A'
A' -> ε
```

## Result
Hence, the elimination of left recursion from a given context-free grammar was successfully implemented using C++.
