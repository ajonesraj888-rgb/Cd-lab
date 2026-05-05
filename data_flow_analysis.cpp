/*
# Lab 14: Implementation of Global Data Flow Analysis

## Aim
To implement Global Data Flow Analysis using Reaching Definitions for program optimization.

## Introduction
Global Data Flow Analysis collects information about the flow of data across basic blocks in a control flow graph (CFG). "Reaching Definitions" is a type of data flow analysis that determines which definitions of variables may reach a particular point in the program.

## Algorithm
1. Represent the CFG as a set of basic blocks.
2. For each block, identify its GEN (definitions created in the block) and KILL (definitions overwritten in the block) sets.
3. Initialize the IN and OUT sets for all blocks to empty.
4. Iteratively update the IN and OUT sets:
   - `IN[B] = Union of OUT[P]` for all predecessors `P` of block `B`.
   - `OUT[B] = GEN[B] U (IN[B] - KILL[B])`.
5. Repeat step 4 until no changes occur in the IN or OUT sets of any block.
6. Display the final GEN, KILL, IN, and OUT sets.

## Language Used
C++

## Tools Used
- VS Code
- GCC Compiler
- Git & GitHub

## Sample Output
```
Reaching Definitions Analysis:

B1:
  GEN  = { a=1, b=2 }
  KILL = { }
  IN   = { }
  OUT  = { a=1, b=2 }

B2:
  GEN  = { a=3 }
  KILL = { a=1 }
  IN   = { a=1, b=2 }
  OUT  = { a=3, b=2 }

B3:
  GEN  = { c=a+b }
  KILL = { }
  IN   = { a=1, a=3, b=2 }
  OUT  = { a=1, a=3, b=2, c=a+b }
```

## Result
Hence, the implementation of global data flow analysis using reaching definitions was executed successfully.
*/

#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

struct BasicBlock {
    string name;
    set<string> gen;
    set<string> kill;
    set<string> in_set;
    set<string> out_set;
    vector<int> predecessors; // Indices of predecessor blocks
};

void reaching_definitions(vector<BasicBlock>& blocks) {
    bool changed = true;

    while (changed) {
        changed = false;

        for (size_t i = 0; i < blocks.size(); ++i) {
            set<string> new_in;
            for (int pred_idx : blocks[i].predecessors) {
                for (const string& val : blocks[pred_idx].out_set) {
                    new_in.insert(val);
                }
            }

            set<string> new_out = blocks[i].gen;
            for (const string& val : new_in) {
                if (blocks[i].kill.find(val) == blocks[i].kill.end()) {
                    new_out.insert(val);
                }
            }

            if (new_in != blocks[i].in_set || new_out != blocks[i].out_set) {
                blocks[i].in_set = new_in;
                blocks[i].out_set = new_out;
                changed = true;
            }
        }
    }
}

void print_set(const set<string>& s) {
    cout << "{ ";
    bool first = true;
    for (const string& val : s) {
        if (!first) cout << ", ";
        cout << val;
        first = false;
    }
    cout << " }";
}

int main() {
    vector<BasicBlock> blocks(3);
    
    blocks[0].name = "B1";
    blocks[0].gen = {"a=1", "b=2"};
    blocks[0].kill = {};
    
    blocks[1].name = "B2";
    blocks[1].gen = {"a=3"};
    blocks[1].kill = {"a=1"};
    blocks[1].predecessors = {0}; // B1 -> B2

    blocks[2].name = "B3";
    blocks[2].gen = {"c=a+b"};
    blocks[2].kill = {};
    blocks[2].predecessors = {0, 1}; // B1 -> B3, B2 -> B3

    reaching_definitions(blocks);

    cout << "Reaching Definitions Analysis:\n\n";
    for (const auto& block : blocks) {
        cout << block.name << ":\n";
        
        cout << "  GEN  = "; print_set(block.gen); cout << "\n";
        cout << "  KILL = "; print_set(block.kill); cout << "\n";
        cout << "  IN   = "; print_set(block.in_set); cout << "\n";
        cout << "  OUT  = "; print_set(block.out_set); cout << "\n\n";
    }

    return 0;
}
