#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to perform BFS and return the BFS order with depths
map<char, int> bfs(const map<char, set<char>> &graph, char start) {
    map<char, int> visited_depth; // To store depth of each visited node
    queue<char> q;                // BFS queue
    q.push(start);
    visited_depth[start] = 0; // Depth of start vertex is 0

    while (!q.empty()) {
        char current = q.front();
        q.pop();

        // Visit all neighbors
        for (char neighbor : graph.at(current)) {
            if (visited_depth.find(neighbor) == visited_depth.end()) {
                visited_depth[neighbor] = visited_depth[current] + 1;
                q.push(neighbor);
            }
        }
    }

    return visited_depth;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <graph_file>" << endl;
        return 1;
    }

    string filename = argv[1];
    ifstream file(filename);

    map<char, set<char>> graph;
    string line;
    set<char> vertices;

    // Parse the graph
    while (getline(file, line)) {
        if (line.empty() || line[0] == '-') continue; // Skip empty lines or headers
        istringstream iss(line);
        char vertex;
        iss >> vertex;
        vertices.insert(vertex);

        string neighbor;
        while (iss >> neighbor) {
            if (neighbor != "0") {
                graph[vertex].insert(neighbor[0]);
            }
        }
    }

    // Output the processed graph
    cout << "Processed file " << filename << ". Found " << vertices.size()
         << " vertices: ";
    for (char v : vertices) {
        cout << v << " ";
    }
    cout << endl;

    string input;
    while (true) {
        cout << "Enter starting vertex for BFS (or 'exit' to quit): ";
        cin >> input;
        if (input == "exit") break;

        char start = input[0];
        if (graph.find(start) == graph.end()) {
            cout << "Error: Vertex " << start << " does not exist in the graph." << endl;
            continue;
        }

        // Perform BFS
        map<char, int> bfs_result = bfs(graph, start);

        // Print BFS result
        cout << "BFS starting at " << start << ": ";
        for (const auto &[vertex, depth] : bfs_result) {
            cout << vertex << ":" << depth << " ";
        }
        cout << endl;
    }

    return 0;
}
