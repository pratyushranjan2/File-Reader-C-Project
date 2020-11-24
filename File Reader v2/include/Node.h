#ifndef NODE_H_
#define NODE_H_
#include <string>
#include <map>
#include <vector>

using namespace std;

class Node {
    public:
        int index;
        string label;
        double degree;
        map<int,double> edges;

    public:
        Node();
        Node(int _index, string _label);
        Node(const Node &node);
        ~Node(); 

    public:
        double getDegree();
        int getIndex();
        string getLabel();
        map<int,double> getEdges();
        
        void setDegree(double d);
        void setIndex(int i);
        void setLabel(string _label);
        
        void addEdge(int endNodeIndex, double weight);
        void filterEdges(int threshold_index);
        void reIndex(map<int,int> newIndices);   
};

#endif