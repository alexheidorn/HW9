/*
* Alex Heidorn
* Created: 11/6/23
* CS2 HW9
*  
*/

#include <iostream>
#include <vector>
#include <limits>
#include "Graph.h"
using namespace std;

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