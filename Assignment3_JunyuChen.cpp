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
    void deleteSubtree(Node<T>* p);
    bool isEmpty() const{
        return root == nullptr;
    }
    int getSize() const{
        return this->size;
    }
    Node<T>* getRoot() const{
        return *root;
    }

public:
    MyTree();
    ~MyTree();
};