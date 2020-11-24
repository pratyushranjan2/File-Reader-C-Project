// Sorts the Nodes in descending order

#include "Node.h"
class NodeComparator {
    public:
        bool operator()(Node left, Node right) {
            return left.getDegree() > right.getDegree();
        }
};