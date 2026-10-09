// Name: Muhammad Ahmad
// Registration No: 542432
// Section: D
// DSA Lab 05 - Task 1: Creating and traversing a doubly linked list

#include <iostream>
using namespace std;

class DoublyList {
private:
    struct node {
        int data;
        node* next;
        node* prev;
    };

    node* head;
    node* tail;

public:
    DoublyList() : head(nullptr), tail(nullptr) {}
    ~DoublyList() { ClearList(); }

    // lists are never copied in this lab
    DoublyList(const DoublyList&) = delete;
    DoublyList& operator=(const DoublyList&) = delete;

    // append at the tail, fixing both next and prev
    void AddNode(int incoming) {
        node* fresh = new node;
        fresh->data = incoming;
        fresh->next = nullptr;
        fresh->prev = tail;       // nullptr if list was empty

        if (tail == nullptr) {
            head = fresh;
        } else {
            tail->next = fresh;
        }
        tail = fresh;
    }

    void PrintForward() const {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        cout << "Forward : ";
        for (node* walker = head; walker != nullptr; walker = walker->next) {
            cout << walker->data;
            if (walker->next != nullptr) cout << ", ";
        }
        cout << endl;
    }

    void PrintReverse() const {
        if (tail == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        cout << "Reverse : ";
        for (node* walker = tail; walker != nullptr; walker = walker->prev) {
            cout << walker->data;
            if (walker->prev != nullptr) cout << ", ";
        }
        cout << endl;
    }

    void ClearList() {
        node* walker = head;
        while (walker != nullptr) {
            node* doomed = walker;
            walker = walker->next;    // save the link before deleting
            delete doomed;
        }
        head = nullptr;
        tail = nullptr;
    }
};

int main() {
    DoublyList chain;
    int howMany;

    cout << "How many numbers do you want to add? ";
    cin >> howMany;

    for (int round = 1; round <= howMany; round++) {
        int entry;
        cout << "Enter number " << round << ": ";
        cin >> entry;
        chain.AddNode(entry);
    }

    chain.PrintForward();
    chain.PrintReverse();

    chain.ClearList();
    return 0;
}
