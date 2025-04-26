// MiniProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <string>
#include <unordered_map>
#include "WeightedGraph.h"


using namespace std;

int main()
{
    directedWeightedGraph graph;

    //adding all our vertexes
    graph.addVertex("KC");
    graph.addVertex("CANCUN");
    graph.addVertex("JFK");
    graph.addVertex("LAX");
    graph.addVertex("SFO");
    graph.addVertex("CDG");
    graph.addVertex("FRA");
    graph.addVertex("ICN");
    graph.addVertex("IST");
    graph.addVertex("DXB");
    graph.addVertex("BKK");
    graph.addVertex("HKG");

    // Add edges from KC
    graph.addEdge("KC", "CANCUN", 1341);
    graph.addEdge("KC", "JFK", 1109);
    graph.addEdge("KC", "LAX", 1363);


    // Add edges from CANCUN
    graph.addEdge("CANCUN", "SFO", 3270);
    graph.addEdge("CANCUN", "CDG", 5103);
    graph.addEdge("CANCUN", "FRA", 5343);

    // Add edges from LAX
    graph.addEdge("LAX", "SFO", 337);
    graph.addEdge("LAX", "CDG", 5103);
    graph.addEdge("LAX", "FRA", 5788);

    // Add edges from JFK
    graph.addEdge("JFK", "FRA", 3867);
    graph.addEdge("JFK", "CDG", 3624);
    graph.addEdge("JFK", "SFO", 2586);

    // Add edges from SFO
    graph.addEdge("SFO", "ICN", 5645);
    graph.addEdge("SFO", "IST", 6705);
    graph.addEdge("SFO", "DXB", 8103);

    // Add edges from CDG
    graph.addEdge("CDG", "IST", 1964);
    graph.addEdge("CDG", "ICN", 5546);
    graph.addEdge("CDG", "DXB", 3253);

    // Add edges from FRA
    graph.addEdge("FRA", "DXB", 3013);
    graph.addEdge("FRA", "IST", 1145);
    graph.addEdge("FRA", "ICN", 5312);

    // Add edges from ICN
    graph.addEdge("ICN", "BKK", 2276);
    graph.addEdge("ICN", "HKG", 1283);

    // Add edges from IST
    graph.addEdge("IST", "HKG", 4983);
    graph.addEdge("IST", "BKK", 4672);

    // Add edges from DXB 
    graph.addEdge("DXB", "HKG", 3684);
    graph.addEdge("DXB", "BKK", 3050);

    

    string source = "";
    cout << "Please select your outgoing location from available airports: " << endl;

    graph.printVertices(graph);
    cout << "\nPlease select from provided airport list: ";
    cin >> source;
    cout << endl;

    unordered_map<string, int> flights;
    unordered_map<string, string> previous;

    graph.dijkstra(source, flights, previous);

    cout << "Shortest distances from " << source << ":" << endl;
    for (const auto& pair : flights) {
        if (pair.first == source) continue;
        if (pair.second == numeric_limits<int>::max())
            cout << source << " -> " << pair.first << ": No path" << endl;
        else
            cout << source << " -> " << pair.first << ": " << pair.second << endl;
    }
    cout << endl;

    // Print shortest paths
    cout << "Shortest paths from " << source << ":" << endl;
    for (const auto& pair : flights) {
        if (pair.first == source) 
            continue; // Skip source vertex

        vector<string> path = graph.getPath(source, pair.first, previous);

        cout << source << " to " << pair.first << ": ";
        if (path.empty()) {
            cout << "No path exists";
        }
        else {
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i];
                if (i < path.size() - 1) 
                    cout << " -> ";
            }
        }
        cout << endl;
    }
}

