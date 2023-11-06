//
// Created by Richard Maclin on 10/23/23.
//

#ifndef DJIKSTRAS_GRAPH_H
#define DJIKSTRAS_GRAPH_H
#include <string>
#include <vector>

namespace std {
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
    public:
        Vertex(string n = "") {
            number = vertexNumber++;
            name = n;
        }
        string getName() { return name; }
        int getNumber() { return number; }
        void addEdge(int toV, double w = 1.0);
        vector<Edge> getEdges() { return edges; }
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
}


#endif //DJIKSTRAS_GRAPH_H
