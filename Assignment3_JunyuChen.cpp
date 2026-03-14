#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* parent;
    std::vector<Node<T>*> children;
    Node(const T& x)
            : data(x), parent(nullptr) {}
};

template <typename T>
class MyTree {
private:
    Node<T>* root;
    int size;
// (recommended) helper for recursive deletion
    void deleteSubtree(Node<T>* p){
        if (p == nullptr) {
            return;
        }
        for (int i = 0; i < (int)p->children.size(); i++) {
            deleteSubtree(p->children[i]);
        }
        delete p;
    }

    void printPreorderHelper(Node<T>* p) const {
        if (p == nullptr) {
            return;
        }

        cout << p->data << " ";

        for (int i = 0; i < (int)p->children.size(); i++) {
            printPreorderHelper(p->children[i]);
        }
    }

    void printPostorderHelper(Node<T>* p) const {
        if (p == nullptr) {
            return;
        }

        for (int i = 0; i < (int)p->children.size(); i++) {
            printPostorderHelper(p->children[i]);
        }

        cout << p->data << " ";
    }

public:
    MyTree();
    ~MyTree(){};
    bool isEmpty() const{
        return root == nullptr;
    }
    int getSize() const{
        return this->size;
    }
    Node<T>* getRoot() const{
        return root;
    }
    Node<T>* find(const T& data) const {
        if (root == nullptr) {
            return nullptr;
        }

        vector<Node<T>*> v;
        v.push_back(root);

        while (!v.empty()) {
            Node<T>* cur = v.back();
            v.pop_back();

            if (cur->data == data) {
                return cur;
            }

            for (int i = 0; i < (int)cur->children.size(); i++) {
                v.push_back(cur->children[i]);
            }
        }
        return nullptr;
    }
    bool addRoot(const T& data){
        if (root != nullptr) {
            return false;
        }else {
            Node<T> *newNode = new Node(data);
            root = newNode;
            this->size = 1;
            return true;
        }
    }
    bool addChild(const T& parentData, const T& childData) {
        if (root == nullptr) {
            return false;
        }

        vector<Node<T>*> nodes;
        nodes.push_back(root);

        while (!nodes.empty()) {
            Node<T>* cur = nodes.back();
            nodes.pop_back();
            if (cur->data == parentData) {
                Node<T>* newNode = new Node<T>(childData);
                newNode->parent = cur;
                cur->children.push_back(newNode);
                size++;
                return true;
            }
            for (int i = 0; i < (int)cur->children.size(); i++) {
                nodes.push_back(cur->children[i]);
            }
        }
        return false;
    }

    bool removeSubtree(const T& data) {
        if (root == nullptr) return false;

        Node<T>* target = find(data);
        if (target == nullptr) return false;

        if (target == root) {
            deleteSubtree(root);
            root = nullptr;
            size = 0;
            return true;
        }

        Node<T>* parentNode = target->parent;
        if (parentNode == nullptr) return false;
        int removedCount = 0;
        vector<Node<T>*> nodes;
        nodes.push_back(target);

        while (!nodes.empty()) {
            Node<T>* cur = nodes.back();
            nodes.pop_back();
            removedCount++;

            for (int i = 0; i < (int)cur->children.size(); i++) {
                nodes.push_back(cur->children[i]);
            }
        }

        for (int i = 0; i < (int)parentNode->children.size(); i++) {
            if (parentNode->children[i] == target) {
                parentNode->children.erase(parentNode->children.begin() + i);
                break;
            }
        }

        deleteSubtree(target);
        size -= removedCount;
        return true;
    }

    int numChildren(const T& data) const {
        Node<T>* target = find(data);
        if (target == nullptr) {
            return 0;
        }

        return (int)target->children.size();
    }

    int depth(const T& data) const {
        Node<T>* cur = find(data);
        if (cur == nullptr) return -1;
        int cnt = 0;
        while(cur != data){
            cnt++;
            cur = cur->parent;
        }
        return cnt;
    }

    void printPreorder() const {
        printPreorderHelper(root);
        cout << endl;
    }

    void printPostorder() const {
        printPostorderHelper(root);
        cout << endl;
    }

    void printByLevels() const {
        if (root == nullptr) {
            cout << endl;
            return;
        }

        vector<Node<T>*> nodes;
        nodes.push_back(root);

        int index = 0;
        while (index < (int)nodes.size()) {
            Node<T>* cur = nodes[index];
            index++;

            cout << cur->data << " ";

            for (int i = 0; i < (int)cur->children.size(); i++) {
                nodes.push_back(cur->children[i]);
            }
        }
        cout << endl;
    }
};
















