#ifndef KDTREE_H
#define KDTREE_H

#include "Photon.h"
#include "Node.h"
#include <iostream>

class Kdtree {
    public:
        Kdtree() { root = new Node(1); }

        void setSize(int size);
        void generateKdtreeAtRoot(Photon* photons[]);
        Node* generateKdtree(Photon* photons[], int depth, int size);
        void shellSort(Photon* photons[], int size, int axis);

        Node* root;
};

#endif // KDTREE_H_INCLUDED
