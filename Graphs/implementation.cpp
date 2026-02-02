#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Graph {
    public:
        int V, E;

        // Adjacency matrix
        vector<vector<int>> adjMatrix;

        // Adjacency list
        vector<vector<int>> adjList;

        // Constructor for undirected graph
        Graph(int vertices, int edges) {
            V = vertices;
            E = edges;

            // Approach 1:- Using Adjacency Matrix
            adjMatrix.assign(V + 1, vector<int>(V + 1, 0));

            // Approach 2 :- Using Adjacency List
            // store the connected nodes for each node
            adjList.assign(V + 1, vector<int>());
        }

        // Build graph using adjacency matrix
        void buildAdjMatrix() {
            for (int i = 0; i < E; i++) {
                int u, v;
                cin >> u >> v;

                adjMatrix[u][v] = 1;
                adjMatrix[v][u] = 1;   // undirected
            }
            // TC: O(E) for construction, O(1) for edge lookup
            // SC: O(V²)
        }

        // Build graph using adjacency list
        void buildAdjList() {
            for (int i = 0; i < E; i++) {
                int u, v;
                cin >> u >> v;

                adjList[u].push_back(v);
                adjList[v].push_back(u);  // undirected
            }
            // TC: O(E) for construction, O(degree(u)) for checking edge u-v
            // SC: O(V + 2E) - V vectors + 2E total entries (each edge stored twice), in Direct SC :- O(V + E)

            // Use adj(V + 1) → if you’ll store neighbors (list style).
            // Use adj(V + 1, vector<int>(V + 1, 0)) → if you’ll check edge existence quickly (matrix style).
        }
};



class GraphTraversal {
    
    public:
        // Adjacency list
        vector<vector<int>> adjList;

        // DFS helper function
        void DFS(unordered_map<int, vector<int>> &adjList, int u, unordered_map<int, bool> &visited, vector<int> &result) {
            // Mark the current node as visited
            visited[u] = true;

            // Add the node to the DFS traversal result
            result.push_back(u);

            // Recur for all neighbors
            for (int v : adjList[u]) {
                if (!visited[v]) {
                    DFS(adjList, v, visited, result);
                }
            }
        }


        // Function to perform DFS traversal of the graph , TC :- O(V+E)
        vector<int> dfsTraversal(unordered_map<int, vector<int>> &adjList, int startNode) {
            vector<int> result;
            unordered_map<int, bool> visited; // Track visited nodes

            DFS(adjList, startNode, visited, result);

            return result;
        }


        // BFS traversal using adjacency list , TC :- O(V+E)
        vector<int> BFS(vector<vector<int>> &adjList, int startNode) {
            vector<int> result;
            vector<bool> visited(adjList.size(), false);
            queue<int> q;

            // Start BFS from startNode
            visited[startNode] = true;
            q.push(startNode);

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                // Add the node to the BFS traversal result
                result.push_back(u);

                // Visit all unvisited neighbors
                for (int v : adjList[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }

            return result;
        }
        /*
            Whenever the Question is about the Shortest path ---> always think of BFS
        */
};



int main(){

    // Graph Implementation
    int V, E;
    cin >> V >> E;

    Graph g(V, E);

    // Degree of a graph = 2 * Total number of Edges

    // Build adjacency matrix
    // g.buildAdjMatrix();

    // Build adjacency list
    g.buildAdjList();


    
    // DFS Traversal
    // Example usage
    unordered_map<int, vector<int>> adjList;
    adjList[1] = {2, 3};
    adjList[2] = {1, 4};
    adjList[3] = {1};
    adjList[4] = {2};
    
    GraphTraversal graph;
    vector<int> traversal = graph.dfsTraversal(adjList, 1);
    
    cout << "DFS Traversal: ";
    for (int node : traversal) {
        cout << node << " ";
    }
    cout << endl;

    
    // BFS traversal starting from node 1 using graph’s adjList
    vector<int> bfsTraversal = graph.BFS(g.adjList, 1);
    cout << "BFS Traversal: ";
    for (int node : bfsTraversal) {
        cout << node << " ";
    }
    cout << endl;

   return 0;
}





