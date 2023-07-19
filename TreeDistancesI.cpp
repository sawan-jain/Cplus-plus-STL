// CSES PROBLEM - Tree Distances I
// LINK : https://cses.fi/problemset/task/1132
// VIDEO LINK: https://youtu.be/V1OrZvvKC0k

#include<bits/stdc++.h>
#define int long long
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;

const int N = 2e5 + 3;
vector<int> g[N];
vector<vector<int>> dp(N,vector<int>(2,0));
// vector<int> parent(N,-1);

void dfs1(int node,int par) {
    for(int nbr:g[node]) {
        if(nbr != par) {
            dfs1(nbr,node);
            dp[node][0] = max(dp[node][0],1 + dp[nbr][0]);
        }
    }
}

void dfs2(int node,int par) {

    int mx1 = -1, mx2 = -1;
    for(int nbr: g[node]) {
        if(nbr != par) {
            if(mx1 <= dp[nbr][0]) {
                mx2 = mx1;
                mx1 = dp[nbr][0];
            }

            else if(mx2 < dp[nbr][0]) {
                mx2 = dp[nbr][0];
            }
        }
    }

    for(int nbr: g[node]) {
        if(nbr != par) {
            int longest = mx1;
            if(dp[nbr][0] == mx1) longest = mx2;
            dp[nbr][1] = 1 + max(dp[node][1],longest+1);
            dfs2(nbr,node);        
        }
    }

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

    dfs1(1,-1);
    dfs2(1,-1);

    for(int i=1; i<=n; i++) {
        cout << max(dp[i][0],dp[i][1]) << " ";
    }
}

