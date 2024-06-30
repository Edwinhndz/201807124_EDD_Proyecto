#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class BTreeNode {
public:
    string *keys;      // Array de claves
    int t;             // Grado mínimo (t define el número máximo de hijos)
    BTreeNode **C;     // Array de punteros a hijos
    int n;             // Número actual de claves
    bool leaf;         // Verdadero si el nodo es hoja

    BTreeNode(int _t, bool _leaf);

    void insertNonFull(const string &k);
    void splitChild(int i, BTreeNode *y);
    void traverse();
    BTreeNode *search(const string &k);
    void generateDOT(ofstream &outfile, int &node_count);
    void remove(const string &k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    string getPred(int idx);
    string getSucc(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);

    friend class BTree;
};

class BTree {
public:
    BTreeNode *root;
    int t;

    BTree(int _t) {
        root = nullptr;
        t = _t;
    }

    void traverse() {
        if (root != nullptr) root->traverse();
    }

    BTreeNode* search(const string &k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    void insert(const string &k);
    void remove(const string &k);
    void generateDOT();
};

BTreeNode::BTreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;

    keys = new string[2 * t - 1];
    C = new BTreeNode *[2 * t];
    n = 0;
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (leaf == false) {
            C[i]->traverse();
        }
        cout << " " << keys[i];
    }

    if (leaf == false) {
        C[i]->traverse();
    }
}

BTreeNode* BTreeNode::search(const string &k) {
    int i = 0;
    while (i < n && k > keys[i]) {
        i++;
    }

    if (keys[i] == k) {
        return this;
    }

    if (leaf == true) {
        return nullptr;
    }

    return C[i]->search(k);
}

void BTree::insert(const string &k) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) {
            BTreeNode *s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k) {
                i++;
            }
            s->C[i]->insertNonFull(k);
            root = s;
        } else {
            root->insertNonFull(k);
        }
    }
}

void BTreeNode::insertNonFull(const string &k) {
    int i = n - 1;

    if (leaf == true) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n = n + 1;
    } else {
        while (i >= 0 && keys[i] > k) {
            i--;
        }
        if (C[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, C[i + 1]);
            if (keys[i + 1] < k) {
                i++;
            }
        }
        C[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y) {
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++) {
        z->keys[j] = y->keys[j + t];
    }

    if (y->leaf == false) {
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

    n = n + 1;
}

void BTreeNode::remove(const string &k) {
    int idx = 0;
    while (idx < n && keys[idx] < k) {
        ++idx;
    }

    if (idx < n && keys[idx] == k) {
        if (leaf) {
            removeFromLeaf(idx);
        } else {
            removeFromNonLeaf(idx);
        }
    } else {
        if (leaf) {
            cout << "The key " << k << " is does not exist in the tree\n";
            return;
        }

        bool flag = (idx == n);

        if (C[idx]->n < t) {
            fill(idx);
        }

        if (flag && idx > n) {
            C[idx - 1]->remove(k);
        } else {
            C[idx]->remove(k);
        }
    }
}

void BTreeNode::removeFromLeaf(int idx) {
    for (int i = idx + 1; i < n; ++i) {
        keys[i - 1] = keys[i];
    }

    n--;
}

void BTreeNode::removeFromNonLeaf(int idx) {
    string k = keys[idx];

    if (C[idx]->n >= t) {
        string pred = getPred(idx);
        keys[idx] = pred;
        C[idx]->remove(pred);
    } else if (C[idx + 1]->n >= t) {
        string succ = getSucc(idx);
        keys[idx] = succ;
        C[idx + 1]->remove(succ);
    } else {
        merge(idx);
        C[idx]->remove(k);
    }
}

string BTreeNode::getPred(int idx) {
    BTreeNode *cur = C[idx];
    while (!cur->leaf) {
        cur = cur->C[cur->n];
    }

    return cur->keys[cur->n - 1];
}

string BTreeNode::getSucc(int idx) {
    BTreeNode *cur = C[idx + 1];
    while (!cur->leaf) {
        cur = cur->C[0];
    }

    return cur->keys[0];
}

void BTreeNode::fill(int idx) {
    if (idx != 0 && C[idx - 1]->n >= t) {
        borrowFromPrev(idx);
    } else if (idx != n && C[idx + 1]->n >= t) {
        borrowFromNext(idx);
    } else {
        if (idx != n) {
            merge(idx);
        } else {
            merge(idx - 1);
        }
    }
}

void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx - 1];

    for (int i = child->n - 1; i >= 0; --i) {
        child->keys[i + 1] = child->keys[i];
    }

    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i) {
            child->C[i + 1] = child->C[i];
        }
    }

    child->keys[0] = keys[idx - 1];

    if (!child->leaf) {
        child->C[0] = sibling->C[sibling->n];
    }

    keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx + 1];

    child->keys[child->n] = keys[idx];

    if (!child->leaf) {
        child->C[child->n + 1] = sibling->C[0];
    }

    keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; ++i) {
        sibling->keys[i - 1] = sibling->keys[i];
    }

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i) {
            sibling->C[i - 1] = sibling->C[i];
        }
    }

    child->n += 1;
    sibling->n -= 1;
}

void BTreeNode::merge(int idx) {
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx + 1];

    child->keys[t - 1] = keys[idx];

    for (int i = 0; i < sibling->n; ++i) {
        child->keys[i + t] = sibling->keys[i];
    }

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i) {
            child->C[i + t] = sibling->C[i];
        }
    }

    for (int i = idx + 1; i < n; ++i) {
        keys[i - 1] = keys[i];
    }

    for (int i = idx + 2; i <= n; ++i) {
        C[i - 1] = C[i];
    }

    child->n += sibling->n + 1;
    n--;

    delete(sibling);
}

void BTreeNode::generateDOT(ofstream &outfile, int &node_count) {
    int current_node = node_count;
    outfile << "  node" << current_node << " [label=\"";
    for (int i = 0; i < n; i++) {
        outfile << "<f" << i << "> |" << keys[i] << "| ";
    }
    outfile << "<f" << n << ">\"];\n";
    node_count++;

    for (int i = 0; i <= n; i++) {
        if (!leaf) {
            int child_node = node_count;
            C[i]->generateDOT(outfile, node_count);
            outfile << "  node" << current_node << ":f" << i << " -> node" << child_node << ";\n";
        }
    }
}

void BTree::generateDOT() {
    ofstream outfile("Btree.dot");
    if (!outfile.is_open()) {
        cerr << "Error: Could not open file " << "arbolB.dot" << endl;
        return;
    }
    outfile << "digraph BTree {\n";
    outfile << "  node [shape=record];\n";
    int node_count = 0;
    if (root != nullptr) {
        root->generateDOT(outfile, node_count);
    }
    outfile << "}\n";
    
    outfile.close();
    system("dot -Tpng Btree.dot -o Btree.png");
    system("open Btree.png");
}

void BTree::remove(const string &k) {
    if (!root) {
        cout << "The tree is empty\n";
        return;
    }

    root->remove(k);

    if (root->n == 0) {
        BTreeNode *tmp = root;
        if (root->leaf) {
            root = nullptr;
        } else {
            root = root->C[0];
        }

        delete tmp;
    }
}