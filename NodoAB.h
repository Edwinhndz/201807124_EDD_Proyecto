#include <iostream>
#include <fstream>
#include <string>
#include "NodoA.h"

class BTreeNode {
public:
    NodoAA** keys;
    int t;
    BTreeNode** C;
    int n;
    bool leaf;

    BTreeNode(int _t, bool _leaf);

    void insertNonFull(NodoAA* k);
    void splitChild(int i, BTreeNode* y);
    void traverse();

    BTreeNode* search(std::string k);
    int findKey(std::string k);

    void remove(std::string k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    std::string getPred(int idx);
    std::string getSucc(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
    void generateDOT(std::ofstream& out);
};

// Constructor
BTreeNode::BTreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;
    keys = new NodoAA*[2*t-1];
    C = new BTreeNode*[2*t];
    n = 0;
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf)
            C[i]->traverse();
        std::cout << " " << keys[i]->numeroRegistro;
    }
    if (!leaf)
        C[i]->traverse();
}

BTreeNode* BTreeNode::search(std::string k) {
    int i = 0;
    while (i < n && keys[i]->numeroRegistro < k)
        i++;
    if (i < n && keys[i]->numeroRegistro == k)
        return this;
    if (leaf)
        return nullptr;
    return C[i]->search(k);
}

int BTreeNode::findKey(std::string k) {
    int idx = 0;
    while (idx < n && keys[idx]->numeroRegistro < k)
        idx++;
    return idx;
}

void BTreeNode::remove(std::string k) {
    int idx = findKey(k);

    if (idx < n && keys[idx]->numeroRegistro == k) {
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    } else {
        if (leaf) {
            std::cout << "La clave " << k << " no existe en el árbol.\n";
            return;
        }

        bool flag = (idx == n);

        if (C[idx]->n < t)
            fill(idx);

        if (flag && idx > n)
            C[idx - 1]->remove(k);
        else
            C[idx]->remove(k);
    }
}

void BTreeNode::removeFromLeaf(int idx) {
    for (int i = idx + 1; i < n; i++)
        keys[i - 1] = keys[i];
    n--;
}

void BTreeNode::removeFromNonLeaf(int idx) {
    std::string k = keys[idx]->numeroRegistro;

    if (C[idx]->n >= t) {
        std::string pred = getPred(idx);
        keys[idx]->numeroRegistro = pred;
        C[idx]->remove(pred);
    } else if (C[idx + 1]->n >= t) {
        std::string succ = getSucc(idx);
        keys[idx]->numeroRegistro = succ;
        C[idx + 1]->remove(succ);
    } else {
        merge(idx);
        C[idx]->remove(k);
    }
}

std::string BTreeNode::getPred(int idx) {
    BTreeNode* cur = C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n - 1];
    return cur->keys[cur->n - 1]->numeroRegistro;
}

std::string BTreeNode::getSucc(int idx) {
    BTreeNode* cur = C[idx + 1];
    while (!cur->leaf)
        cur = cur->C[0];
    return cur->keys[0]->numeroRegistro;
}

void BTreeNode::fill(int idx) {
    if (idx != 0 && C[idx - 1]->n >= t)
        borrowFromPrev(idx);
    else if (idx != n && C[idx + 1]->n >= t)
        borrowFromNext(idx);
    else {
        if (idx != n)
            merge(idx);
        else
            merge(idx - 1);
    }
}

void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx - 1];

    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];
    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i)
            child->C[i + 1] = child->C[i];
    }

    child->keys[0] = keys[idx - 1];
    if (!leaf)
        child->C[0] = sibling->C[sibling->n];

    keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx + 1];

    child->keys[child->n] = keys[idx];
    if (!child->leaf)
        child->C[child->n + 1] = sibling->C[0];

    keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->C[i - 1] = sibling->C[i];
    }

    child->n += 1;
    sibling->n -= 1;
}

void BTreeNode::merge(int idx) {
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx + 1];
    child->keys[t - 1] = keys[idx];

    for (int i = 0; i < sibling->n; ++i)
        child->keys[i + t] = sibling->keys[i];
    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->C[i + t] = sibling->C[i];
    }

    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];
    for (int i = idx + 2; i <= n; ++i)
        C[i - 1] = C[i];

    child->n += sibling->n + 1;
    n--;

    delete sibling;
}

void BTreeNode::generateDOT(std::ofstream& out) {
    out << "node" << this << " [label=\"";
    for (int i = 0; i < n; i++) {
        out << "<f" << i << "> |" << keys[i]->numeroRegistro << "|";
    }
    out << "<f" << n << ">\"];\n";

    if (!leaf) {
        for (int i = 0; i <= n; i++) {
            out << "\"node" << this << "\":f" << i << " -> \"node" << C[i] << "\";\n";
            C[i]->generateDOT(out);
        }
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++) {
        z->keys[j] = y->keys[j + t];
    }

    if (!y->leaf) {
        for (int j = 0; j < t; j++) {
            z->C[j] = y->C[j + t];
        }
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--) {
        C[j + 1] = C[j];
    }

    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--) {
        keys[j + 1] = keys[j];
    }

    keys[i] = y->keys[t - 1];

    n++;
}



void BTreeNode::insertNonFull(NodoAA* k) {
    int i = n - 1;

    if (leaf) {
        while (i >= 0 && keys[i]->numeroRegistro > k->numeroRegistro) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n++;
    } else {
        while (i >= 0 && keys[i]->numeroRegistro > k->numeroRegistro) {
            i--;
        }

        if (C[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, C[i + 1]);

            if (keys[i + 1]->numeroRegistro < k->numeroRegistro) {
                i++;
            }
        }
        C[i + 1]->insertNonFull(k);
    }
}
