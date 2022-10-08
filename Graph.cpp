#include<iostream>
#include<list>
#include<queue>
#include<unordered_map>
#include<vector>
#include<bits/stdc++.h>
using namespace std;

class Graph {
    int v;
    list<int> *l;

public :
    Graph(int V) {
        v = V;
        l = new list<int>[v];
    }

    void addNode(int i,int j,bool undir = true) {
        l[i].push_back(j);
        if(undir) {
            l[j].push_back(i);
        }
    }

    // BFS CALCULATES THE MINIMUM DISTANCE BW ANY 2 GIVEN VERTICES IN A GRAPH
    // BFS IS A LEVEL ORDER TRAVERSAL 

    void BFS(int source) {   
        queue<int> out;
        unordered_map<int,bool> vis;
        unordered_map<int,int> dis;   // map containing the vertex and its distance from source

        out.push(source);
        vis[source] = true;
        dis[source] = 0;

        while(!out.empty()) {
            
            for(auto nbr: l[out.front()]) {
                if(!vis[nbr]) {
                    out.push(nbr);
                    dis[nbr] = dis[out.front()]+1;
                    vis[nbr] = true;
                }
            }

            cout<<out.front()<<endl;
            out.pop();
        }
    }

    void DFShelper(int node,unordered_map<int,bool> &vis) {
        vis[node] = true;
        cout<<node<<" ";

        for(int nbr:l[node]) {
            if(!vis[nbr]) {
                DFShelper(nbr,vis);
            }
        }

        return;
    }

    void DFS(int source) {
        unordered_map<int,bool> vis;
        DFShelper(source,vis);         
    }

    void topological_sort() {
        vector<int> indegree(v,0);
        for(int i=0; i<v; i++) {
            for(auto nbr: l[i]) {
                indegree[nbr]++;
            }
        }

        queue<int> q;
        for(int i=0; i<v; i++) {
            if(indegree[i]==0) {
                q.push(i);
            }
        }

        while(!q.empty()) {
            int f = q.front() ;
            cout<<f<<endl;
            q.pop(); 
           
            for(auto nbr: l[f]) {
                indegree[nbr]--;
                if(indegree[nbr]==0) {
                    q.push(nbr);
                }
            }
        }
    }

    list<int>* List() {
        return l;
    }

};

void helper1(list<int>* l,vector<int> &v,int i,vector<vector<int>> &add) {
    
    int key = v[i];
    if(l[key].size() == 0) {
        add.push_back(v);
bellman_Ford_Algorithm
        //backtracking
        v.pop_back();

        return;
    }

    for(int nbr:l[key]) {
        v.push_back(nbr);
        helper1(l,v,i+1,add);
    }

    //backtracking 
    v.pop_back();
}


vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& v) {
    Graph g(v.size());
    vector<int> indegree(v.size(),0);
    vector<vector<int>> add;
    for(int i=0; i<v.size(); i++) {
        for(int j=0; j<v[i].size(); j++) {
            int key = v[i][j];
            g.addNode(i,key,false);
            indegree[key]++;
        }
    } 

    int k=0;
    for(;k<indegree.size(); k++) {
        if(indegree[k]==0) {
            break;
        }
    }

    list<int>* l = g.List();
    vector<int> v1;
    v1.push_back(k);
    helper1(l,v1,0,add);

    return add;

}

void helper(vector<vector<int>> v, vector<vector<int>> &ans, int i,vector<int> &add) {
    
    if(v[i].size() == 0) {
        ans.push_back(add);
        add.pop_back();
        return;
    }

    for(int nbr: v[i]) {
        add.push_back(nbr);
        helper(v,ans,nbr,add);
    }

    add.pop_back();
}

vector<vector<int>> pathToSource(vector<vector<int>> &v) {
    vector<vector<int>> ans;
    vector<int> add;

    vector<int> v1(v.size(),0);
    for(int i=0; i<v.size(); i++) {
        for(int x:v[i]) {
            v1[x]++;
        }
    }

    int k = 0;
    for(; k<ans.size(); k++) {
        if(v1[k] == 0) break;
    }

    add.push_back(k);
    helper(v,ans,0,add);

    for(int i=0; i<ans.size(); i++) {
        for(int x: ans[i]) cout<<x<<" ";

        cout<<"\n";
    }
    return ans;
}

/*bool canVisitAllRooms(vector<vector<int>>& rooms) {
    Graph g(rooms.size());
    vector<bool> visited(rooms.size(),false);
    visited[0] = true;
    for(int i=0; i<rooms.size(); i++) {
        for(int j=0; j<rooms[i].size(); j++) {
            int key = rooms[i][j];
            g.addNode(i,key,false);
            visited[key] = true;
        }
    }

    for(int i=0; i<rooms.size(); i++) {
        
        if(visited[i]==false) {
            return false;
        }
    }

    return true;
}*/

bool canVisitAllRooms(vector<vector<int>> &rooms) {
    vector<bool> visited(rooms.size(),false);
    visited[0] = true;

    for(int i=0; i<rooms.size(); i++) {
        for(int j=0; j<rooms[i].size(); j++) {
            visited[rooms[i][j]] = true;
        }
    }

    for(int i=0; i<visited.size(); i++) {
        if(visited[i] == false) return false;
    }

    return true;
}

// a star topology was given and we have to find the centre of the star
// done by calculating the number of edges each node is connected and finding the index with max value

int findCenter(vector<vector<int>>& v) {
    //Graph g(v.size()+1);
    vector<int> edges(v.size()+2,0);
    for(int i=0; i<v.size(); i++) {
        int u = v[i][0];
        int v1 = v[i][1];
        //g.addNode(u,v1);
        edges[u]++;
        edges[v1]++;
    }

    int max = *max_element(edges.begin(),edges.end());
    for(int i=1; i<v.size()+2; i++) {
        if(edges[i] == max) return i;
    }

}

int find(vector<vector<int>> &v) {
    vector<int> edges(v.size()+1,0);
    for(int i=0; i<v.size(); i++) {
        for(int j=0; j<2 ;j++) {
            int index = v[i][j];
            edges[index]++;
        }
    }

    int max = edges[0];
    int val = 0;
    for(int i=1; i<v.size()+1 ;i++) {
        if(edges[i]>max) {
            max = edges[i];
            val = i;
        }
    }

    return val;

}

vector<int> bellman_Ford_Algorithm(vector<vector<int> v,int src,int n) { 
    // This Algo is used ot find the shortest path btw starting node to all other nodes provided the graph does not contain 
    // cycle with negative length in a weighted graph. However it can detect negative cycles also.

    // v = {node1,node2,weight}  n = no. of nodes/vertex in graph
    // v.size() = no. of edges int graph


    vector<int> distance(v.size(),INT_MAX);
    distance[src] = 0;

    for(int i=1; i<=n-1; i++) {
        for(auto e : v) {
            int a = e[0];
            int b = e[1];
            int w = e[2];

            distance[b] = min(distance[b],distance[a]+w);
        }
    }

    return distance;
} 

vector<int> dijkstra_Algo(vector<vector<pair<int,int>>> v, int src) {
    priority_queue<pair<int,int>> q;
    vector<int> distance(v.size(),INT_MAX);
    vector<bool> visited(v.size(),false);

    distance[src] = 0;
    q.push({0,src});

    while(!q.empty()) {
        int a = q.top().first;
        q.pop();
        if(visited[a]) continue;
        visited[a] = true;

        for(auto u : v[a]) {
            int b = u.second,w = u.first;
            if(distance[a] > distance[w]+b) {
                distance[a] = distance[w]+b;
                q.push({-1*distance[w],w});
            }
        }
    }

    return distance;
}

// *********************************************************************************************************
// code to find the number of possible paths btw 2 nodes in a graph
// TIME COMPLEXITY = O(N*E) -----> optimised approach using DP
// OTHERWISE USING BACKTRACKING AND LOOPS THE TIME COMPLEXITY COMES OUT TO BE O(N!)

int helper_number_of_paths(vector<vector<int>> parents,vector<int> &paths,int dest) {
    
    if(dest == 0) {
        return 1;
    }

    if(paths[dest] != 0) {
        return paths[dest];
    }

    for(int x : parents[dest]) {
        paths[dest] += helper_number_of_paths(parents,paths,x);
    }

    return paths[dest];
}

int number_Of_Paths(vector<vector<int>> v,int dest) {
    /*vector<vector<int>> parents(v.size(),vector<int>k);
    
    for(int i=0; i<v.size(); i++) {
        for(int x : v[i]) {
            parents[x].push_back({i});
        }
    }*/

    vector<int> paths(v.size(),0);
    paths[0] = 1;
    helper_number_of_paths(v,paths,dest);
    return paths[dest];

}

void helper_paths_bwnodes(vector<int> adj[], vector<int> &paths,int node) {
    if(adj[node].size() == 0) return;
    for(int x : adj[node]) {
        paths[x] = max(paths[x],paths[x]+paths[node]);
        helper_paths_bwnodes(adj,paths,x);
    }
    
}

int paths_bw_nodes(vector<int> adj[], int src, int dest) {
    vector<int> paths(adj.size()+1,0);
    paths[src] = 1;
}

// **************************************************************************************************
// code ot find the shortest or longest path btw 2 nodes in a graph
// shortest ----> BFS
// longest -----> write topological sort and difference btw index of the 2 nodes will give the max no of edges btw them

// **************************************************************************************************





int main() {

    vector<vector<int>> rooms = {{4,3,1},{3,2,4},{3},{4},{}};
    vector<vector<int>> v = {{1,3,4},{2,3,4},{3},{4},{}};
    //cout<<find(v)<<endl;
    pathToSource(v);

    Graph g(7);
    g.addNode(0,1);
    g.addNode(1,2);
    g.addNode(3,5);
    g.addNode(5,6);
    g.addNode(4,5);
    g.addNode(0,4);
    g.addNode(3,4);

   // g.BFS(1);
    //g.DFS(1);

    //g.topological_sort();
    return 0;
}
