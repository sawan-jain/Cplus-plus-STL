// PROBLEM LINK: https://cses.fi/problemset/task/1196/
// SOLUTION: https://cses.fi/paste/6ad6590fcca7fb36644f24/

#include<bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define int long long
using namespace std;

const int N = 1e5 + 5;
int K = 11;
vector<vector<int>> g[N]; 
vector<vector<int>> dp(N,vector<int>(K,1e18)); 

void dijkstra(int k) {
    priority_queue<pair<int,int>> pq;
    dp[1][0] = 0;

    pq.push({0,1});
    while(!pq.empty()) {
        int dis = pq.top().first * -1;
        int u = pq.top().second;
        pq.pop();

        if(dp[u][k-1] < dis) continue;
        for(auto nbr: g[u]) {
            int v = nbr[1], d = nbr[0];
            if(dp[v][k-1] > d + dis) {
                dp[v][k-1] = d + dis;
                pq.push({-1*dp[v][k-1],v});
                sort(dp[v].begin(),dp[v].end());
            }
        }
    }
}

void solution() {
    int n,m,k; cin >> n >> m >> k;

    for(int i=0; i<m; i++) {
        int u,v,w; cin >> u >> v >> w;
        g[u].push_back({w,v});
    }

    dijkstra(k);
    for(int i=0; i<k; i++) cout << dp[n][i] << " ";
}

int32_t main() {
    fast_io;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    int t = 1;
    while(t--) solution();
}
