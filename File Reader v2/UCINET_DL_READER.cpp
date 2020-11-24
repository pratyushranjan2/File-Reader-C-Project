#include "include/UCINET_DL_READER.h" 

UCINET_DL_READER::UCINET_DL_READER(string _fileName): base(), fileName(_fileName) {}

UCINET_DL_READER::UCINET_DL_READER(const UCINET_DL_READER &udr): fileName(udr.fileName), n(udr.n), labels(udr.labels), nodes(udr.nodes) {}

UCINET_DL_READER::~UCINET_DL_READER() {
    labels.clear();
    labels.shrink_to_fit();
    nodes.clear();
    nodes.shrink_to_fit();
}

void UCINET_DL_READER::reIndexNodes() {
    map<int,int> newIndices;
    
    for (int i=0;i<nodes.size();i++) {
        newIndices.insert(pair<int,int>(nodes[i].getIndex(),i+1)); // [old index -> new index]
    }

    for (int i=0;i<nodes.size();i++) {
        nodes[i].reIndex(newIndices);
    }
}

void UCINET_DL_READER::filterNodes(int threshold_index) {
    for (int i=0;i<threshold_index;i++) {
        nodes[i].filterEdges(threshold_index);
    }
}

void UCINET_DL_READER::storeLabels(vector<string> rawData) {
    for (int i=0;i<rawData.size();i++) {
        string label = rawData[i];
        label = StringUtility::removeFromString(",",label);
        label = StringUtility::trim(label);
        labels.push_back(label);
    }
}

void UCINET_DL_READER::initializeNodes() {
    for (int i=0;i<labels.size();i++) {
        nodes.push_back(Node(i+1,labels[i]));
    }
}

void UCINET_DL_READER::readAndStoreData() {
    vector<string> parts;
    fstream file;
    file.open(fileName,ios::in);

    if (file.is_open()) {
        string line;
        
        while (getline(file,line)) {
            parts = StringUtility::splitBySpace(line);

            if (parts[0] == "DL") {
                n = stoi(parts[1].substr(2,1));
            }
            else if (parts[0] == "labels:") {
                getline(file,line);
                parts = StringUtility::splitBySpace(line);
                storeLabels(parts);
                initializeNodes();
            }
                
            else if (parts[0] == "data:") {
                for (int i=0;i<n;i++) {
                    getline(file,line);
                    parts = StringUtility::splitBySpace(line);
                    int nodeIndex = stoi(parts[0]);
                    int edgeNodeIndex = stoi(parts[1]);
                    double weight = stod(parts[2]);
                    nodes[nodeIndex-1].addEdge(edgeNodeIndex, weight);
                    nodes[edgeNodeIndex-1].setDegree(nodes[edgeNodeIndex-1].getDegree()+weight);
                }
            }
        }
        file.close();
    }
}

void UCINET_DL_READER::writeback() {
    fstream file;
    file.open("output_files/task_5.txt",ios::out);
    if (file.is_open()) {
        file << "DL n=" << n/2 << "\nformat = edgelist1\nlabels:\n";
        for (int i=0;i<(n/2)-1;i++) {
            file << nodes[i].getLabel() << ", ";
        }
        file << nodes[(n/2)-1].getLabel() << "\ndata:\n";

        for (int i=0;i<n/2;i++) {
            map<int,double> edges = nodes[i].getEdges();
            for (const auto& edge: edges) {
                file << nodes[i].getIndex() << " " << edge.first << " " << edge.second << "\n";
            }
        }
        file.close();
    }
}

void UCINET_DL_READER::generateOutputFile() {
    readAndStoreData();
    sort(nodes.begin(),nodes.end(), NodeComparator()); // sort the nodes a/q degree
    reIndexNodes();
    filterNodes(nodes.size()/2);
    writeback(); // write to the output file
}


// Base class methods
void UCINET_DL_READER::fileRead() {
    readAndStoreData();
}

void UCINET_DL_READER::execute() {
    sort(nodes.begin(),nodes.end(), NodeComparator()); // sort the nodes a/q degree
    reIndexNodes();
    filterNodes(nodes.size()/2);
}

void UCINET_DL_READER::fileWrite() {
    writeback();
}

void UCINET_DL_READER::testing() {
    cout << "n = " << n << endl;
    for (int i=0;i<labels.size();i++) {
        cout << labels[i] << " ";
    }
    cout << endl;

    for (int i=0;i<nodes.size();i++) {
        Node node = nodes[i];
        cout << "index: " << node.index << "  label: " << node.label << "  degree: " << node.degree << endl << endl;
        cout << "Edges: " << endl;
        for (const auto& x: node.edges) {
            cout << x.first << " " << nodes[x.first-1].label << " " << x.second << endl;
        }
        cout << endl;
    }

    sort(nodes.begin(), nodes.end(),NodeComparator());
    cout << "After Sorting - " << endl;
    for (int i=0;i<nodes.size();i++) {
        Node node = nodes[i];
        cout << "index: " << node.index << "  label: " << node.label << "  degree: " << node.degree << endl << endl;
        cout << "Edges: " << endl;
        for (const auto& x: node.edges) {
            cout << x.first << " " << nodes[x.first-1].label << " " << x.second << endl;
        }
        cout << endl;
    }
}