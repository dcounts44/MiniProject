#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <string>
#include <unordered_map>
#include <limits>
#include "WeightedGraph.h"

using namespace std;

directedWeightedGraph::Edge::Edge(const string& to, int w) {
	destination = to;
	weight = w;
}

void directedWeightedGraph::addEdge(const string& source, const string& destination, int weight) {
    // Ensure both vertices exist
    addVertex(source);
    addVertex(destination);

    // Add the edge
    Edge edge = { destination, weight };
    adjList[source].push_back(edge);
}

void directedWeightedGraph::addVertex(const string& vertex) {
    // This creates an entry in the adjacency list if it doesn't exist
    if (adjList.find(vertex) == adjList.end()) {
        adjList[vertex] = vector<Edge>();
    }
}

//creating this function for checks
void directedWeightedGraph::printGraph() {
    for (const auto& pair : adjList) {
        cout << "From: " << pair.first;
        const auto& edges = pair.second;
        for (const auto& edge : edges) {
            cout << "\nTo: " << edge.destination << ", Distance: " << edge.weight << " ";
        }

        cout << endl;
    }
}

void directedWeightedGraph::dijkstra(const string& start, unordered_map<string, int>& flights, unordered_map<string, string>& previous) {
    //STEP 1: SET ALL INITIAL DISTANCES TO INFINITY
    for (const auto& pair : adjList) {
        flights[pair.first] = numeric_limits<int>::max();
    }

    // STEP 2: SET INPUTTED START LOCATIONS DISTANCE TO 0
    flights[start] = 0;

    // create a new mapping to help us keep track of visited vertices
    unordered_map<string, bool> visited;

    // Process all vertices
    for (size_t i = 0; i < adjList.size(); i++) {
        // Find vertex with minimum distance that hasn't been visited
        string u = "";
        int min_dist = numeric_limits<int>::max();

        for (const auto& pair : flights) {
            const string& vertex = pair.first;
            int dist = pair.second;

            if (!visited[vertex] && dist < min_dist) {
                min_dist = dist;
                u = vertex;
            }
        }

        // If we can't find a vertex, function finished
        if (u.empty()) break;

        // Mark as visited
        visited[u] = true;

        // Update distances to adjacent vertices
        for (const auto& edge : adjList[u]) {
            string v = edge.destination;
            int weight = edge.weight;

            if (!visited[v] &&
                flights[u] != numeric_limits<int>::max() &&
                flights[u] + weight < flights[v]) {
                flights[v] = flights[u] + weight;
                previous[v] = u;
            }
        }
    }
}

vector<string> directedWeightedGraph::getPath(const string& source, const string& destination, const unordered_map<string, string>& previous) {
    vector<string> path;
    string current = destination;

    // If there's no path to destination
    if (previous.find(current) == previous.end() && current != source) {
        return path;  // Return empty path
    }

    // Reconstruct path by following previous vertices
    while (current != source) {
        path.push_back(current);
        current = previous.at(current);
    }

    // Add the source
    path.push_back(source);

    // Reverse to get path from source to destination
    reverse(path.begin(), path.end());

    return path;
}

void directedWeightedGraph::printVertices(const directedWeightedGraph & graph) {
    int counter = 1;
    for (const auto& pair : adjList) {
        cout << counter++ << ". " << pair.first << endl;
    }
}