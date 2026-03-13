#include <iostream>
using namespace std;

template<typename T>
struct Node{
    T data;
    Node* next;
    Node* prev;
    Node(const T& v) : data(v), next(NULL), prev(NULL) {}

};

template<typename T>
class DoublyCircularLinkedList{
public:
    Node<T>* head;
    Node<T>* tail;
    int size;
    DoublyCircularLinkedList() : head(NULL), tail(NULL),size(0){}
    ~DoublyCircularLinkedList(){
        while (!isEmpty()) {
            pop_front();
        }
    }
    bool isEmpty() const;
    int getSize() const;
    T front() const;
    T back() const;

    void push_front(const T& x);
    void push_back(const T& x);
    void insertAt(int index, const T& x);

    void pop_front();
    void pop_back();
    void removeAt(int index);

    T getAt(int index) const;
    void setAt(int index, const T& x);

    int indexOf(const T& x) const;

    void printForward(int idx) const;
    void printBackward(int idx) const;

};

template<typename T>
bool DoublyCircularLinkedList<T>::isEmpty() const {
    return head == NULL && tail == NULL;
}
template<typename T>
int DoublyCircularLinkedList<T>::getSize() const {
    return size;
}

template<typename T>
T DoublyCircularLinkedList<T>::front() const {
    if (isEmpty()) return T();
    Node<T>* cur = head;
    return cur->data;
}

template<typename T>
T DoublyCircularLinkedList<T>::back() const {
    if (isEmpty()) return T();
    Node<T>* cur = tail;
    return cur->data;
}

template<typename T>
void DoublyCircularLinkedList<T>::push_front(const T &x) {
    Node<T>* newNode = new Node<T>(x);
    if (isEmpty()){
        head = tail = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
        size++;
        return;
    }
    newNode->next = head;
    newNode->prev = tail;

    head->prev = newNode;
    tail->next = newNode;
    head = newNode;
    size++;
}

template<typename T>
void DoublyCircularLinkedList<T>::push_back(const T &x) {
    Node<T>* newNode = new Node<T>(x);
    if (isEmpty()) {
        head = tail = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
        size++;
        return;
    }

    newNode->next = head;
    newNode->prev = tail;

    tail->next = newNode;
    head->prev = newNode;

    tail = newNode;
    size++;
}

template<typename T>
void DoublyCircularLinkedList<T>::insertAt(int index, const T &x) {
    if (index < 0 || index > this->getSize()) return;
    if (isEmpty()) {
        Node<T>* newNode = new Node<T>(x);
        head = tail = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
        size++;
        return;
    }
    if (index == 0) {
        push_front(x);
        size++;
        return;
    }
    if (index == this->getSize()) {
        push_back(x);
        size++;
        return;
    }
    Node<T>* cur = head;
    int curPos = 0;
    while(curPos != index){
        curPos++;
        cur = cur->next;
    }
    Node<T>* newNode = new Node<T>(x);
    newNode->next = cur;
    newNode->prev = cur->prev;
    cur->prev->next = newNode;
    cur->prev = newNode;
    size++;
}

template<typename T>
void DoublyCircularLinkedList<T>::pop_front() {
    if (isEmpty()) return;
    if (head == tail){
        delete head;
        head = tail = NULL;
        size--;
        return;
    }
    Node<T>* oldHead = head;
    Node<T>* newHead = head->next;

    tail->next = newHead;
    newHead->prev = tail;

    head = newHead;
    size--;
    delete oldHead;
}
template<typename T>
void DoublyCircularLinkedList<T>::pop_back() {
    if (isEmpty()) return;
    if (head == tail){
        delete tail;
        head = tail = NULL;
        size--;
        return;
    }
    Node<T>* oldTail = tail;
    Node<T>* newTail = tail->prev;
    newTail->next = head;
    head->prev = newTail;
    tail = newTail;
    delete oldTail;
}

template<typename T>
void DoublyCircularLinkedList<T>::removeAt(int index) {
    if (index < 0 || index >= this->getSize()) return;
    if (isEmpty()) return;
    if (head == tail){
        delete tail;
        head = tail = NULL;
        size--;
        return;
    }

    if (index == 0) {
        pop_front();
        size--;
        return;
    }
    if (index == this->getSize()-1) {
        pop_back();
        size--;
        return;
    }

    Node<T>* cur = head;
    int curPos = 0;
    while(curPos != index){
        curPos++;
        cur = cur->next;
    }
    Node<T>* prevNode = cur->prev;
    Node<T>* nextNode = cur->next;
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
    delete cur;
    size--;
}

template<typename T>
T DoublyCircularLinkedList<T>::getAt(int index) const {
    int size = this->getSize();
    if (index < 0 || index >= size) return T();
    if (isEmpty()) return T();

    Node<T>* cur = head;
    int pos = 0;
    while (pos != index) {
        cur = cur->next;
        pos++;
    }
    return cur->data;
}

template<typename T>
void DoublyCircularLinkedList<T>::setAt(int index, const T& x) {
    int size = this->getSize();
    if (index < 0 || index >= size) return;
    if (isEmpty()) return;

    Node<T>* cur = head;
    int pos = 0;
    while (pos != index) {
        cur = cur->next;
        pos++;
    }
    cur->data = x;
}

template<typename T>
int DoublyCircularLinkedList<T>::indexOf(const T& x) const {
    if (isEmpty()) return -1;

    int size = this->getSize();
    Node<T>* cur = head;
    int pos = 0;

    while (pos < size) {
        if (cur->data == x) return pos;
        cur = cur->next;
        pos++;
    }
    return -1;
}

template<typename T>
void DoublyCircularLinkedList<T>::printForward(int idx) const {
    int size = this->getSize();
    if (size == 0) {
        cout << "[]\n";
        return;
    }

    if (idx < 0 || idx >= size) return;

    Node<T>* cur = head;
    int pos = 0;
    while (pos != idx) {
        cur = cur->next;
        pos++;
    }

    cout << "[";
    int printed = 0;
    while (printed < size) {
        if (printed > 0) std::cout << ", ";
        cout << cur->data;
        cur = cur->next;
        printed++;
    }
    cout << "]\n";
}

template<typename T>
void DoublyCircularLinkedList<T>::printBackward(int idx) const {
    int size = this->getSize();
    if (size == 0) {
        cout << "[]\n";
        return;
    }
    if (idx < 0 || idx >= size) return;

    Node<T>* cur = head;
    int pos = 0;
    while (pos != idx) {
        cur = cur->next;
        pos++;
    }

    cout << "[";
    int printed = 0;

    while (printed < size) {
        if (printed > 0) cout << ", ";
        cout << cur->data;
        cur = cur->prev;
        printed++;
    }
    cout << "]\n";
}

struct Contact {
    string name;
    string phone;

    Contact() {}
    Contact(const string& n, const string& p) : name(n), phone(p) {}
    bool operator==(const Contact& other) const {
        return name == other.name || phone == other.phone;
    }
};
ostream& operator<<(ostream& os, const Contact& c) {
    os << c.name << " - " << c.phone;
    return os;
}


int main() {

    DoublyCircularLinkedList<Contact> contacts;

    int choice = 0;

    while (choice != 6) {

        cout << "\n1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. Display\n";
        cout << "5. Size\n";
        cout << "6. Quit\n";
        cout << "Choice: ";

        cin >> choice;
        cin.ignore(10000, '\n');

        // ---------------- INSERT ----------------
        if (choice == 1) {

            string name, phone;
            cout << "Name: ";
            getline(cin, name);
            cout << "Phone: ";
            getline(cin, phone);

            contacts.push_back(Contact(name, phone));
            cout << "Inserted.\n";
        }

            // ---------------- DELETE ----------------
        else if (choice == 2) {

            if (contacts.isEmpty()) {
                cout << "List empty.\n";
                continue;
            }

            string key;
            cout << "Enter name OR phone to delete: ";
            getline(cin, key);

            int i = contacts.getSize() - 1;
            bool found = false;

            while (i >= 0) {
                Contact c = contacts.getAt(i);
                if (c.name == key || c.phone == key) {
                    contacts.removeAt(i);
                    found = true;
                }
                i--;
            }

            if (!found) cout << "Not found.\n";
            else cout << "Deleted.\n";
        }

            // ---------------- SEARCH ----------------
        else if (choice == 3) {

            if (contacts.isEmpty()) {
                cout << "List empty.\n";
                continue;
            }

            string key;
            cout << "Enter name OR phone to search: ";
            getline(cin, key);

            int i = 0;
            bool found = false;

            while (i < contacts.getSize()) {
                Contact c = contacts.getAt(i);
                if (c.name == key || c.phone == key) {
                    cout << c.name << " - " << c.phone << endl;
                    found = true;
                }
                i++;
            }

            if (!found) cout << "Not found.\n";
        }

            // ---------------- DISPLAY ----------------
        else if (choice == 4) {

            if (contacts.isEmpty()) {
                cout << "List empty.\n";
                continue;
            }

            string phone;
            cout << "Start phone: ";
            getline(cin, phone);

            int start = -1;
            int i = 0;

            while (i < contacts.getSize()) {
                if (contacts.getAt(i).phone == phone) {
                    start = i;
                    break;
                }
                i++;
            }

            if (start == -1) {
                cout << "Phone not found.\n";
                continue;
            }

            char dir;
            cout << "Direction (F/B): ";
            cin >> dir;
            cin.ignore(10000, '\n');

            if (dir == 'B' || dir == 'b')
                contacts.printBackward(start);
            else
                contacts.printForward(start);
        }

            // ---------------- SIZE ----------------
        else if (choice == 5) {
            cout << "Size: " << contacts.getSize() << endl;
        }

            // ---------------- QUIT ----------------
        else if (choice == 6) {
            cout << "Bye.\n";
        }

        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}




















