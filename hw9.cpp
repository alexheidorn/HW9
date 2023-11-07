/*
* Alex Heidorn
* Created: 11/6/23
* CS2 HW9
*  
*/

#include <iostream>
#include <vector>
#include <limits>
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
        static int set; //keeps track of which set a Vertex belongs to
    public:
        Vertex(string n = "", int s) { //changed ctor to require set number
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
        int insertVertexName(string n);
        int getOrInsertVertexName(string n);
        void addEdge(int v1, int v2, double w);
        bool readUndirectedGraph(string fileName);
        bool readDirectedGraph(string fileName);
        void showGraph();
    };

    int Vertex::vertexNumber = 0;

    // ensure a vertex doesn't link with a vertex in the same set
    void Vertex::addEdge(int toV, double w) {
        if (set == ){ //having an issue doing this...
            cerr << "Vertices are in the same set; cannot create edge.\n";
        }
        else{ edges.push_back(Edge(number,toV,w)); }   
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

    int Graph::insertVertexName(string n) {
        vertexArray.push_back(Vertex(n));
        return (vertexArray.size() - 1);
    }

    int Graph::getOrInsertVertexName(string n) {
        int ni = getVertexNumber(n);
        if (ni == -1) {
            return insertVertexName(n);
        }
        else {
            return ni;
        }
    }

    void Graph::addEdge(int v1, int v2, double w) {
        vertexArray[v1].addEdge(v2,w);
    }

    bool Graph::readUndirectedGraph(string fileName) {
        ifstream inStream(fileName);
        if (inStream.is_open()) {
            while (inStream.good()) {
                string v1name;
                string v2name;
                double val;
                inStream >> v1name >> v2name >> val;
                int v1 = getOrInsertVertexName(v1name);
                int v2 = getOrInsertVertexName(v2name);
                addEdge(v1,v2,val);
                addEdge(v2,v1,val);
            }
            return true;
        }
        else
            return false;
    }

    bool Graph::readDirectedGraph(string fileName) {
        ifstream inStream(fileName);
        if (inStream.is_open()) {
            while (inStream.good()) {
                string v1name;
                string v2name;
                double val;
                inStream >> v1name >> v2name >> val;
                int v1 = getOrInsertVertexName(v1name);
                int v2 = getOrInsertVertexName(v2name);
                cout << v1 << endl;
                cout << v2 << endl;
                addEdge(v1,v2,val);
            }
            return true;
        }
        else
            return false;
    }

    void Graph::showGraph() {
        cout << "Graph:\n";
        for (auto v: vertexArray) {
            v.showVertex();
        }
    }

//vertices arent allowed to have edges within their own graphs...

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