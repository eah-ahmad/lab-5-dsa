// Name: Muhammad Ahmad
// Registration No: 542432
// Section: D
// DSA Lab 05 - Task 6: Implementing a stack using linked nodes
//
// LIFO (last in, first out): the most recently pushed value is the first one
// popped, like a pile of plates - you add and take plates from the top only.
//
// Array stack (Task 5) vs linked stack (Task 6):
//   - ArrayStack has a fixed capacity of 5; the sixth push is rejected
//     (overflow) because the array size is decided at compile time.
//   - LinkedStack creates a new node with "new" on every push, so it grows
//     until memory runs out. There is no fixed limit and no IsFull().
//   - Both push and pop are O(1): the linked stack only touches the head.
//   - The linked stack must free its nodes (pop deletes one, ClearStack
//     deletes the rest); the array stack needs no cleanup.

#include <iostream>
using namespace std;

class LinkedStack {
private:
    struct node {
        int data;
        node* next;
    };

    node* top;

public:
    LinkedStack() : top(nullptr) {}
    ~LinkedStack() { ClearStack(); }

    LinkedStack(const LinkedStack&) = delete;
    LinkedStack& operator=(const LinkedStack&) = delete;

    bool IsEmpty() const { return top == nullptr; }

    void Push(int incoming) {
        node* fresh = new node;
        fresh->data = incoming;
        fresh->next = top;
        top = fresh;
        cout << "Pushed " << incoming << endl;
    }

    void Pop() {
        if (IsEmpty()) {
            cout << "Underflow: stack is empty, nothing to pop." << endl;
            return;
        }
        node* doomed = top;
        int gone = doomed->data;
        top = top->next;          // move top before deleting
        delete doomed;
        cout << "Popped " << gone << endl;
    }

    void Peek() const {
        if (IsEmpty()) {
            cout << "Underflow: stack is empty, nothing to peek." << endl;
            return;
        }
        cout << "Top element is " << top->data << endl;
    }

    void Display() const {
        if (IsEmpty()) {
            cout << "Stack is empty." << endl;
            return;
        }
        cout << "Stack (top -> bottom): ";
        for (node* walker = top; walker != nullptr; walker = walker->next) {
            cout << walker->data;
            if (walker->next != nullptr) cout << ", ";
        }
        cout << endl;
    }

    void ClearStack() {
        while (top != nullptr) {
            node* doomed = top;
            top = top->next;
            delete doomed;
        }
    }
};

static void showMenu() {
    cout << "\n===== Linked Stack Menu =====" << endl;
    cout << "1. Push" << endl;
    cout << "2. Pop" << endl;
    cout << "3. Peek" << endl;
    cout << "4. Display" << endl;
    cout << "5. Exit" << endl;
    cout << "Choice: ";
}

int main() {
    LinkedStack pile;
    int pick = 0;

    while (pick != 5) {
        showMenu();
        if (!(cin >> pick)) {
            cout << "\nInput ended, exiting." << endl;
            break;
        }

        if (pick == 1) {
            int incoming;
            cout << "Value to push: ";
            cin >> incoming;
            pile.Push(incoming);
        } else if (pick == 2) {
            pile.Pop();
        } else if (pick == 3) {
            pile.Peek();
        } else if (pick == 4) {
            pile.Display();
        } else if (pick == 5) {
            cout << "Releasing remaining nodes and exiting." << endl;
        } else {
            cout << "Invalid choice, please enter 1-5." << endl;
        }
    }

    pile.ClearStack();
    return 0;
}

/*
 Suggested test sequence (menu choices):
   1 10, 1 20, 1 30, 4   -> 30, 20, 10
   2 (pops 30), 3        -> top is 20
   2, 2, 2               -> empties, last one reports underflow
   9                     -> invalid choice
   1 5, 5                -> exit with a node still in the stack (cleared on exit)
*/
