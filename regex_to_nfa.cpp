# Lab 2: Conversion of Regular Expression to NFA

## Aim
To design and implement a C++ program that converts a given regular expression into its equivalent Non-Deterministic Finite Automaton (NFA).

## Introduction
A regular expression is a formal way to describe patterns in strings. A Non-Deterministic Finite Automaton (NFA) is an automaton that can have multiple transitions for a single input symbol and can also include epsilon (ε) transitions. This experiment demonstrates how a basic regular expression can be converted into an NFA representation.

## Algorithm
1. Read the regular expression from the user.
2. Initialize the starting state as 0.
3. For each character in the regular expression:
   - If the character is a symbol, create a transition to a new state.
   - If the character is `*` (Kleene star), add epsilon transitions to represent repetition.
4. Store all transitions in a data structure.
5. Display the NFA transitions along with start and final states.

## Language Used
C++

## Tools Used
- VS Code
- GCC Compiler
- Git & GitHub

## Sample Input
```
ab*c
```

## Sample Output
```
NFA Transitions:
From    Symbol  To
0       a       1
1       b       2
2       ε       1
2       ε       3
3       c       4

Start State: 0
Final State: 4
```

## Result
Thus, the conversion of a regular expression to a Non-Deterministic Finite Automaton (NFA) was successfully implemented using C++.
