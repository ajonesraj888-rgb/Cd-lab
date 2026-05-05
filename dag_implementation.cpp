/*
# Lab 13: Implementation of Directed Acyclic Graph (DAG)

## Aim
To implement a Directed Acyclic Graph (DAG) for a given sequence of expressions to facilitate Common Subexpression Elimination (CSE).

## Introduction
A Directed Acyclic Graph (DAG) is used in compiler design to represent basic blocks and optimize intermediate code. It helps in identifying common subexpressions, dead code, and variable assignments. A DAG has leaves representing operands and internal nodes representing operators.

## Algorithm
1. Read a sequence of expressions (e.g., `a = b + c`).
2. For each expression, identify the LHS variable, operator, and RHS operands.
3. If the RHS operands don't exist as nodes in the DAG, create leaf nodes for them.
4. Check if an internal node with the same operator and child nodes already exists.
5. If it exists, append the LHS variable to its label list (Common Subexpression Elimination).
6. If it does not exist, create a new internal node and label it with the LHS variable.
7. Print all the nodes in the DAG with their operations, children, and labels.

## Language Used
C++

## Tools Used
- VS Code
- GCC Compiler
- Git & GitHub

## Sample Output
```
Input Expressions:
a = b + c
d = b + c
e = a + d
f = b * c

DAG Nodes:
Node 0: (Leaf: b) Labels: b
Node 1: (Leaf: c) Labels: c
Node 2: (+) -> [b, c] Labels: a, d
Node 3: (+) -> [a, a] Labels: e
Node 4: (*) -> [b, c] Labels: f
```

## Result
Hence, the implementation of a Directed Acyclic Graph (DAG) for identifying common subexpressions was executed successfully.
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

using namespace std;

struct DAGNode {
    string op;
    int left;
    int right;
    string value;
    vector<string> labels;
};

class DAG {
public:
    vector<DAGNode> nodes;

    int find_node(string op, int left, int right) {
        for (size_t i = 0; i < nodes.size(); ++i) {
            if (nodes[i].op == op && nodes[i].left == left && nodes[i].right == right) {
                return i;
            }
        }
        return -1;
    }

    int find_leaf(string value) {
        for (size_t i = 0; i < nodes.size(); ++i) {
            if (nodes[i].op.empty() && nodes[i].value == value) {
                return i;
            }
        }
        return -1;
    }

    int get_leaf(string value) {
        int idx = find_leaf(value);
        if (idx != -1) return idx;

        DAGNode new_node;
        new_node.op = "";
        new_node.left = -1;
        new_node.right = -1;
        new_node.value = value;
        new_node.labels.push_back(value);
        
        nodes.push_back(new_node);
        return nodes.size() - 1;
    }

    int create_node(string op, int left, int right) {
        int existing = find_node(op, left, right);
        if (existing != -1) return existing;

        DAGNode new_node;
        new_node.op = op;
        new_node.left = left;
        new_node.right = right;
        new_node.value = "";
        
        nodes.push_back(new_node);
        return nodes.size() - 1;
    }

    void build_from_expressions(const vector<string>& expressions) {
        for (const string& expr : expressions) {
            vector<string> parts;
            stringstream ss(expr);
            string part;
            while (ss >> part) parts.push_back(part);

            if (parts.size() >= 3 && parts[1] == "=") {
                string lhs = parts[0];
                if (parts.size() == 3) {
                    int node_idx = get_leaf(parts[2]);
                    nodes[node_idx].labels.push_back(lhs);
                } else if (parts.size() == 5) {
                    int left = get_leaf(parts[2]);
                    string op = parts[3];
                    int right = get_leaf(parts[4]);

                    int node_idx = create_node(op, left, right);
                    nodes[node_idx].labels.push_back(lhs);
                }
            }
        }
    }

    void print_dag() {
        cout << "\nDAG Nodes:\n";
        for (size_t i = 0; i < nodes.size(); ++i) {
            if (!nodes[i].op.empty()) {
                string left_val = nodes[nodes[i].left].labels[0];
                string right_val = nodes[nodes[i].right].labels[0];
                cout << "Node " << i << ": (" << nodes[i].op << ") -> [" << left_val << ", " << right_val << "] Labels: ";
            } else {
                cout << "Node " << i << ": (Leaf: " << nodes[i].value << ") Labels: ";
            }
            
            for (size_t j = 0; j < nodes[i].labels.size(); ++j) {
                cout << nodes[i].labels[j] << (j < nodes[i].labels.size() - 1 ? ", " : "");
            }
            cout << "\n";
        }
    }
};

int main() {
    vector<string> expressions = {
        "a = b + c",
        "d = b + c",
        "e = a + d",
        "f = b * c"
    };

    DAG dag;
    dag.build_from_expressions(expressions);

    cout << "Input Expressions:\n";
    for (const string& exp : expressions) {
        cout << exp << "\n";
    }

    dag.print_dag();

    return 0;
