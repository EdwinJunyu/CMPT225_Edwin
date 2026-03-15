#include <iostream>
#include <string>
using namespace std;

struct ExprNode {
    string token;
    int id;
    ExprNode* left;
    ExprNode* right;

    ExprNode(const string& t, int nodeId) {
        token = t;
        id = nodeId;
        left = nullptr;
        right = nullptr;
    }
};

void deleteTree(ExprNode* p) {
    if (p == nullptr) {
        return;
    }

    deleteTree(p->left);
    deleteTree(p->right);
    delete p;
}

bool isDigitChar(char c) {
    return c >= '0' && c <= '9';
}

bool isOperatorChar(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

void skipSpaces(const string& s, int& i) {
    while (i < (int)s.size() && s[i] == ' ') {
        i++;
    }
}

/*
Grammar:
Expr := digit | '(' Expr op Expr ')'
op   := + | - | * | /
*/

ExprNode* parseExpr(const string& s, int& i, bool& ok, int& nextId) {
    skipSpaces(s, i);

    if (i >= (int)s.size()) {
        ok = false;
        return nullptr;
    }

    if (isDigitChar(s[i])) {
        string token = "";
        token += s[i];
        ExprNode* node = new ExprNode(token, nextId);
        nextId++;
        i++;
        return node;
    }

    if (s[i] == '(') {
        i++;
        skipSpaces(s, i);

        if (i < (int)s.size() && s[i] == ')') {
            ok = false;
            return nullptr;
        }

        ExprNode* leftNode = parseExpr(s, i, ok, nextId);
        if (!ok || leftNode == nullptr) {
            deleteTree(leftNode);
            ok = false;
            return nullptr;
        }

        skipSpaces(s, i);

        if (i >= (int)s.size() || !isOperatorChar(s[i])) {
            deleteTree(leftNode);
            ok = false;
            return nullptr;
        }

        string op = "";
        op += s[i];
        ExprNode* opNode = new ExprNode(op, nextId);
        nextId++;
        i++;

        ExprNode* rightNode = parseExpr(s, i, ok, nextId);
        if (!ok || rightNode == nullptr) {
            deleteTree(leftNode);
            deleteTree(rightNode);
            delete opNode;
            ok = false;
            return nullptr;
        }

        skipSpaces(s, i);

        if (i >= (int)s.size() || s[i] != ')') {
            deleteTree(leftNode);
            deleteTree(rightNode);
            delete opNode;
            ok = false;
            return nullptr;
        }

        i++;

        opNode->left = leftNode;
        opNode->right = rightNode;
        return opNode;
    }

    ok = false;
    return nullptr;
}

bool parseExpression(const string& expr, ExprNode*& root) {
    int i = 0;
    int nextId = 1;
    bool ok = true;

    ExprNode* tempRoot = parseExpr(expr, i, ok, nextId);
    skipSpaces(expr, i);

    if (!ok || tempRoot == nullptr || i != (int)expr.size()) {
        deleteTree(tempRoot);
        return false;
    }

    deleteTree(root);
    root = tempRoot;
    return true;
}

void printPreorder(ExprNode* p) {
    if (p == nullptr) {
        return;
    }

    cout << p->token << "#" << p->id << " ";
    printPreorder(p->left);
    printPreorder(p->right);
}

int evaluate(ExprNode* p) {
    if (p == nullptr) {
        return 0;
    }

    if (p->left == nullptr && p->right == nullptr) {
        return p->token[0] - '0';
    }

    int leftValue = evaluate(p->left);
    int rightValue = evaluate(p->right);

    if (p->token == "+") {
        return leftValue + rightValue;
    }
    else if (p->token == "-") {
        return leftValue - rightValue;
    }
    else if (p->token == "*") {
        return leftValue * rightValue;
    }
    else {
        return leftValue / rightValue;
    }
}

int main() {
    ExprNode* root = nullptr;
    string expr;

    cout << "Enter a fully-parenthesized infix expression: ";
    cin >> expr;

    if (!parseExpression(expr, root)) {
        cout << "Error: invalid expression." << endl;
        deleteTree(root);
        return 0;
    }

    cout << "Preorder traversal: ";
    printPreorder(root);
    cout << endl;

    cout << "Evaluated result: " << evaluate(root) << endl;

    deleteTree(root);
    return 0;
}