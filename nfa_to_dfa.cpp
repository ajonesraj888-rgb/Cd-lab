# Lab 3: Conversion of NFA to DFA

## Aim
To implement a C++ program that converts a given Non-Deterministic Finite Automaton (NFA) into an equivalent Deterministic Finite Automaton (DFA) using the subset construction method.

## Introduction
A Non-Deterministic Finite Automaton (NFA) allows multiple transitions for the same input symbol, whereas a Deterministic Finite Automaton (DFA) allows only one transition per symbol from a state. Since DFAs are easier to implement, NFAs are often converted into DFAs. This experiment demonstrates the conversion of an NFA into a DFA.

## Algorithm
1. Read the number of NFA states and transitions.
2. Accept the transition function of the NFA.
3. Consider the start state of the DFA as the set containing the start state of the NFA.
4. For each DFA state and input symbol:
   - Find all possible NFA transitions.
   - Form a new DFA state as a subset of NFA states.
5. Repeat the process until no new DFA states are generated.
6. Display the DFA transition table.

## Language Used
C++

## Tools Used
- VS Code
- GCC Compiler
- Git & GitHub

## Sample Input
```
Enter number of NFA states: 4
Enter number of transitions: 5
Enter transitions (from symbol to):
0 a 1
0 b 2
1 a 3
2 b 3
3 a 3
```

## Sample Output
```
DFA Transition Table:
{ 0 } : a -> { 1 3 } b -> { 2 }
{ 1 3 } : a -> { 1 3 } b -> { 2 }
{ 2 } : b -> { 2 }
```

## Result
Hence, the conversion of a Non-Deterministic Finite Automaton (NFA) to a Deterministic Finite Automaton (DFA) was successfully implemented using C++.
