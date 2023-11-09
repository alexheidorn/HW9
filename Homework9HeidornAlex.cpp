/*
* Alex Heidorn
* Teammates: 
* Created: 11/6/23
* CS2 HW9
*  
*/
/* Input (in .txt file):
A Q 2
A P 3
A O 5.5
Q P 9
B N 7
C N 3
D M 5
E L 5
E K 5.7
F K 4.4
F I 5
G J 4.3
G P 0
H J 4
H I 2.8

I B 5
B H 7
A C 4
K R 9

R S 8
T S 3
T R 4
R V 7
R W 3
X Y 0
R Z 109

B Y 12
B Y 9
Y B 4
*/

/* Output:
File with graph: bipgraph1.txt
Vertices 1 and 2 are in the same set; cannot create edge.
Vertices 2 and 1 are in the same set; cannot create edge.
Vertices 4 and 16 are in the same set; cannot create edge.
Vertices 16 and 4 are in the same set; cannot create edge.
Vertices 0 and 6 are in the same set; cannot create edge.
Vertices 6 and 0 are in the same set; cannot create edge.
Vertices 11 and 17 are in the same set; cannot create edge.
Vertices 17 and 11 are in the same set; cannot create edge.
Vertices 17 and 18 are in the same set; cannot create edge.
Vertices 18 and 17 are in the same set; cannot create edge.
Vertices 17 and 20 are in the same set; cannot create edge.
Vertices 20 and 17 are in the same set; cannot create edge.
Vertices 17 and 21 are in the same set; cannot create edge.
Vertices 21 and 17 are in the same set; cannot create edge.
Vertices 17 and 24 are in the same set; cannot create edge.
Vertices 24 and 17 are in the same set; cannot create edge.
Graph:
Set 1:
A (0): 1 : 2   2 : 3   3 : 5.5
B (4): 5 : 7   13 : 5   23 : 12   23 : 9   23 : 4
C (6): 5 : 3   
D (7): 8 : 5
E (9): 10 : 5   11 : 5.7
F (12): 11 : 4.4   13 : 5
G (14): 15 : 4.3   2 : 0
H (16): 15 : 4   13 : 2.8
T (19): 18 : 3   17 : 4
X (22): 23 : 0
Set 2:
Q (1): 0 : 2
P (2): 0 : 3   14 : 0
O (3): 0 : 5.5
N (5): 4 : 7   6 : 3
M (8): 7 : 5
L (10): 9 : 5
K (11): 9 : 5.7   12 : 4.4   
I (13): 12 : 5   16 : 2.8   4 : 5
J (15): 14 : 4.3   16 : 4
R (17): 19 : 4
S (18): 19 : 3
V (20):
W (21):
Y (23): 22 : 0   4 : 12   4 : 9   4 : 4
Z (24):
PS C:\Users\alexh\CS2> 
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Edge {
private:
    int vertex1;
    int vertex2;
    double weight;
    Edge() {}
public:
    Edge(int v1, int v2, double w = 1.0) {
        vertex1 = v1;
        vertex2 = v2;
        weight = w;
    }
    int getVertex1() { return vertex1; }
    int getVertex2() { return vertex2; }
    double getWeight() { return weight; }
};

class Vertex {
private:
    static int vertexNumber;
    string name;
    int number;
    vector<Edge> edges;
    int set; // Added from Mac's code: keeps track of which set a Vertex belongs to
public:
    Vertex(int s, string n = "") { //Added: changed ctor to require set number
        number = vertexNumber++;
        name = n;
        set = s;
    }
    string getName() { return name; }
    int getNumber() { return number; }
    void addEdge(int toV, double w = 1.0);
    vector<Edge> getEdges() { return edges; }
    int getSet() { return set; }
    void showVertex();
};

class Graph {
private:
    vector <Vertex> vertexArray;
public:
    Graph() {}
    vector<Vertex> getVertices() { return vertexArray; }
    int getVertexNumber(string n);
    int insertVertexName(int s, string n) { // params need to change for edited Set ctor
        vertexArray.push_back(Vertex(s, n));
        return (vertexArray.size() - 1);
    }
    int getOrInsertVertexName(int s, string n) { // ditto
        int ni = getVertexNumber(n);
        if (ni == -1) {
            return insertVertexName(s, n);
        }
        else {
            return ni;
        }
    }

    // added a check to ensure a vertex doesn't link with a vertex in the same set
    void addEdge(int v1, int v2, double w) {
        if (vertexArray[v1].getSet() == vertexArray[v2].getSet()) {
            cerr << "Vertices " << v1 << " and " << v2 <<
            " are in the same set; cannot create edge.\n"; 
        }
        else { vertexArray[v1].addEdge(v2,w); }
    }

    bool readUndirectedGraph(string fileName) {
        ifstream inStream(fileName);
        if (inStream.is_open()) {
            while (inStream.good()) {
                string v1name;
                string v2name;
                double val;
                inStream >> v1name >> v2name >> val;
                // we assume v1, in the first column of the txt file, is apart of set1
                // we assume v2, in the second column of the text file, is apart of set2
                int v1 = getOrInsertVertexName(1, v1name);
                int v2 = getOrInsertVertexName(2, v2name);
                addEdge(v1,v2,val);
                addEdge(v2,v1,val);
            }
            return true;
        }
        else return false;
    }
    bool readDirectedGraph(string fileName) {
        ifstream inStream(fileName);
        if (inStream.is_open()) {
            while (inStream.good()) {
                string v1name;
                string v2name;
                double val;
                inStream >> v1name >> v2name >> val;
                // we assume v1, in the first column of the txt file, is apart of set1
                // we assume v2, in the second column of the text file, is apart of set2
                int v1 = getOrInsertVertexName(1, v1name);
                int v2 = getOrInsertVertexName(2, v2name);
                cout << v1 << endl;
                cout << v2 << endl;
                addEdge(v1,v2,val);
            }
            return true;
        }
        else
            return false;
    }
    void showGraph() {
        cout << "Graph:\n";
        cout << "Set 1: \n";
        for (auto v: vertexArray) {
            if (v.getSet() == 1) { v.showVertex(); }
        }
        cout << "Set 2:\n";
        for (auto v: vertexArray) {
            if (v.getSet() == 2) { v.showVertex(); }
        }
    }
};

int Vertex::vertexNumber = 0;

void Vertex::addEdge(int toV, double w) {
    edges.push_back(Edge(number,toV,w));  
}

void Vertex::showVertex() {
    cout << name << " (" << number << "): ";
    for (auto e: edges) {
        cout << e.getVertex2() << " : " << e.getWeight() << "   ";
    }
    cout << "\n";
}

int Graph::getVertexNumber(string n) {
    for (int i = 0; i < vertexArray.size(); i++) {
        if (n.compare(vertexArray[i].getName()) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    string fileName;
    cout << "File with graph: ";
    cin >> fileName;
    Graph g;
    if (g.readUndirectedGraph(fileName)) {
        g.showGraph();
    }
    else {
        cout << "Unable to open file " << fileName << "\n";
    }

    return 0;
}