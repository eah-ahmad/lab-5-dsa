// Name: Muhammad Ahmad
// Registration No: 542432
// Section: D
// DSA Lab 05 - Task 5: Implementing a stack using an array

#include <iostream>
using namespace std;

class ArrayStack {
private:
    static const int LIMIT = 5;
    int items[5];
    int top;

public:
    ArrayStack() : top(-1) {}

    bool IsEmpty() const { return top == -1; }
    bool IsFull() const { return top == LIMIT - 1; }

    void Push(int incoming) {
        if (IsFull()) {
            cout << "Overflow: stack is full, cannot push " << incoming << "." << endl;
            return;
        }
        items[++top] = incoming;
        cout << "Pushed " << incoming << endl;
    }

    void Pop() {
        if (IsEmpty()) {
            cout << "Underflow: stack is empty, nothing to pop." << endl;
            return;
        }
        int gone = items[top--];
        cout << "Popped " << gone << endl;
    }

    void Peek() const {
        if (IsEmpty()) {
            cout << "Underflow: stack is empty, nothing to peek." << endl;
            return;
        }
        cout << "Top element is " << items[top] << endl;
    }

    // top to bottom
    void Display() const {
        if (IsEmpty()) {
            cout << "Stack is empty." << endl;
            return;
        }
        cout << "Stack (top -> bottom): ";
        for (int slot = top; slot >= 0; slot--) {
            cout << items[slot];
            if (slot > 0) cout << ", ";
        }
        cout << endl;
    }
};

int main() {
    ArrayStack pile;

    cout << "--- Push 10, 20, 30, 40, 50 ---" << endl;
    pile.Push(10);
    pile.Push(20);
    pile.Push(30);
    pile.Push(40);
    pile.Push(50);
    pile.Display();

    cout << "\n--- Sixth push must be rejected ---" << endl;
    pile.Push(60);
    pile.Display();

    cout << "\n--- Pop 50, then peek 40 ---" << endl;
    pile.Pop();
    pile.Peek();
    pile.Display();

    cout << "\n--- Empty the stack ---" << endl;
    while (!pile.IsEmpty()) {
        pile.Pop();
    }
    pile.Display();

    cout << "\n--- One more pop and peek on empty stack ---" << endl;
    pile.Pop();
    pile.Peek();
    return 0;
}
