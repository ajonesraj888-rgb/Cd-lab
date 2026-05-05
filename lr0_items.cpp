*
# Lab 9: Computation of LR(0) Items

## Aim
To implement a C++ program for the construction of LR(0) items and the canonical collection of LR(0) states for a given context-free grammar.

## Introduction
LR(0) items are fundamental to building bottom-up LR parsers (such as SLR, CLR, and LALR). An LR(0) item of a grammar G is a production of G with a dot at some position of the body. The canonical collection of sets of LR(0) items provides the states of a deterministic finite automaton (DFA) that is used to make parsing decisions.

## Algorithm
1. Augment the grammar by adding a new start symbol `S'` -> `S`.
2. Define a `closure` function:
   - For every item `[A -> α•Bβ]` in the set, add `[B -> •γ]` for all productions `B -> γ` to the set.
   - Repeat until no new items can be added.
3. Define a `goto` function:
   - `goto(I, X)` is defined as the closure of the set of all items `[A -> αX•β]` such that `[A -> α•Xβ]` is in `I`.
4. Construct the Canonical Collection `C`:
   - Start with `C = { closure({ [S' -> •S] }) }`.
   - For each state `I` in `C` and each grammar symbol `X`:
     - Calculate `goto(I, X)`.
     - If it's not empty and not already in `C`, add it to `C`.
5. Print all states and their transitions.

## Language Used
C++

## Tools Used
- VS Code
- GCC Compiler
- Git & GitHub

## Sample Output
```
LR(0) Item Sets:
I0:
S' -> •E
E -> •E + T
E -> •T
T -> •T * F
T -> •F
F -> •( E )
F -> •id
...
Transitions:
I0 -- E --> I1
I0 -- T --> I2
...
```

## Result
Hence, the computation of LR(0) items and the canonical collection was implemented successfully using C++.
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

struct Item {
    string head;
    vector<string> body;
    int dot_pos;

    bool operator<(const Item& other) const {
        if (head != other.head) return head < other.head;
        if (body != other.body) return body < other.body;
        return dot_pos < other.dot_pos;
    }

    bool operator==(const Item& other) const {
        return head == other.head && body == other.body && dot_pos == other.dot_pos;
    }
};

map<string, vector<vector<string>>> grammar = {
    {"S'", {{"E"}}},
    {"E", {{"E", "+", "T"}, {"T"}}},
    {"T", {{"T", "*", "F"}, {"F"}}},
    {"F", {{"(", "E", ")"}, {"id"}}}
};

set<Item> closure(set<Item> items) {
    set<Item> closure_set = items;
    bool changed = true;

    while (changed) {
        changed = false;
        set<Item> new_items = closure_set;

        for (const auto& item : closure_set) {
            if (item.dot_pos < item.body.size()) {
                string symbol = item.body[item.dot_pos];

                if (grammar.find(symbol) != grammar.end()) {
                    for (const auto& prod : grammar[symbol]) {
                        Item new_item = {symbol, prod, 0};
                        if (new_items.find(new_item) == new_items.end()) {
                            new_items.insert(new_item);
                            changed = true;
                        }
                    }
                }
            }
        }
        closure_set = new_items;
    }
    return closure_set;
}

set<Item> goto_state(const set<Item>& items, const string& symbol) {
    set<Item> moved;
    for (const auto& item : items) {
        if (item.dot_pos < item.body.size() && item.body[item.dot_pos] == symbol) {
            moved.insert({item.head, item.body, item.dot_pos + 1});
        }
    }
    return closure(moved);
}

void canonical_collection() {
    Item start_item = {"S'", grammar["S'"][0], 0};
    set<Item> start_set = closure({start_item});

    vector<set<Item>> C;
    C.push_back(start_set);

    struct Transition {
        int from;
        string symbol;
        int to;
    };
    vector<Transition> transitions;

    set<string> symbols;
    for (const auto& pair : grammar) {
        for (const auto& prod : pair.second) {
            for (const string& sym : prod) {
                symbols.insert(sym);
            }
        }
    }

    bool changed = true;
    while (changed) {
        changed = false;
        int current_size = C.size();

        for (int i = 0; i < current_size; ++i) {
            for (const string& symbol : symbols) {
                set<Item> g = goto_state(C[i], symbol);
                if (!g.empty()) {
                    auto it = find(C.begin(), C.end(), g);
                    int to_index;
                    if (it == C.end()) {
                        C.push_back(g);
                        to_index = C.size() - 1;
                        changed = true;
                    } else {
                        to_index = distance(C.begin(), it);
                    }

                    // Avoid duplicate transitions
                    bool trans_exists = false;
                    for (const auto& t : transitions) {
                        if (t.from == i && t.symbol == symbol && t.to == to_index) {
                            trans_exists = true; break;
                        }
                    }
                    if (!trans_exists) {
                        transitions.push_back({i, symbol, to_index});
                    }
                }
            }
        }
    }

    cout << "LR(0) Item Sets:\n";
    for (size_t i = 0; i < C.size(); ++i) {
        cout << "\nI" << i << ":\n";
        for (const auto& item : C[i]) {
            cout << item.head << " -> ";
            for (int j = 0; j < item.body.size(); ++j) {
                if (j == item.dot_pos) cout << ". ";
                cout << item.body[j] << " ";
            }
            if (item.dot_pos == item.body.size()) cout << ".";
            cout << "\n";
        }
    }

    cout << "\nTransitions:\n";
    for (const auto& t : transitions) {
        cout << "I" << t.from << " -- " << t.symbol << " --> I" << t.to << "\n";
    }
}

int main() {
    canonical_collection();
    return 0;
}
