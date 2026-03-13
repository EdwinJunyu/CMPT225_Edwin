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
};