# Lab 1: Implementation of Lexical Analyzer

## Aim
To implement a lexical analyzer using C++ that identifies and classifies tokens such as keywords, identifiers, operators, numbers, and special symbols from a given input program.

## Introduction
A lexical analyzer is the first phase of a compiler. It reads the source code character by character and converts it into meaningful tokens. These tokens are then passed to the syntax analyzer for further processing. This experiment demonstrates the basic working of a lexical analyzer using simple rules.

## Algorithm
1. Read the input source code as a single line.
2. Initialize an empty string to store tokens.
3. Traverse the input character by character.
4. If the character is alphanumeric, add it to the current token.
5. When a delimiter is encountered:
   - Check if the token is a keyword.
   - If the token starts with a digit, classify it as a number.
   - Otherwise, classify it as an identifier.
6. Check for operators and special symbols separately.
7. Display the classified tokens.
8. Stop the execution.

## Language Used
C++

## Tools Used
- VS Code
- GCC Compiler
- Git & GitHub

## Sample Input
```
int a = 10;
```

## Sample Output
```
int : Keyword
a : Identifier
= : Operator
10 : Number
; : Special Symbol
```

## Result
Hence, the program to implement a lexical analyzer using C++ was executed successfully and the output was verified.
