// Name: Muhammad Ahmad
// Registration No: 542432
// Section: D
// DSA Lab 05 - Task 4: Deletion in a circular linked list

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
            fresh->next = fresh;
            head = fresh;
        } else {
            fresh->next = head;
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

    // Remove the first node equal to target; search stops after one cycle.
    bool DeleteNode(int target) {
        if (head == nullptr) {
            cout << "Cannot delete " << target << ": list is empty." << endl;
            return false;
        }

        node* behind = tail;      // always sits one step behind probe
        node* probe = head;
        do {
            if (probe->data == target) {
                if (probe == head && probe == tail) {
                    // the only node
                    head = nullptr;
                    tail = nullptr;
                } else {
                    behind->next = probe->next;
                    if (probe == head) head = probe->next;
                    if (probe == tail) tail = behind;
                }
                delete probe;
                return true;
            }
            behind = probe;
            probe = probe->next;
        } while (probe != head);

        cout << "Cannot delete " << target << ": value not found." << endl;
        return false;
    }

    void ClearList() {
        if (head == nullptr) return;

        tail->next = nullptr;
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

// small helper so the test output stays tidy
static void showState(const CircularList& ring) {
    ring.PrintList();
    cout << "Count: " << ring.CountNodes() << endl;
}

int main() {
    CircularList ring;

    cout << "--- Empty list: DeleteNode(5) ---" << endl;
    ring.DeleteNode(5);
    showState(ring);

    cout << "\n--- Build 10, 20, 30 ---" << endl;
    ring.AddNode(10);
    ring.AddNode(20);
    ring.AddNode(30);
    showState(ring);

    cout << "\n--- Missing value: DeleteNode(99) ---" << endl;
    ring.DeleteNode(99);
    showState(ring);

    cout << "\n--- Delete head (10) ---" << endl;
    ring.DeleteNode(10);
    showState(ring);

    cout << "\n--- Delete tail (30) ---" << endl;
    ring.DeleteNode(30);
    showState(ring);

    cout << "\n--- Delete the only node (20) ---" << endl;
    ring.DeleteNode(20);
    showState(ring);
    cout << "(head and tail are now both nullptr)" << endl;

    cout << "\n--- Middle node: build 1, 2, 3, 4 and delete 3 ---" << endl;
    ring.AddNode(1);
    ring.AddNode(2);
    ring.AddNode(3);
    ring.AddNode(4);
    ring.DeleteNode(3);
    showState(ring);
    ring.ClearList();

    cout << "\n--- Duplicates: 10, 20, 20, 30 then DeleteNode(20) once ---" << endl;
    ring.AddNode(10);
    ring.AddNode(20);
    ring.AddNode(20);
    ring.AddNode(30);
    ring.DeleteNode(20);
    showState(ring);

    ring.ClearList();
    cout << "\nAfter ClearList:" << endl;
    showState(ring);
    return 0;
}
