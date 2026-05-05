Lab 6: Construction of Predictive Parsing Table (LL(1))

## Aim
To implement a C++ program to construct a predictive parsing table for a given grammar using FIRST and FOLLOW sets.

## Introduction
Predictive parsing is a top-down parsing technique used in LL(1) parsers. The predictive parsing table is constructed using the FIRST and FOLLOW sets of the grammar. Each entry in the table specifies the production rule to be applied for a given non-terminal and input symbol.

## Algorithm
1. Read the number of grammar productions.
2. Accept grammar productions in the form `A=α`.
3. Identify all non-terminals, terminals, and the start symbol.
4. Compute the FIRST set for each non-terminal.
5. Compute the FOLLOW set for each non-terminal.
6. Construct the predictive parsing table using the FIRST and FOLLOW sets.
7. Display the predictive parsing table entries.

## Language Used
C++

## Tools Used
- VS Code
- GCC Compiler
- Git & GitHub

## Sample Input
```
Enter number of productions: 5
Enter productions (Example: E=TR):
E=TR
E=ε
T=FY
T=ε
Y=*T
F=(E)
F=i
```

## Sample Output
```
Predictive Parsing Table:
M[E,(] = E -> TR
M[E,i] = E -> TR
M[E,$] = E -> ε
M[T,(] = T -> FY
M[T,i] = T -> FY
M[T,$] = T -> ε
M[Y,*) = Y -> *T
M[Y,$] = Y -> ε
M[F,(] = F -> (E)
M[F,i] = F -> i
```

## Result
Hence, the construction of a predictive parsing table for a given grammar using FIRST and FOLLOW sets was successfully implemented using C++.
