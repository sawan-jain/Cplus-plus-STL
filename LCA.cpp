// BINARY LIFTING : FINDING THE Kth ANCESTOR OF A NODE IN A TREE
// MAX HEIGHT OF TREE = 19/20

#include<bits/stdc++.h>
#define int long long
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;

const int N = 2e5 + 3, K = 20;
vector<int> g[N];
vector<vector<int>> dp(N,vector<int>(K+1,0));
vector<int> lvl(N,0);

// dp[u][i] : 2^i ancestor node of node U
// up(u,i) = up(up(u,i-1),i-1)

void dfs(int u,int p) {

    if(p != -1) lvl[u] = lvl[p] + 1;

    dp[u][0] = p;
    for(int i=1; i<=K; i++) {
        if(dp[u][i-1] != -1) {
            dp[u][i] = dp[dp[u][i-1]][i-1];  
        }

        else dp[u][i] = -1;
    }

    for(int v:g[u]) {
        if(v == p) continue;
        dfs(v,u);
    }

}

int query(int u,int k) {

    for(int i=31; i>=0; i--) {
        if(u == -1 || k == 0) break;
        if((k>>i)&1) {
            u = dp[u][i];
            k -= (1<<i);
        }
    }

    return u;

}

int LCA(int u,int v) {
    if(lvl[u] < lvl[v]) swap(u,v);

    u = query(u,lvl[u]-lvl[v]);  // now u,v are at the same level 

    if(u == v) return u;

    for(int i=19; i>=0; i--) {
        if(dp[u][i] != dp[v][i]) {
            u = dp[u][i];
            v = dp[v][i];
        }
    }

    return query(u,1);   
}


int32_t main() {
    fast_io;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif

    int n; cin >> n;
    if(n == 1) {cout << 0 << "\n"; return 0;}
    for(int i=1; i<n; i++) {
        int u,v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1,-1);

    int q; cin >> q;
    while(q--) {
        int u,v; cin >> u >> v;
        cout << LCA(u,v) << "\n";
    }
    return 0;
}

