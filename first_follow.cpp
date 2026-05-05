# Lab 5: Computation of FIRST and FOLLOW Sets

## Aim
To implement a C++ program to compute the FIRST and FOLLOW sets for a given context-free grammar.

## Introduction
FIRST and FOLLOW sets are fundamental concepts in compiler design and are used in the construction of predictive parsers. FIRST helps in determining which terminal symbols can appear at the beginning of a string derived from a non-terminal, while FOLLOW helps in identifying the terminals that can appear immediately after a non-terminal in a sentential form.

## Algorithm
1. Read the number of productions.
2. Accept grammar productions in the form `A=α`.
3. Identify all non-terminals and the start symbol.
4. Compute the FIRST set for each non-terminal.
5. Compute the FOLLOW set for each non-terminal:
   - Add `$` to the FOLLOW of the start symbol.
   - Apply grammar rules to find FOLLOW sets.
6. Display the FIRST and FOLLOW sets.

## Language Used
C++

## Tools Used
- VS Code
- GCC Compiler
- Git & GitHub

## Sample Input
    Enter number of productions: 5
    Enter productions (Example: E=TR):
    E=TR
    E=ε
    T=FY
    T=ε
    Y=*T
    F=(E)
    F=i

## Sample Output
    FIRST Sets:
    FIRST(E) = { (, ε }
    FIRST(T) = { (, ε }
    FIRST(Y) = { * }
    FIRST(F) = { (, i }

    FOLLOW Sets:
    FOLLOW(E) = { ), $ }
    FOLLOW(T) = { ), $ }
    FOLLOW(Y) = { ), $ }
    FOLLOW(F) = { *, ), $ }

## Result
Hence, the computation of FIRST and FOLLOW sets for a given context-free grammar was successfully implemented using
