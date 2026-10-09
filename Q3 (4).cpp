// Name: Muhammad Ahmad
// Registration No:542432
// Section: D
// DSA Lab 05 - Task 3: Creating and traversing a circular linked list
//
// Why a plain nullptr-based traversal never ends here:
//   In a non-empty circular list no node has next == nullptr, because the
//   last node (tail) points back to head. A loop like
//   "while (walker != nullptr) walker = walker->next;" therefore keeps going
//   round and round forever. We must stop after one full cycle instead,
//   i.e. when walker comes back to head (do-while loop below).

#include <iostream>
using namespace std;

class CircularList {
private:
    struct node {
        int data;
        node* next;
    };

    node* head;
    node* tail;

public:
    CircularList() : head(nullptr), tail(nullptr) {}
    ~CircularList() { ClearList(); }

    CircularList(const CircularList&) = delete;
    CircularList& operator=(const CircularList&) = delete;

    void AddNode(int incoming) {
        node* fresh = new node;
        fresh->data = incoming;

        if (tail == nullptr) {
            fresh->next = fresh;          // lone node points at itself
            head = fresh;
        } else {
            fresh->next = head;           // keep the ring closed
            tail->next = fresh;
        }
        tail = fresh;
    }

    void PrintList() const {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        node* walker = head;
        do {
            cout << walker->data;
            walker = walker->next;
            if (walker != head) cout << " -> ";
        } while (walker != head);
        cout << " -> (back to head)" << endl;
    }

    int CountNodes() const {
        if (head == nullptr) return 0;

        int tally = 0;
        node* walker = head;
        do {
            tally++;
            walker = walker->next;
        } while (walker != head);
        return tally;
    }

    void ClearList() {
        if (head == nullptr) return;

        tail->next = nullptr;             // open the ring first
        node* walker = head;
        while (walker != nullptr) {
            node* doomed = walker;
            walker = walker->next;
            delete doomed;
        }
        head = nullptr;
        tail = nullptr;
    }
};

int main() {
    CircularList ring;

    cout << "--- Empty list ---" << endl;
    ring.PrintList();
    cout << "Count: " << ring.CountNodes() << endl;

    cout << "\n--- One node (7) ---" << endl;
    ring.AddNode(7);
    ring.PrintList();
    cout << "Count: " << ring.CountNodes() << endl;

    ring.ClearList();

    cout << "\n--- 10, 20, 30 ---" << endl;
    ring.AddNode(10);
    ring.AddNode(20);
    ring.AddNode(30);
    ring.PrintList();
    cout << "Count: " << ring.CountNodes() << endl;

    ring.ClearList();
    cout << "\nAfter ClearList: count = " << ring.CountNodes() << endl;
    return 0;
}
