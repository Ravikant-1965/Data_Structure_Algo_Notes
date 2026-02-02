#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>

using namespace std;

/*
Question 1 :- Cycle detection in Undirected Graph using DFS , TC :- O(V+E)
Why only marking and seeing the visited nodes will not work
Suppose the graph is.

(1) ---------- (2)

then from 1 -> 2, 2 -> 1
start traversing, 1 - visted, 1 --> 2, 2 visited, now from 2 we can go to (1).                                 
(1) is already visited. Does this mean that there is a cycle ?                                                 
So we have to also keep track of the parent and make sure that the neighbour node is not the previuos node (parent node) (from
where we came from.)
*/

class Solution1 {
public:
    bool dfs(int u, int parent, vector<vector<int>> adj, vector<bool> &visited) {
        visited[u] = true;

        for (int v : adj[u]) {
            if (v == parent) continue; // skip the edge we came from

            if (visited[v]) return true; // found a back edge → cycle
            // If a visited neighbor is not the parent → it means there’s another path back to that vertex → cycle exists.

            if (dfs(v, u, adj, visited)) return true;
            // If the recursive call returns true, it means a cycle was
            // found deeper in the graph — so we immediately propagate that true upward.
        }
        return false;
    }

    bool isCycle(int V, vector<vector<int>>& edges) {
        // first build an adjacency list from the given edge list before doing DFS :
        vector<vector<int>> adj(V);
        for (auto &e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // To track visited nodes
        vector<bool> visited(V, false);

        // Check each component (if there are more than 1 component)
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (dfs(i, -1, adj, visited)) return true;   // sabse pehla node ka parent -1 maan liya
            }
        }

        return false;
    }
};


// Question 2 :- Cycle detection in Undirected Graph using BFS, TC :- O(V+E)
// Using Queue of Pair {node, parent_of_node}
class Solution2 {
    public:
    bool isCycleBFS(vector<int> adj[], int V, int start, vector<bool>& visited) {
        queue<pair<int, int>> que;
        // sabse pehla node push karr do
        que.push({start, -1});
        visited[start] = true;

        while(!que.empty()) {
            int source   = que.front().first;
            int parent = que.front().second;
            que.pop();

            for (auto x : adj[source]) {
                if(visited[x] == false) {  // agr visted nahi hai toh
                    que.push({x, source});
                    visited[x] = true;
                }
                else if(x != parent){  // if the node is already visited, and it is not the parent node, then cycle is present
                	return true;  // found a back edge
                }
            }
        }

        return false;
    }

    // Function to detect cycle in an undirected graph.
    bool isCycle(int V, vector<int> adj[]) {

        vector<bool> visited(V, false);

        for(int i = 0; i<V; i++) {
            if(!visited[i] && isCycleBFS(adj, V, i, visited)) {
                return true;
            }
		}

        return false;

    }
};



// Question 3 :- Cycle detection in Directed Graph using DFS
/*
(0)--------> (1) <-------- (2)
see this to verify why, the previous approach would not work in Directed graph

Approach :- Agr cuurent recursion me koi aisa node mill gaya jo ki pehle se visited hai, so cycle is there.
*/
class Solution3 {
    public:
      bool isCycleDFS(unordered_map<int, vector<int>> &adj, int u, vector<bool> &visited, vector<bool> &inRecursion) {
          visited[u] = true;
          inRecursion[u] = true;
  
          for (auto &v : adj[u]) {
              // if not visited, do DFS
              if (!visited[v] && isCycleDFS(adj, v, visited, inRecursion)) {
                  return true;
              }
              // if visited and is in the recursion stack.->this means cycle
              else if (inRecursion[v]) {
                  return true;
              }
          }
  
          // backtrack
          inRecursion[u] = false;
          return false;
      }
  
      bool isCyclic(int V, vector<vector<int>> &edges) {
          unordered_map<int, vector<int>> adj;
          // first build the adjacency matrix from the edges
          for (auto &edge : edges) {
              int u = edge[0];
              int v = edge[1];
              adj[u].push_back(v); // directed edge
          }
  
          vector<bool> visited(V, false);
          vector<bool> inRecursion(V, false);
  
          for (int i = 0; i < V; i++) {
              if (!visited[i] && isCycleDFS(adj, i, visited, inRecursion)) {
                  return true;
              }
          }
  
          return false;
      }
};
  
/*
Question 4 :- Topological sorting of a graph
Definition :- A topological sort of a Directed Acyclic Graph (DAG) is a linear ordering of its vertices such that:

For every directed edge u → v, vertex u comes before vertex v in the ordering.

Example :- Suppose you have this directed graph:

5 → 0 ← 4
↓       ↑
2 → 3 → 1

One valid topological order is :- 5, 2, 3, 1, 4, 0

Here, every edge points forward in the order — never backward.

Intuitive Meaning :-

        Think of topological sorting like scheduling tasks with dependencies:
        Each node = a task
        Each edge u → v = “task u must be done before task v”
        So, a topological order is a sequence you can follow to complete all tasks without breaking dependencies.

🔹 When Is It Possible?

✅ Only possible for a DAG (Directed Acyclic Graph)
❌ If the graph has a cycle, there’s no valid topological order (because some tasks depend on each other in a loop).

   A ───▶ B
   ▲     │
   └─────┘

   according to edge 1 it says that 'A' should come first, but according to edge 2 it says 'B' should come first
*/
class Solution4 {
    public:
      void dfs(unordered_map<int, vector<int>> &adj, int u, vector<bool> &visited, stack<int> &ansSt){
          visited[u] = true;
          // pehle ('u' ke node ke) bacho ko daalo
          for(auto &v : adj[u]){
              if(!visited[v]){
                  dfs(adj, v, visited, ansSt);
              }
          }
          // ab mujhe daalo
          ansSt.push(u);
      } 
    
      vector<int> topoSort(int V, vector<vector<int>>& edges) {
          // First build the adjacency list
          unordered_map<int, vector<int>> adj;
          for(auto &it : edges){
              int u = it[0];
              int v = it[1];
              adj[u].push_back(v);  // directed graph
            }
            
          stack<int> ansSt;
          vector<bool> visited(V, false);

          for(int i = 0; i < V; i++){
              if(!visited[i]){
                  dfs(adj, i, visited, ansSt);
              }
          }
          
          // answer vector banao
          vector<int> ans;
          while (!ansSt.empty()) {
              ans.push_back(ansSt.top());
              ansSt.pop();
          }
  
          
          return ans;
      }
};



/*
Question 5 :- Topological Sorting using BFS (Kahn's algortihm)

What is Indegree?
    The indegree of a vertex is the number of incoming edges to that vertex.
    For example, if vertex v has edges coming from a, b, and c, then

    indegree (𝑣) = 3

Template :-
    1) Find the Indegree of all the nodes
    2) Fill Queue with all the inDegrees with value 0
    3) Simple BFS
*/

class Solution4_2 {
    public:
    vector<int> topoSort(int V, vector<vector<int>>& edges) {
        // code here
        unordered_map<int, vector<int>> adj;
  
        for(auto &it : edges){
            int u = it[0];
            int v = it[1];
  
            adj[u].push_back(v); // directed graph
        }

        // 1. Find the Indegree of all the nodes
        vector<int> inDegree(V, 0);
        for(auto &u : adj){
            for(auto &v : u.second){
                inDegree[v]++;
            }
        }
  
        // 2. Fill Queue with all the inDegrees with value 0
        queue<int> que;
        for (int i = 0; i < V; i++) {
            if (inDegree[i] == 0) {
                que.push(i);
            }
        }
  
        // 3. Simple BFS
        vector<int> result;
        while(!que.empty()){
            int u = que.front();
            // u ki inDegree 0 hai so push it in the result
            result.push_back(u);
            que.pop();
            // now 'u' pe jitne bhi dependent the unki indegree ghatao, kyuki u ki inDegree 0 ho chuki hai voh game se bahr hai
            for(auto &v : adj[u]){
                inDegree[v]--;
                  
                if(inDegree[v] == 0){
                    que.push(v);
                }
            }
        }
          
        return result;
    }
};



/*
Question 6 :- Detecting a cycle in directed Graph using BFS

Topological sort can only be done on Directed acyclic graph, this means if the topological sort is not possible on a 
directed graph therefore it is a cyclic graph.

So we will use Kan's algorithm
*/

class Solution5 {
    public:
      bool isCyclic(int V, vector<vector<int>> &edges) {
          // code here
          // convert the edges to adj list.
          unordered_map<int, vector<int>> adj;
          for(auto &it : edges){
              int u = it[0];
              int v = it[1];
              
              adj[u].push_back(v);  // directed graph
          }
          // 1. Find the Indegree of all the nodes
          vector<int> inDegree(V, 0);
          for(auto &u : adj){
              for(auto &v : u.second){
                  inDegree[v]++;
              }
          }
          // 2. Fill Queue with all the inDegrees with value 0
          int count = 0;
          queue<int> que;
          for(int i = 0 ; i < V; i++){
              if(inDegree[i] == 0){
                  que.push(i);
                  count++;
              }
          }

          // 3. Simple BFS
          while(!que.empty()){
              int u = que.front();
              // u ki inDegree 0 hai so push it in the result
              que.pop();
              // now 'u' pe jitne bhi dependent the unki indegree ghatao, kyuki u ki inDegree 0 ho chuki hai voh game se bahr hai
              for(auto &v : adj[u]){
                  inDegree[v]--;

                  if(inDegree[v] == 0){
                      que.push(v);
                      count++;
                  } 
              }
          }
          
          if(count == V){ // we visited all node, matlab no cycle
              return false;
          }
          return true;  // we didn't visited all nodes, matlab cycle tha
      }
};



/*  Question 6 : 
    Bipartite Graph :-  A graph in which we can color all the nodes of the graph with exactly 2 colors such that three should be
                        no 2 adjacent nodes with same color.

Key Properties
    1) Bipartite graphs cannot contain odd-length cycles
    2) They can be colored using only two colors (each set gets one color)
    3) All trees are bipartite graphs

A bipartite graph is a type of graph in graph theory where the vertices can be divided into two distinct sets such that:
    1) Every edge connects a vertex from one set to a vertex in the other set
    2) No edge connects two vertices within the same set


If the queston mantions something like dividing the Graph in 2 parts or groups , then it is of Bipartite Graph
*/
class Solution6 {    // Using DFS
    public:
      bool checkBipartite(unordered_map<int, vector<int>> &adjList, int curr, vector<int> &color, int currColor){
          // sabse pehle parent node ko color karr do
          color[curr] = currColor;
          
          for(int &v : adjList[curr]){
              if(color[v] == color[curr]){
                  return false;
              }
              
              if(color[v] == -1){   // never been colored
                  int colorOfV = 1 - currColor;
                  
                  if(checkBipartite(adjList, v, color, colorOfV) == false){
                      return false;
                  }
              }
          }
          
          return true;
      }
    
      bool isBipartite(int V, vector<vector<int>> &edges) {
          // Code here
          // convert to adjacency List
          unordered_map<int, vector<int>> adjList;
          
          for(auto &edge : edges){
              int u = edge[0];
              int v = edge[1];
              
              adjList[u].push_back(v);
              adjList[v].push_back(u);
          }
          
          vector<int> color(V, -1);
          
          for(int i = 0; i < V; i++){
              if(color[i] == -1){ // matlab agr color nahi hua hai toh traverse karo
                  if(!checkBipartite(adjList, i, color, 1)){
                      return false;
                  }
              }
          }
          
          return true;
          
      }
  };




/* Disjoint set Union (DSU)

Disjoint set :- A set in which there is nothing in common, whose intersection is NULL.

There is only 2 Operations in DSU :-
  	1) Combine 2 given sets
	2) To tell if 2 members (b, g) belong to the same set or not
That's why we also called it 'Union Find' ----> Unions 2 set and find the set of 2 elements


Index :    0   1   2   3   4   5   6   7
        ---------------------------------
Element: | a | b | c | d | e | f | g | h |
        ---------------------------------
Parent : | e | a | a | c | g | e | g | g |
        ---------------------------------

*/


// Tempelate
int find(int i, vector<int> parent){
	if(i == parent[i]){    // agr i ka parent khud i hi hai toh
		return i;
	}

	return find(parent[i], parent);   // varna uska parent dhundo
}

void Union(int x, int y, vector<int> parent){
	int x_parent = find(x, parent);
	int y_parent = find(y, parent);

	if(x_parent != y_parent){
		parent[x_parent] = y_parent;
	}
}


/* Problem with the basic DSU

If we keep attaching one set under another without any rule, the structure can become skew tree

👉 find() becomes O(N) in the worst case

To fix this, we use two powerful optimizations:
    1) Union by Rank
    2) Path Compression (in 'Find' code)




1️⃣ Union by Rank (or Size)

❓ What is Rank?
Rank ≈ height (depth) of the tree
    ~ Each set is represented as a tree
    ~ Root node represents the set
    ~ Rank helps us decide which tree should be attached under which

📌 Rule:
    ~ Attach the smaller height tree under the larger height tree
    (Smaller rank under the larger rank)

This helps the Tree not to be Skewed !!


2️⃣ Path Compression
❓ What is Path Compression?

Path Compression makes every node point directly to the root
during find() operation.

📌 After one find(), the tree becomes almost flat

*/
vector<int> parent, rankDSU;

int find(int x){
    if(parent[x] != x){
        parent[x] = find(parent[x]);  // Path Compression
    }
    return parent[x];
}
// There are 2 Main rules to find Union in this
// 1) If rank is Equal, then make any one the 'Parent' and increase its rank by 1
// 2) If the rank is not equal, then the element with highest rank would be 'Parent'
void Union(int x, int y){
    int px = find(x);
    int py = find(y);

    if(px == py) return;

    if(rankDSU[px] < rankDSU[py]){
        parent[px] = py;
    }
    else if(rankDSU[px] > rankDSU[py]){
        parent[py] = px;
    }
    else{
        parent[py] = px;
        rankDSU[px]++;
    }
}
// codeStoryWithMIK
int find2(int i, vector<int> parent){
	if(i == parent[i]){    // agr i ka parent khud i hi hai toh
		return i;
	}

	return parent[i] = find2(parent[i], parent);   // varna uska parent dhundo
}



// Question 7 :- Function to detect cycle using DSU in an undirected graph.
int detectCycle(int V, vector<int> adj[]) {
    // Code here
    parent.resize(V);
    rankDSU.resize(V);
    
    for(int i = 0; i < V; i++){
        parent[i] = i;    // starting me sab khud ke hi parent hote hai
        rankDSU[i] = 0;   // the rank of a single node in a tree is 0
    }
    for(int u = 0; u < V; u++){
        for(auto v : adj[u]){
            if(u < v){
                int parent_u = find(u);
                int parent_v = find(v);
                
                if(parent_u == parent_v){
                    return true;
                }
                
                Union(u, v);
            }       
        }
    }
    
    return false;
}




// Question 8 :- Leetcode 2316
// From this Question you can learn the how to find the number of members in each component.
long long countPairs(int n, vector<vector<int>>& edges) {
    parent.resize(n);
    rankDSU.resize(n, 0);
    // starting me sab khud ke hi parent hote hai
    for(int i = 0; i < n; i++){
        parent[i] = i;
    }

    // make components
    for(auto &edge : edges){
        int u = edge[0];
        int v = edge[1];

        Union(u, v);
    }

    // make map to store parent(component) ------> size of component
    unordered_map<int, int> mp;

    for(int i = 0; i < n; i++){
        int parent = find(i);    // its like
        mp[parent]++;            // 0---->3, 4----->2, 5----->1
    }

    long long result = 0;
    long long remainingNodes = n;  // starting me saare nodes bache hai

    for(auto it : mp){

        long long componentSize = it.second;

        result += (componentSize) * (remainingNodes - componentSize);
        remainingNodes -= componentSize;  // update the remainingNodes
    }

    return result;
}




// Question 9 :- Dijkstra Algorithm        TC :- O(E logV)
// Used to find the shortest distance from a source 'node' to all the other 'nodes' in weighted graph

/* Important :- Why BFS is not used to find the shortest path in undirected weighted graph ?

    answer :- because it minimizes the number of edges, not the total weight.
            (It works best if the weight of each of the node is same or the graph is unweighted)
*/
class Solution {
    public:
      vector<int> dijkstra(int V, vector<vector<int>> &edges, int src) {
          // Code here
          // Build adjacency list first
          vector<vector<pair<int,int>>> adj(V);
          
          for (auto &e : edges) {
              int u = e[0];
              int v = e[1];
              int w = e[2];
              
              adj[u].push_back({v, w});   // 'u' se 'v' with weight 'w'
              adj[v].push_back({u, w});   // to represent undirected
          }
          
          
          priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
          
          vector<int> distance(V, INT_MAX);
          
          distance[src] = 0;   // source se source ka distance 0
          pq.push({0, src});   // from source -----> distance, node
          
          while(!pq.empty()){
              
              int d    = pq.top().first;   // the cost to reach the present node
              int node = pq.top().second;  // presently at this node
              pq.pop();
              
              // If already found a better path, skip
              if (d > distance[node]) continue;
              
              for(auto &nebr : adj[node]){
                  int adjNode = nebr.first;
                  int wt      = nebr.second;
                  
                  // if the distance to reach adjacent node is less than the 
                  if(distance[node] + wt < distance[adjNode]){
                      distance[adjNode] = distance[node] + wt;
                      pq.push({distance[adjNode], adjNode});
                  }
              }
              
          }
          
          return distance;
      }
  };
// using set
vector <int> dijkstra(int V, vector<vector<int>> adj[], int S) {
    set<pair<int,int>> pq;

    vector<int> result(V, INT_MAX);

    result[S] = 0;
    pq.insert({0, S});

    while(!pq.empty()) {

        auto &it = *pq.begin();

        int d  = it.first;     
        int node = it.second;  
        pq.erase(it);

        for(auto &vec : adj[node]) {

            int adjNode = vec[0];
            int dist    = vec[1];

            if(d + dist < result[adjNode]) {
                
                if(result[adjNode] != INT_MAX) {
                    auto iter = pq.find({result[adjNode], adjNode});
                    pq.erase(iter);
                    //OR, pq.erase({result[adjNode], adjNode});
                }
                
                result[adjNode] = d + dist;
                pq.insert({d+dist, adjNode});
            }
        }
    }
    return result;
}



// Question 10 :-  To find the shortest path from source to destination
class Solution {
    public:
      vector<int> shortestPath(int n, int m, vector<vector<int>>& edges) {
          // Code here
          unordered_map<int, vector<pair<int, int>>> adj;
          
          for(auto &edge : edges){
              int u = edge[0];
              int v = edge[1];
              int w = edge[2];
              
              adj[u].push_back({v, w});
              adj[v].push_back({u, w});
          }
          
          
          priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
          
          vector<int> result(n+1, INT_MAX);
          vector<int> parent(n+1);
          
          for(int i = 1; i <= n; i++){
              parent[i] = i;               // in the starting all the nodes are parent of themselves
          }
          
          result[1] = 0; // the cost to reach the starting node is 0
          pq.push({0, 1});
          
          while(!pq.empty()){
              
              int d    = pq.top().first;    // the cost to reach the present node
              int present_node = pq.top().second;   // presently at this node
              pq.pop();
              
              if (d > result[present_node]) continue;
              
              for(auto &nbr : adj[present_node]){
                  int nbrNode = nbr.first;
                  int cost    = nbr.second;
                  
                  if(d + cost < result[nbrNode]){
                      result[nbrNode] = d + cost;
                      pq.push({d+cost, nbrNode});
                      
                      parent[nbrNode] = present_node;
                  }
              }
          }
          
          
          // if i never reached the destination node (which is n)
          int destNode = n;
          if(result[destNode] == INT_MAX){
              return {-1};
          }
          
          vector<int> path;
          while(parent[destNode] != destNode){
              path.push_back(destNode);
              destNode = parent[destNode];
          }
          // loop will break at 1, because parent[source] = source
          path.push_back(1);
          
          reverse(path.begin(), path.end());
          
          return path;
          
      }
  };

/*
Drawkbacks of Dijkastra :-  1) Can't work with negative edge
                            2) Can't detect negative edges cycle (a cycle whoes sum of edges is < 0)

That's where Bellman-Ford comes in play
    1. Handles negative edge weights
    2. Detects negative cycles
    3. Works on all weighted graphs (directed or undirected (With no -ve edge))
        (was mainly for directed graph, but directed can be converted to directed)


1. Why at most V − 1 relaxations?

    Core fact (VERY IMPORTANT)
        The longest possible simple path in a graph has at most (V − 1) edges

    Why?
        A simple path does not repeat vertices
        Visiting V vertices uses at most V−1 edges

    Implication
        •If a shortest path exists:
        •It must be a simple path
        •Therefore, it has ≤ V − 1 edges
    So:
        After V − 1 full relaxations of all edges,
        all shortest paths must already be found.

2. Why not relax more than V − 1 times?

    If you do another relaxation pass (V-th pass) and any distance still decreases, that means:
    The path must be using more than V − 1 edges

    But a simple path cannot do that.

    ❗ So it must be reusing vertices ⇒ cycle exists
*/
  
// Question 11 :- Belllman ford algo 
class Solution {
    public:
      vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
          // Code here
          int n = edges.size();
          int m = edges[0].size();
          
          vector<int> result(V, INT_MAX);
          result[src] = 0;
          
          for(int count = 1; count <= V-1; count++){
              
              for(auto &edge : edges){
                  
                  int u = edge[0];
                  int v = edge[1];
                  int w = edge[2];
                  
                  if(result[u] != INT_MAX && result[u] + w < result[v]){
                      result[v] = result[u] + w;
                  }
              }
          }
          
          // Now to detect -ve cycle
          // (after V-1 relaxation, if after 1 more relaxation any node gets)
          // (changed then there is definetly a cycle)
          for(auto &edge : edges){
                  
              int u = edge[0];
              int v = edge[1];
              int w = edge[2];
              
              if(result[u] != 1e8 && result[u] + w < result[v]){
                  return {-1};
              }
          }
          
          return result;
          
      }
  };
// TC :- O(V*E)




/* Floyd–Warshall  TC :- O(V³)
1️⃣ What does Floyd–Warshall tell?

    Floyd–Warshall computes the shortest path between every pair of vertices.

In one run, it answers:
    •Shortest distance from i → j
    •For all i, j pairs
    •Works with negative edges
    •Detects negative cycles

2️⃣ When do we use Floyd–Warshall?

Use it when:
    •You need all-pairs shortest paths
    •Graph size is small to medium
    •Negative edges may exist
    •Cycle detection is needed

3️⃣ Core idea (VERY IMPORTANT)

    Gradually allow paths to use more intermediate vertices

At step k:
    “Is the shortest path from i to j better if I’m allowed to go through vertex k?”

4️⃣ How Floyd–Warshall detects negative cycles

🔑 Key observation (VERY IMPORTANT)
    If a vertex is part of a negative cycle,
    the shortest distance from that vertex to itself becomes negative.
*/
class Solution {
    public:
      void floydWarshall(vector<vector<int>> &dist) {
          // Code here
          int n = dist.size();
          const int INF = 100000000;
          
          for(int via = 0; via < n; via++){
              
              for(int i = 0; i < n; i++){
                  for(int j = 0; j < n; j++){
                      if (dist[i][via] == INF || dist[via][j] == INF){
                          continue;
                      }
                      dist[i][j] = min(dist[i][j], dist[i][via] + dist[via][j]);
                  }
              }
          }
      }
  };




/* Spannig Tree

In graph theory, a spanning tree is:
    •A subgraph of a connected, undirected graph
    •It includes all the vertices (nodes)
    •It has no cycles
    •It is connected
    •It contains exactly (V − 1) edges, where V is the number of vertices

In short:
    A spanning tree connects all nodes with the minimum number of edges and no loops.

Example idea:-  If a graph has 5 vertices, any spanning tree of it will have 4 edges.


What is a Minimum Spanning Tree (MST)?

    •A minimum spanning tree is a special type of spanning tree where:
    •Each edge has a weight (cost, distance, time, etc.)
    •Among all possible spanning trees, it has the minimum total weight

In short:- An MST connects all nodes with no cycles and the least total cost.

Prims's and Kruskal's ALgorithm are used to Find minimum spanning Tree


Kruskal’s Algorithm
Idea:
    Keep adding the smallest edge that doesn’t form a cycle.

How it works
    •Sort all edges by increasing weight
    •Start with each vertex as its own component
    •Add the next smallest edge if it doesn’t create a cycle
    •Stop when you have V − 1 edges

Key traits
    •Works well for sparse graphs
    •Focuses on edges, not vertices
    •Does not need the graph to be connected (gives a forest)


Kruskal: “Pick the cheapest edges globally, avoid cycles.”
Prim: “Grow a tree step by step from a starting node.”

*/

// Question 12 :- Finding Minimum spanning Tree (Prims's)
class Solution {
    public:
      typedef pair<int, int> P;
      
      int spanningTree(int V, vector<vector<int>>& edges) {
          // code here
          // built adjaceny list
          unordered_map<int, vector<P>> adjList;
          for(auto &edge : edges){
              int u = edge[0];
              int v = edge[1];
              int w = edge[2];
              
              adjList[u].push_back({v, w});
              adjList[v].push_back({u, w}); // undirected
          }
          
          
          vector<bool> inMST(V, false);
          vector<int> parent(V, -1);

          priority_queue<P, vector<P>, greater<P>> pq;
  
          pq.push({0, 0});  // {wt, node}
  
          int sum = 0;
  
          while(!pq.empty()){
              
              auto p = pq.top();
              pq.pop();
              
              int node = p.second;
              int wt   = p.first;
              
              if(inMST[node] == true) continue;
              
              inMST[node] = true; // mark visited
              sum += wt;
              
              // now iss node se kaha kaha jaa sakte hai ?
              for(auto &it : adjList[node]){
                  int adjNode = it.first;
                  int adjWt   = it.second;
                  
                  if(inMST[adjNode] == false){
                      parent[adjNode] = node;
                      pq.push({adjWt, adjNode});
                  }
              }
          }

          // 🔍 Actual MST edges (path)
          for(int i = 1; i < V; i++){
            cout << parent[i] << " - " << i << endl;
          }
          
          return sum;
      }
};




// Question 13 :- Finding Minimum spanning Tree (Kruskal's)
class Solution {
    public:
      vector<int> parent, rankDSU;
      
      int krushkal(vector<vector<int>>& edges){
          int sum = 0;
          
          for(auto &edge: edges){
              int u  = edge[0];
              int v  = edge[1];
              int wt = edge[2];
              
              int parent_u = find(u);
              int parent_v = find(v);
              
              if(parent_u != parent_v){
                  Union(u, v);
                  sum += wt;
              }
          }
          
          return sum;
      }
      
      int spanningTree(int V, vector<vector<int>>& edges) {
          // code here
          parent.resize(V);
          rankDSU.resize(V, 0);
          for(int i=0; i<V; i++){
              parent[i] = i;
          }
          
          sort(edges.begin(), edges.end(),[](vector<int> &a, vector<int> &b){
                   return a[2] < b[2];
          });
          
          return krushkal(edges);
      }
  };




/*
🔁 Strongly Connected Component (SCC)

    A Strongly Connected Component in a directed graph is:
        •A maximal set of vertices such that every vertex is reachable from every other vertex in that component.
    
    In simple words
        •If you can go from A to B and from B back to A, then A and B are in the same SCC.

    0 → 1 → 2
    ↑   ↓
    └───3

    Here:-
        •{0, 1, 3} is one SCC (all mutually reachable)
        •{2} is its own SCC (no return path)

    Key points about SCCs
        •Only defined for directed graphs
        •Each node belongs to exactly one SCC
        •If you collapse each SCC into a single node, the graph becomes a DAG


Kosaraju’s algorithm finds all SCCs in O(V + E) time using two DFS passes.

🪜 Steps of Kosaraju’s Algorithm

    1️⃣ DFS on original graph
        •Perform DFS for all vertices
        •Push vertices onto a stack in order of finishing time

    2️⃣ Reverse the graph
        •Reverse all edges (this is called the transpose graph)

    3️⃣ DFS using stack order
        •Pop vertices from the stack
        •Run DFS on the reversed graph
        •Each DFS call gives one SCC

    🧩 Why it works (intuition)
        •First DFS orders nodes by exit time
        •Reversing edges turns SCC “sinks” into “sources”
        •Second DFS cleanly extracts each SCC
*/

//Kosaraju's Algorithm :     Time  : O(V+E), V = # vertices, E = # edges , Space : O(V)
class Solution{
	public:
	
	void dfsFill(int u, vector<vector<int>>& adj, vector<bool> &visited, stack<int>& st) {
	    visited[u] = true;
	    
	    for(int &v : adj[u]) {
	        
	        if(!visited[v]) {
	            dfsFill(v, adj, visited, st);
	        }
	        
	    }
	    
	    st.push(u);
	}
	
	void dfsTraverse(int u, vector<vector<int>>& adjReversed, vector<bool> &visited) {
	    visited[u] = true;
	    
	    for(int &v : adjReversed[u]) {
	        
	        if(!visited[v]) {
	            dfsTraverse(v, adjReversed, visited);
	        }
	        
	    }

	}
	
	//Function to find number of strongly connected components in the graph.
    int kosaraju(int V, vector<vector<int>>& adj) {
        stack<int> st;
        vector<bool> visited(V, false);
        
        for(int i = 0; i<V; i++) {
            if(!visited[i]) {
                dfsFill(i, adj, visited, st);
            }
        }
        
        
        vector<vector<int>> adjReversed(V);
        for(int u = 0; u<V; u++) {
            for(int &v : adj[u]) {
                
                //u->v
                //v->u
                adjReversed[v].push_back(u);
                
            }   
        }
        
        int count = 0;
        
        visited = vector<bool>(V, false);
        while(!st.empty()) {
            int node = st.top();
            st.pop();
            if(!visited[node]) {
                dfsTraverse(node, adjReversed, visited);
                count++;
            }
        }
        
        return count;
        
    }
};




// DSU by Size (Not rank)
class DSU {
    vector<int> parent;
	vector<int> size;
public:
    DSU(int n) {
    	parent.resize(n);
        size.resize(n);

        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int find(int x) {
        if (x == parent[x])
            return x;
            
        return parent[x] = find(parent[x]);
    }

    void Union (int x, int y) {
	    int x_parent = find(x);
	    int y_parent = find(y);
	
	    if (x_parent == y_parent) 
	        return;
	
	    if(size[x_parent] > size[y_parent]) {
	        parent[y_parent] = x_parent;
	        size[x_parent]  += size[y_parent];
	    } else if(size[x_parent] < size[y_parent]) {
	        parent[x_parent] = y_parent;
	        size[y_parent]  += size[x_parent];
	    } else {
	        parent[x_parent] = y_parent;
	        size[y_parent]  += size[x_parent];
	    }
	}
};






/*
🔹 Eulerian Path
    •An Eulerian path is a path in a graph that uses every edge exactly once.
    •The path does not have to start and end at the same vertex.
    •Vertices may be repeated, but edges cannot.
    •Condition (for an undirected graph):
        :- The graph is connected (ignoring isolated vertices), and all vertices with non zero degrees should belong
            to a single conncted component
        :- Exactly two vertices have odd degree → the path starts at one odd-degree vertex and ends at the other.


🔹 Eulerian Circuit
    •An Eulerian circuit (or Eulerian cycle) is an Eulerian path that starts and ends at the same vertex.
    •Every edge is still used exactly once.
    •Condition (for an undirected graph):
        •The graph is connected (ignoring isolated vertices), and
        •All vertices have even degree.    
    •Not all Grpahs have Eulerian Circuit
    •If the Graph have Eulerian Circuit then you can start at any node, and will end at that node

    •If a Graph doesn't have Eulerian Circuit, then 
        :- Either you won't be able to come back to the start node
        :- if you came back, you will not be able to visit all the edges of the Graph


Important :- If a Graph have Eulerian Path, but have not a Eulerian Circuit, then the Graph is called Semi-Eulerian Graph
*/


/* Question :- Euler circuit and Path
An Eulerian Path is a path in graph that visits every edge exactly once.
An Eulerian Circuit is an Eulerian Path which starts and ends on the same vertex.
Given an undirected graph with V nodes, and E edges, with adjacency list adj, return 2
if the graph contains an eulerian circuit, else if the graph contains an eulerian path, return 1, otherwise, return 0.


Appraoch :-
    1) Check if all the non-zero vertices are connected to a single component
    2) Odd degree
        • > 2, then Nothing
        • == 2, then EP
        • 0 , then EC
*/
class Solution {
    public:
    
        void DFS(vector<int>adj[], int u, vector<bool>& visited) {
            visited[u] = true;
            
            for(auto it = adj[u].begin(); it != adj[u].end(); it++) {
                if(visited[*it] == false) {
                    DFS(adj, *it, visited);
                }
            }
        }
    
        bool isConnected(int V, vector<int>adj[]) {
            vector<bool> visited(V, false);
            
            //Find a vertex with non-zero degree
            int nonZeroDegreeVertex = -1;
            for(int i = 0; i<V; i++) {
                if(adj[i].size() != 0) {
                    nonZeroDegreeVertex = i;
                    break;
                }
            }
            
            // Start DFS traversal from a vertex with non-zero degree
            DFS(adj, nonZeroDegreeVertex, visited);
            
            // Check if all non-zero degree vertices are visited
            for(int i = 0; i<V; i++) {
                if(visited[i] == false && adj[i].size() > 0)
                    return false;
            }
            return true;
        }
    
        int isEularCircuit(int V, vector<int>adj[]){
            
            //Check if all non-zero degree vertices are connected
            if(isConnected(V, adj) == false) {
                return 0; //Non-Eulerian
            }
            
            //Count vertices with odd degree
            int oddCount = 0;
            for(int i = 0; i<V; i++) {
                if(adj[i].size()%2 != 0) {
                    oddCount++;
                }
            }
            
            // If count is more than 2, then graph is not Eulerian
            if (oddCount > 2)
                return 0; //Non-Eulerian
            
            if(oddCount == 2) {
                return 1; //Semi-Eulerian (It has only Euler Path)
            }
            
            return 2; //(Euler Circuit)
            
        }
    };



/* Euler path and circuit in Directed Graph

To find if There is a Euler Path or not, there should be exactly one node that folows the rule :-
    For Source      :- outDegree[node] - inDegree[node] == 1
    For destination :- inDegree[node] - outDegree[node] == 1
    other nodes     :- inDegree[node] == outDegree[node]

To find the Euler path :-
    a) Find Source node, to start
        if(outDegree[node] - inDegree[node] == 1){
            startNode = node;
        }

    b) If the all nodes have equal inDegree and outDegree then that graph is called Euler Circuit


Pseudocode (Directed Graph) :- 

HIERHOLZER(graph):
    stack ← empty stack
    path ← empty list

    start ← valid start node
    push start into stack

    while stack is not empty:
        v ← top of stack

        if v has unused outgoing edges:
            u ← one unused neighbor of v
            remove edge (v → u) from graph
            push u into stack
        else:
            pop v from stack
            append v to path

    reverse(path)
    return path

Pseudocode (Undirected Graph) :- 

HIERHOLZER_UNDIRECTED(graph):
    stack ← empty stack
    path ← empty list

    start ← any vertex with non-zero degree
    push start into stack

    while stack is not empty:
        v ← top of stack

        if v has unused edges:
            u ← one unused neighbor of v
            remove edge (v, u) from graph
            push u into stack
        else:
            pop v from stack
            append v to path

    reverse(path)
    return path
*/
vector<int> hierholzer(int start, vector<vector<int>> &adj) {
    stack<int> st;
    vector<int> path;

    st.push(start);

    while (!st.empty()) {
        int v = st.top();

        if (!adj[v].empty()) {
            int u = adj[v].back();
            adj[v].pop_back();   // remove edge v -> u
            st.push(u);
        } else {
            path.push_back(v);
            st.pop();
        }
    }

    reverse(path.begin(), path.end());
    return path;
}




/* Diameter of a Graph :- The longest path from any one node to any other node , without repeating any edge in a Graph.

    Two rules are there (see CodeStoryWithMIK video video 44)
    let the actual diameter of a Graph is from node A--to--B
        1) if you find the diameter from any random node in the Graph, it will always end in the either of the node of actual Diameter (A or B).
        2) Use the above step to find the one node of the Diameter, that will return either A or B.
        3) Now use the returned node, to find the other end of the actual Diameter.

// 3203. Find Minimum Diameter After Merging Two Trees */
class Solution {
    public:
    
        int n;
        pair<int, int> BFS(unordered_map<int, vector<int>>& adj, int source) {
            queue<int> que;
            que.push(source);
    
            unordered_map<int, bool> visited;
            visited[source] = true;
    
            int distance = 0;
            int farthestNode = source;
    
            while(!que.empty()) {
                int size = que.size(); //current level me itne nodes hain
    
                while(size--) {
                    int curr = que.front();
                    que.pop();
    
                    farthestNode = curr;
    
                    for(auto &nbr : adj[curr]) {
                        if(visited[nbr] == false) {
                            visited[nbr] = true;
                            que.push(nbr);
                        }
                    }
                }
                if(!que.empty()) {
                    distance++;
                }
            }
    
            return {farthestNode, distance};
    
        }
    
        int findDiameter(unordered_map<int, vector<int>> adj) {
            //step-1 find the farthest node from a random node - 0
            auto [farthestNode, dist] = BFS(adj, 0);
    
            //step-2 : the farthestNode we got above is nothing but one end of the diameter of adj
    
            //step-3 : Find the farthestnode from the node we got above , that will be the other end of diameter - diameter
            auto [otherEndNode, diameter] = BFS(adj, farthestNode);
    
            return diameter;
        }
    
        unordered_map<int, vector<int>> buildAdj(vector<vector<int>>& edges) {
            unordered_map<int, vector<int>> adj;
    
            for(auto &edge : edges) {
                int u = edge[0];
                int v = edge[1];
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
            return adj;
        }
    
    
        int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
            unordered_map<int, vector<int>> adj1 = buildAdj(edges1);
            unordered_map<int, vector<int>> adj2 = buildAdj(edges2);
    
            int d1 = findDiameter(adj1);
            int d2 = findDiameter(adj2);
    
            int combined = (d1+1)/2 + (d2+1)/2 + 1;
    
            return max({d1, d2, combined});
        }
    };




/*Multi Source BSF :- Starts Simultaneosly form multiple sources

- useful when you wants to spread out from multiple sources/nodes at once.
- hen you need to compute shortest distance / minimum cost / minimum time from multiple starting points to other points in a grid / graph.

Multi-Source BFS ensures that all the nodes are reached with minimal Distance / Time from nearest source.
*/

// leetcode 994 :-
class Solution {
    public:
        typedef pair<int, int> P;
        vector<vector<int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
        int orangesRotting(vector<vector<int>>& grid) {
            // multi source BFS
            int m = grid.size();
            int n = grid[0].size();
    
            queue<P> que;
            int freshCount = 0;
    
            for(int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++) {
                    if(grid[i][j] == 2) {
                        que.push({i, j}); //Storing all possible sources at once in the queue
                    }
                    else if(grid[i][j] == 1) {
                        freshCount++;
                    }
                }
            }
            
            if(freshCount == 0)
                return 0;
            
            auto isSafe = [&](int x, int y) {
                return x >= 0 && x < grid.size() && y >= 0 && y<grid[x].size() && grid[x][y] == 1;
            };
            
            //Applying Multi-Source BFS
            int time = 0;
            while(!que.empty()) {
                int n = que.size();
                //because we want to cover all neighbours of a node
                //at once which are affected in a particular time frame
                while(n--) {
                    P curr = que.front();
                    que.pop();
                    int i = curr.first;
                    int j = curr.second;
                    
                    for(auto &dir : directions) {
                        int new_i = i + dir[0];
                        int new_j = j + dir[1];
                        
                        if(isSafe(new_i, new_j)) {
                            grid[new_i][new_j] = 2;
                            que.push({new_i, new_j});
                            freshCount--;
                        }
                    }
                }
                time++;
            }
            
            return (freshCount==0) ? time-1 : -1;
        }
    };


// Imporrtant :- Leetocde 1765
class Solution {
    public:
        typedef pair<int, int> P;
        vector<vector<int>> directions{{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    
        vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
            int m = isWater.size();
            int n = isWater[0].size();
    
    
            vector<vector<int>> height(m, vector<int>(n, -1));
    
            queue<P> que;
            //Height of water cells must be 0 only
            //T.C : O(m*n)
            for(int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++) {
                    if(isWater[i][j] == 1) { //this cell is water
                        height[i][j] = 0; //This is a source for hitting BFS
                        que.push({i, j});
                    }
                }
            }
    
            //Apply khandani template - Multi source BFS ka
            //T.C : O(m*n)
            //S.C : O(m*n)
            while(!que.empty()) {
                int N = que.size();
    
                while(N--) {
                    P curr = que.front();
                    que.pop();
    
                    int i = curr.first;
                    int j = curr.second;
    
                    for(auto &dir : directions) {
                        int i_ = i + dir[0];
                        int j_ = j + dir[1];
    
                        if(i_ >= 0 && i_ < m && j_ >= 0 && j_ < n && height[i_][j_] == -1) {
                            height[i_][j_] = height[i][j] + 1;
                            que.push({i_, j_});
                        }
                    }
                }
            }
    
            return height;
        }
    };



int main() {
    // =======================
    // Question 1 : Undirected Graph Cycle Detection (DFS)
    // =======================
    Solution1 sol1;
    int V1 = 5;
    vector<vector<int>> edges1 = {
        {0, 1}, {1, 2}, {2, 0}, {3, 4}
    };

    if (sol1.isCycle(V1, edges1))
        cout << "Cycle detected!" << endl;
    else
        cout << "No cycle found." << endl;




    // =======================
    // Question 2 : Undirected Graph Cycle Detection (BFS)
    // =======================
    Solution2 sol2;
    int V2 = 5;
    vector<vector<int>> edges2 = {
        {0, 1}, {1, 2}, {2, 0}, {3, 4}
    };
    // first make adjacency list from the given set of edges
    vector<int> adj[V2];
    for (const auto &e : edges2) {
        int u = e[0], v = e[1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (sol2.isCycle(V2, adj))
        cout << "Cycle detected!" << endl;
    else
        cout << "No cycle found." << endl;




    // =======================
    // Question 3 : Directed Graph Cycle Detection (DFS)
    // =======================
    Solution3 sol3;
    int V3 = 4;
    vector<vector<int>> edges3 = {
        {0, 1}, {1, 2}, {2, 0}, {2, 3}
    };

    if (sol3.isCyclic(V3, edges3))
        cout << "Cycle detected!" << endl;
    else
        cout << "No cycle found." << endl;



    // =======================
    // Question 4 : Topological Sort (DFS)
    // =======================
    Solution4 sol4_dfs;
    int V4 = 6;
    vector<vector<int>> edges4 = {
        {5, 0}, {5, 2}, {4, 0}, {4, 1}, {2, 3}, {3, 1}
    };

    vector<int> topoDFS = sol4_dfs.topoSort(V4, edges4);
    cout << "Q4 (Topo DFS): ";
    for (int x : topoDFS) cout << x << " ";
    cout << endl;



    // =======================
    // Question 4_2 : Topological Sort (BFS / Kahn’s Algorithm)
    // =======================
    Solution4_2 sol4_bfs;
    vector<int> topoBFS = sol4_bfs.topoSort(V4, edges4);
    cout << "Q5 (Topo BFS): ";
    for (int x : topoBFS) cout << x << " ";
    cout << endl;


    // =======================
    // Question 5 : Directed Graph Cycle Detection (BFS / Kahn’s)
    // =======================
    Solution5 sol5;
    int V6 = 4;
    vector<vector<int>> edges6 = {
        {0, 1}, {1, 2}, {2, 0}, {2, 3}
    };

    if (sol5.isCyclic(V6, edges6))
        cout << "Q6 (BFS Directed): Cycle detected!" << endl;
    else
        cout << "Q6 (BFS Directed): No cycle found." << endl;



    
    // =======================
    // Question 6 : Bipartite Graph
    // =======================
    Solution6 sol6;

    // -------- Test Case 1 : Bipartite Graph --------
    int V1 = 4;
    vector<vector<int>> edges1 = {
        {0, 1},
        {1, 2},
        {2, 3}
    };

    if (sol6.isBipartite(V1, edges1))
        cout << "Graph 1 is Bipartite" << endl;
    else
        cout << "Graph 1 is NOT Bipartite" << endl;


    // -------- Test Case 2 : Non-Bipartite Graph (Odd Cycle) --------
    int V2 = 3;
    vector<vector<int>> edges2 = {
        {0, 1},
        {1, 2},
        {2, 0}
    };

    if (sol6.isBipartite(V2, edges2))
        cout << "Graph 2 is Bipartite" << endl;
    else
        cout << "Graph 2 is NOT Bipartite" << endl;


    // -------- Test Case 3 : Disconnected Bipartite Graph --------
    int V3 = 5;
    vector<vector<int>> edges3 = {
        {0, 1},
        {2, 3}
    };

    if (sol6.isBipartite(V3, edges3))
        cout << "Graph 3 is Bipartite" << endl;
    else
        cout << "Graph 3 is NOT Bipartite" << endl;



    



    return 0;

}


