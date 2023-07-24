#include<bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define int long long 
using namespace std;

const int N = 5e4 + 5;
void dfs(int u,unordered_map<int,int> &vis,vector<int> &nodes,vector<int> rg[]) {
    vis[u] = 1;
    for(int v: rg[u]) {
        if(vis[v] == 0) dfs(v,vis,nodes,rg);
    }
 
    nodes.push_back(u);
}
 
void solution() {
    int n,m,q; cin >> n >> m >> q;

    vector<int> g[n+1],rg[n+1];
 
    for(int i=0; i<m; i++) {
        int u,v; cin >> u >> v;
        g[u].push_back(v);
        rg[v].push_back(u);
    }
    
    // TO FIND SCC AND NAME THE COMPONENTS
    unordered_map<int,int> vis1,vis2;
    vector<int> nodes;
    for(int i=1; i<=n; i++) {
        if(vis1[i] == 0) {
            dfs(i,vis1,nodes,g);
        }
    }
 
    vector<int> ans(n+1,0);
    int u = 0, v = 0,cnt = 0;
    for(int i=n-1; i>=0; i--) {
        if(vis2[nodes[i]] == 0) {
            cnt++;
            vector<int> node;
            dfs(nodes[i],vis2,node,rg);

            // numbering the nodes according to scc
            for(int x: node) ans[x] = cnt;
 
        }
    }   


    // creating a condensed graph
    vector<int> condn[n+1];
    for(int i=1; i<=n; i++) {
        for(auto j: g[i]) {

            // checking if i and j are in same or different scc
            if(ans[i] != ans[j]) {
                condn[ans[i]].push_back(ans[j]);
            }
        }
    }

    vis1.clear();
    nodes.clear();

    // toposort of the condensed graph to 
    for(int i=1; i<=n; i++) {
        if(vis1[i] == 0) {
            dfs(i,vis1,nodes,condn);
        }
    }

    // preprocessing to answer reachability queries
    vector<bitset<N>> dp(N);
    for(auto d: nodes) {
        dp[d][d] = 1;
        for(auto i: condn[d]) {
            dp[d] |= dp[i];
        }
    }


    while(q--) {
        int a,b; cin >> a >> b;
        if(dp[ans[a]][ans[b]] == 0) cout << "NO\n";
        else cout << "YES\n";
    }
}
int32_t main() {
    fast_io;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    int t= 1;
    while(t--) solution();
}


