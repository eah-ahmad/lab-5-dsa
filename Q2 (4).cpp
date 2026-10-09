// Name: Muhammad Ahmad
// Registration No: 542432
// Section: D
// DSA Lab 05 - Task 2: Insertion and deletion in a doubly linked list

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

    DoublyList(const DoublyList&) = delete;
    DoublyList& operator=(const DoublyList&) = delete;

    void AddNode(int incoming) {
        node* fresh = new node;
        fresh->data = incoming;
        fresh->next = nullptr;
        fresh->prev = tail;

        if (tail == nullptr) head = fresh;
        else tail->next = fresh;
        tail = fresh;
    }

    // Put a new node just before the node sitting at slotNo (1-based).
    // Returns false and leaves the list alone if slotNo has no node.
    bool InsertBefore(int slotNo, int incoming) {
        if (slotNo < 1 || head == nullptr) {
            cout << "Cannot insert: position " << slotNo << " is invalid." << endl;
            return false;
        }

        node* anchor = head;
        for (int step = 1; step < slotNo && anchor != nullptr; step++) {
            anchor = anchor->next;
        }
        if (anchor == nullptr) {
            cout << "Cannot insert: position " << slotNo << " is invalid." << endl;
            return false;
        }

        node* fresh = new node;
        fresh->data = incoming;
        fresh->next = anchor;
        fresh->prev = anchor->prev;

        if (anchor->prev == nullptr) {
            head = fresh;                 // inserting before the old head
        } else {
            anchor->prev->next = fresh;
        }
        anchor->prev = fresh;
        return true;
    }

    // Remove only the first node holding target.
    bool DeleteNode(int target) {
        if (head == nullptr) {
            cout << "Cannot delete " << target << ": list is empty." << endl;
            return false;
        }

        node* probe = head;
        while (probe != nullptr && probe->data != target) {
            probe = probe->next;
        }
        if (probe == nullptr) {
            cout << "Cannot delete " << target << ": value not found." << endl;
            return false;
        }

        if (probe->prev == nullptr) head = probe->next;
        else probe->prev->next = probe->next;

        if (probe->next == nullptr) tail = probe->prev;
        else probe->next->prev = probe->prev;

        delete probe;
        return true;
    }

    void PrintForward() const {
        if (head == nullptr) {
            cout << "Forward : list is empty." << endl;
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
            cout << "Reverse : list is empty." << endl;
            return;
        }
        cout << "Reverse : ";
        for (node* walker = tail; walker != nullptr; walker = walker->prev) {
            cout << walker->data;
            if (walker->prev != nullptr) cout << ", ";
        }
        cout << endl;
    }

    void PrintBoth() const {
        PrintForward();
        PrintReverse();
    }

    void ClearList() {
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
    DoublyList chain;

    cout << "--- Main case: 10, 20, 30 ---" << endl;
    chain.AddNode(10);
    chain.AddNode(20);
    chain.AddNode(30);
    chain.PrintBoth();

    cout << "\n--- InsertBefore(2, 15) ---" << endl;
    chain.InsertBefore(2, 15);
    chain.PrintBoth();

    cout << "\n--- DeleteNode(20)  (expect 10, 15, 30) ---" << endl;
    chain.DeleteNode(20);
    chain.PrintBoth();

    cout << "\n--- Insert before head: InsertBefore(1, 5) ---" << endl;
    chain.InsertBefore(1, 5);
    chain.PrintBoth();

    cout << "\n--- Invalid positions (list must not change) ---" << endl;
    chain.InsertBefore(0, 99);
    chain.InsertBefore(-3, 99);
    chain.InsertBefore(5, 99);    // list has 4 nodes, so 5 is past the end
    chain.PrintBoth();

    cout << "\n--- Delete head (5) ---" << endl;
    chain.DeleteNode(5);
    chain.PrintBoth();

    cout << "\n--- Delete tail (30) ---" << endl;
    chain.DeleteNode(30);
    chain.PrintBoth();

    cout << "\n--- Missing value (777) ---" << endl;
    chain.DeleteNode(777);
    chain.PrintBoth();

    cout << "\n--- Delete until the only node is gone (10, then 15) ---" << endl;
    chain.DeleteNode(10);
    chain.PrintBoth();
    chain.DeleteNode(15);
    chain.PrintBoth();

    cout << "\n--- Empty list ---" << endl;
    chain.DeleteNode(10);
    chain.InsertBefore(1, 10);
    chain.PrintBoth();

    cout << "\n--- Only-node case: add 42, delete 42 ---" << endl;
    chain.AddNode(42);
    chain.PrintBoth();
    chain.DeleteNode(42);
    chain.PrintBoth();

    cout << "\n--- Duplicates: 8, 9, 9, 8 then DeleteNode(9) removes first 9 only ---" << endl;
    chain.AddNode(8);
    chain.AddNode(9);
    chain.AddNode(9);
    chain.AddNode(8);
    chain.DeleteNode(9);
    chain.PrintBoth();

    chain.ClearList();
    return 0;
}
