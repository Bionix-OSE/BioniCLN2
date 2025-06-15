/* VGU CSE23 - DSA 2025 - Lab 2 (SCRAPPED CODE) */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// This code was taken directly from https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
// Ultimately I could not comprehend this version to modify the algorithm, so it was scrapped in favor of 2.1

// Function to construct adjacency 
vector<vector<vector<int>>> constructAdj(vector<vector<int>> &edges, int V) {
	// adj[u] = list of {v, wt}
	// Where: u = current vertex; v = neighboring vertexes; wt = weight of each said vertex 
	vector<vector<vector<int>>> adj(V); 

	for (const auto &edge : edges) {
		int u = edge[0];
		int v = edge[1];
		int wt = edge[2];
		adj[u].push_back({v, wt});
		adj[v].push_back({u, wt}); 
	}

	return adj;
}
// Returns shortest distances from src to everything
// (Assuming cycletimes is a vector we read from the first n+2 lines, go implement that later)
vector<int> dijkstra(int V, vector<vector<int>> &edges, int src, vector<int> &cycletimes) {
	
	// Create adjacency list
	vector<vector<vector<int>>> adj = constructAdj(edges, V); 

	// Create a priority queue to store vertices that
	// are being preprocessed.
	priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

	// Create a vector for distances and initialize all
	// distances as infinite
	vector<int> dist(V, INT_MAX);

	// Insert source itself in priority queue and initialize
	// its distance as 0 + its cycletime.
	pq.push({0 + cycletimes[src], src});
	dist[src] = 0 + cycletimes[src];

	// Looping till priority queue becomes empty
	while (!pq.empty()) {
		
		// The first vertex in pair is the minimum distance
		// vertex, extract it from priority queue.
		int u = pq.top()[1];
		pq.pop();
 
		// Get all adjacent of u.
		for (auto x : adj[u]) {
			
			// Get vertex label and weight of current
			// adjacent of u.
			int v = x[0], weight = x[1];
			// as well as its cycle time
			int vtime = cycletimes[v];

			// The cherry on top
			// ...I give up. This code makes things so hard to understand.

			// If there is shorter path to v through u.
			if (dist[v] > dist[u] + weight)
			{
				// Updating distance of v
				dist[v] = dist[u] + weight;
				pq.push({dist[v], v});
			}
		}
	}

	return dist;
}


// Test code from the page
/*
int main(){
	int V = 5;
	int src = 0;
	
	// edge list format: {u, v, weight}
	vector<vector<int>> edges = {{0, 1, 4}, {0, 2, 8}, {1, 4, 6}, {2, 3, 2}, {3, 4, 10}};
	
	vector<int> result = dijkstra(V, edges, src);
	
	// Print shortest distances in one line
	for (int dist : result)
		cout << dist << " ";
	
	return 0;
}
*/
