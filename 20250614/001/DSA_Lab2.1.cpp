/* VGU CSE23 - DSA 2025 - Lab 2 */

#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Special thanks: https://www.youtube.com/watch?v=NyrHRNiRpds (src code is in Python)
// Some bits and pieces referenced from: https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/

/* *********** PART 1 START *********** */
int dijkstra(
	// I'm familiar with the concept of hashtables, and the original Python code uses a
	// dictinonary for storing the graph, which is something similar as well. 
	// After asking the internet about the C++ equivalent of this kind of data structure,
	// this is what I landed with. 
	// I hope Unordered Map is allowed... It shouldn't have any logics to handle 
	// "shortest paths" on its own.
	const unordered_map<string, vector<pair<string, int>>> graph,
	const unordered_map<string, int> cycletimes,
	const string src,
	const string dest,
	vector<string>& path2dest // Because of the way we need to format the output PBR is the least janky way to do this
) {
	unordered_map<string, int> tlist;
	unordered_map<string, string> traces;
	for (const auto& kv : graph) {
		tlist[kv.first] = INT_MAX;
	}
	tlist[src] = 0; // t for time 

	// Heap in the Python source is legit... an array 
	// Now we have a true heap here
	using vp = pair<int, string>;
	auto cmp = [](const vp& a, const vp& b) { return a.first > b.first; };
	priority_queue<vp, vector<vp>, decltype(cmp)> heap(cmp);

	heap.push({tlist[src], src});

	while (!heap.empty()) {
		auto [tv, v] = heap.top();
		// tv (or time of v) can also be achieved with tlist[v] (I'm sorry I can't think of better variable names).
		heap.pop();

		// Skip if we already found a better way to v
		if (tv > tlist[v]) continue;

		for (const auto& [vnext, tvnxt] : graph.at(v)) {
			// The "cherry on top"
			int tnow = tv + tvnxt; 
			if (vnext != dest) {
				int cvnext = cycletimes.at(vnext);
				if (tnow % cvnext != 0) {
					tnow += cvnext - (tnow % cvnext);
				}
			}

			if (tnow < tlist[vnext]) {
				tlist[vnext] = tnow;
				traces[vnext] = v;
				heap.push({tnow, vnext});
			}
		}
	}

	// Rebuild the path traversed for reporting
	string cur = dest;
	while (cur != src) {
		path2dest.push_back(cur);
		cur = traces[cur];
	}
	path2dest.push_back(src);
	reverse(path2dest.begin(), path2dest.end());

	return tlist[dest];
}
/* *********** PART 1 END *********** */

/* *********** PART 2 START *********** */
vector<string> split(string str, char delimiter) {
	// From: https://www.geeksforgeeks.org/cpp/cpp-string-to-vector-using-delimiter/
	// Using str in a string stream
	stringstream ss(str);
	vector<string> res;
	string token;
	while (getline(ss, token, delimiter)) {
		res.push_back(token);
	}
	return res;
}
string trim(const string str) {
	string strim;
	for (char c : str) {if (c != ' ') strim += c;}
	return strim;
}
/* *********** PART 2 END *********** */

/* *********** PART 3 START *********** */
int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
		return 1;
	}
	ifstream ifile(argv[1]);
	ofstream ofile(argv[2]);
	if (!ifile.is_open()) {throw runtime_error("ERROR: Failed to open input file.");}

	// For convenience, we will load the whole file into memory
	// (I don't know how to read the file based on a specific line so this is the best way around)
	vector<string> contents;
	string buffer;
	while (getline(ifile, buffer)) {
		if (!buffer.empty()) {contents.push_back(buffer);}
	}
	buffer.clear(); ifile.close();
	if (contents.empty()) {cout << "Input file is empty!\n"; return 1;}

	// Time to turn that absurd input format into something we can chew through
	// Unfortunately I can't build a function for this purpose due to the way the input is formatted
	// Step 1: How many graphs?
	int gn = stoi(contents[0]);
	// Also have something to keep track of where our "line cursor" is
	int cursor = 1; // Should be line 2
	for (int g = 0; g < gn; g++) {
		// Now for each graph: 
		unordered_map<string, vector<pair<string, int>>> graph;
		unordered_map<string, int> cycletimes;
		vector<string> path2dest;
		// Step 2: How many vertices?
		int vn = stoi(contents[cursor]); cursor++;
		// Step 3: Read stuffs
		// 3.1: Read vertices and their cycle times
		for (int loop = 0; loop < vn; loop++) {
			vector<string> buffer = split(contents[cursor], ',');
			string v = trim(buffer[0]);
			int ct = stoi(buffer[1]);
			cycletimes[v] = ct;
			cursor++;
		}
		// 3.2: Construct the graph from the edges
		while (contents[cursor].find(",") != std::string::npos) {
			vector<string> buffer = split(contents[cursor], ',');
			string v1 = trim(buffer[0]), v2 = trim(buffer[1]);
			int wt = stoi(buffer[2]); 
			// This should add it for both ways
			graph[v1].push_back({v2, wt});
			graph[v2].push_back({v1, wt});
			cursor++;
		}

		// Step 4: Now we let the core function cook and output the results
		int finalverdict = dijkstra(graph, cycletimes, "A", "G", path2dest);
		cout << finalverdict << endl; ofile << finalverdict << endl;
		for (const auto& finalpaths : path2dest) {
			cout << finalpaths << " ";
			ofile << finalpaths << " ";
		}
		
		cout << endl; ofile << endl;
	}

	ofile.close();
	return 0;
}
/* *********** PART 3 END *********** */

/* ~.~ */
