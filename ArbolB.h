#include <iostream>
#include <fstream>
#include <string>
#include "NodoAB.h"


class BTree {
public:
    BTreeNode* root;
    int t;

    BTree(int _t) {
        root = nullptr;
        t = _t;
    }

    void traverse() {
        if (root != nullptr) root->traverse();
        std::cout << std::endl;
    }

    BTreeNode* search(std::string k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    void insert(NodoAA* k);
    void remove(std::string k);
    void generateDOT(const std::string& filename);
};

void BTree::insert(NodoAA* k) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);

            s->C[0] = root;
            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0]->numeroRegistro < k->numeroRegistro)
                i++;
            s->C[i]->insertNonFull(k);

            root = s;
        } else {
            root->insertNonFull(k);
        }
    }
}

void BTree::remove(std::string k) {
    if (!root) {
        std::cout << "El árbol está vacío\n";
        return;
    }

    root->remove(k);

    if (root->n == 0) {
        BTreeNode* tmp = root;
        if (root->leaf)
            root = nullptr;
        else
            root = root->C[0];

        delete tmp;
    }
}

void BTree::generateDOT(const std::string& filename) {
    std::ofstream out(filename);
    out << "digraph BTree {\n";
    out << "node [shape = record];\n";
    if (root != nullptr)
        root->generateDOT(out);
    out << "}\n";
    out.close();
    system(("dot -Tpng " + filename + " -o " + filename + ".png").c_str());
    system(("open " + filename + ".png").c_str());
}
