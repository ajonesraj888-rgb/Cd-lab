/*
# Lab 15: Storage Allocation Strategies (Stack Allocation)

## Aim
To implement and demonstrate Stack Storage Allocation, a key runtime memory management strategy used in Compiler Design.

## Introduction
During the execution of a program, memory is allocated to store variables, arguments, and return values. Stack Allocation is used primarily to manage the memory of function calls. When a function is called, an Activation Record (or stack frame) is pushed onto the stack. When the function returns, the Activation Record is popped off.

## Algorithm
1. Create a `Stack` to manage `ActivationRecord` instances.
2. Define an `ActivationRecord` class/structure containing:
   - Function name
   - Return address
   - Local variables map
3. When a function is called (e.g., `main`, `foo`, `bar`):
   - Instantiate an `ActivationRecord`.
   - Set local variables in it.
   - Push the record onto the `Stack`.
   - Display the state of the stack.
4. When a function returns:
   - Pop the `ActivationRecord` from the `Stack`.
   - Display the new state of the stack.

## Language Used
C++

## Tools Used
- VS Code
- GCC Compiler
- Git & GitHub

## Sample Output
```
PUSH: main
--- Stack State ---
0: main | Locals: { a: 10 }
-------------------

PUSH: foo
--- Stack State ---
1: foo | Locals: { x: 20 }
0: main | Locals: { a: 10 }
-------------------
...
POP: bar
...
```

## Result
Hence, the Stack Storage Allocation strategy demonstrating function call activation records was executed successfully in C++.
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class ActivationRecord {
public:
    string function_name;
    string return_address;
    map<string, int> local_variables;

    ActivationRecord(string fname, string raddr) : function_name(fname), return_address(raddr) {}

    void set_variable(string var, int value) {
        local_variables[var] = value;
    }

    void print() const {
        cout << function_name << " | Locals: { ";
        bool first = true;
        for (const auto& pair : local_variables) {
            if (!first) cout << ", ";
            cout << pair.first << ": " << pair.second;
            first = false;
        }
        cout << " }";
    }
};

class Stack {
private:
    vector<ActivationRecord> stack_frames;

public:
    void push(const ActivationRecord& ar) {
        cout << "\nPUSH: " << ar.function_name << "\n";
        stack_frames.push_back(ar);
        display();
    }

    void pop() {
        if (!stack_frames.empty()) {
            ActivationRecord ar = stack_frames.back();
            stack_frames.pop_back();
            cout << "\nPOP: " << ar.function_name << "\n";
            display();
        }
    }

    void display() const {
        cout << "--- Stack State ---\n";
        for (int i = stack_frames.size() - 1; i >= 0; --i) {
            cout << i << ": ";
            stack_frames[i].print();
            cout << "\n";
        }
        cout << "-------------------\n";
    }
};

int main() {
    Stack call_stack;

    ActivationRecord main_ar("main", "start");
    main_ar.set_variable("a", 10);
    call_stack.push(main_ar);

    ActivationRecord foo_ar("foo", "main");
    foo_ar.set_variable("x", 20);
    call_stack.push(foo_ar);

    ActivationRecord bar_ar("bar", "foo");
    bar_ar.set_variable("y", 30);
    call_stack.push(bar_ar);

    call_stack.pop();
    call_stack.pop();
    call_stack.pop();

    return 0;
}
