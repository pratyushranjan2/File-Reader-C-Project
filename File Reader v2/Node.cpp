#include "include/Node.h"

Node::Node() {}

Node::Node(int _index, string _label): index(_index), label(_label), degree(0.0) {}

Node::Node(const Node &node): index(node.index), label(node.label), degree(node.degree), edges(node.edges) {}

Node::~Node() {
    edges.clear();
}

void Node::addEdge(int endNodeIndex, double weight) {
    edges.insert(pair<int,double>(endNodeIndex,weight));
    degree += weight;
}

double Node::getDegree() {
    return degree;
}

int Node::getIndex() {
    return index;
}

string Node::getLabel() {
    return label;
}

map<int,double> Node::getEdges() {
    return edges;
}

void Node::setDegree(double d) {
    degree = d;
}

void Node::setIndex(int i) {
    index = i;
}

void Node::setLabel(string _label) {
    label = _label;
}

void Node::filterEdges(int threshold_index) {
    for (const auto& edge: edges) {
        int endNodeIndex = edge.first;
        if (endNodeIndex > threshold_index) {
            edges.erase(endNodeIndex);
        }
    }
}

void Node::reIndex(map<int,int> newIndices) {
    setIndex(newIndices[index]);

    for (const auto& edge: edges) {
        int oldIndex = edge.first; // old index of end node of this edge
        double weight = edge.second;
        int newIndex = newIndices[oldIndex]; // new index to be set of the end node
        edges.erase(oldIndex);
        edges.insert(pair<int,double>(newIndex,weight));
    }
}