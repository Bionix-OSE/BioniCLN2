## Reference list 
- https://www.youtube.com/watch?v=NyrHRNiRpds
- https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
- https://www.geeksforgeeks.org/cpp/unordered_map-in-cpp-stl/
- https://www.geeksforgeeks.org/cpp/getline-string-c/
- https://www.geeksforgeeks.org/cpp/convert-string-to-int-in-cpp/
- https://www.geeksforgeeks.org/cpp/copy-file-to-vector-in-cpp-stl/
- https://cplusplus.com/forum/beginner/82290/ (buffer.clear())
- 

## Draft codes and notes
```C++
/* - About the time thingy: (this is the cherry on top of the dijkstra) [DONE]
  + Each vertex has an additional value to it: Cycle time (CT)
  + When you reach a v there are 2 possibilities: 
	a. If your current total time (weight) is divisible by the v's CT, you may continue
	b. If not, you have to add to the total time whatever it takes for it to be divisible, then you can continue
- Input file parser: [DONE]
  + Progress based on line number
- Dijkstra core: [DONE]
  + Somehow make it report back the nodes traversed before getting to dest (maybe a vector recording the path?)
*/

// Draft stuffs
int main() {
	unordered_map<string, vector<pair<string, int>>> graph = {
		// This is case 1 in the pdf
		{"A", {{"B", 4},{"C", 2}}},
		{"B", {{"D", 5},{"A", 4}}},
		{"C", {{"D", 8},{"E", 10},{"A", 2}}},
		{"D", {{"F", 6},{"B", 5},{"C", 8}}},
		{"E", {{"F", 3},{"C", 10}}},
		{"F", {{"G", 1},{"E", 3},{"D", 6}}},
		{"G", {{"F", 1}}}
	};
	unordered_map<string, int> cycletimes = {
		{"A", 2},
		{"B", 3},
		{"C", 5},
		{"D", 4},
		{"E", 6},
		{"F", 2},
		{"G", 1}
	};

	cout << dijkstra(graph, cycletimes, "A", "G") << endl;
	return 0;
}

pair<unordered_map<string, vector<pair<string, int>>>, 
	unordered_map<string, int>> 
	inputparser(const string& ifilepath) {
	unordered_map<string, vector<pair<string, int>>> graph;
	unordered_map<string, int> cycletimes;
	
	ifstream ifile(ifilepath);
	if (!ifile.is_open()) {throw runtime_error("Failed to open input file.");}

	return {graph, cycletimes};
}

// Test
for (int i = 0; i < contents.size(); i++) {
	cout << contents[i] << "\n";
}

	// Before we continue let's first verify the graph is loaded correctly //
		for (auto& kv : graph) {
			cout << kv.first << ": ";
			for (auto& edge : kv.second) {
				cout << "(" << edge.first << ", " << edge.second << ") ";
			}
			cout << "\n";
		}
		cout << "\n";
```
