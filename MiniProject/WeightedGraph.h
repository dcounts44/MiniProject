#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <string>
#include <unordered_map>

using namespace std;

class directedWeightedGraph {
private:
	struct Edge {
		string destination;
		int weight;

		Edge(const string& to, int weight);
	};

	unordered_map<string, vector<Edge>> adjList;
public:
	void addEdge(const string& from, const string& to, int weight);
	void printGraph();
	void dijkstra(const string& start,unordered_map<string, int>& distances,unordered_map<string, string>& previous);
	vector<string> getPath(const string& source,const string& destination,const unordered_map<string, string>& previous);
	void printVertices(const directedWeightedGraph& graph);
	void addVertex(const string& vertex);
};

