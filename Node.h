#ifndef NODE_H
#define NODE_H

class Node {
    public:
        Node() {}
        Node(int d) : depth(d) {}
        Node(Photon* p1, int d) : p(p1), depth(d) {}

        Node* left;
        Node* right;
        int depth, pointsetSize;
        Photon* p;
};

#endif // NODE_H_INCLUDED
