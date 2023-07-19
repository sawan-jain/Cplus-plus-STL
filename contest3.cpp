#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define fast_io ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;
using namespace __gnu_pbds;
#define int long long

template<typename T>
using ordered_set = tree<T, null_type,less<T>, rb_tree_tag,tree_order_statistics_node_update>;

void dfs(int u,int p,vector<pair<int,int>> g[],vector<vector<int>> &dp,int &maxi) {
    if(p!=-1 && g[u].size() == 1) {
        dp[u][0] = 0;dp[u][1] = 0;
        return;
    }

    for(auto nbr: g[u]) {
        int v = nbr.first, wt = nbr.second;
        if(v == p) continue;
        dfs(v,u,g,dp,maxi);

        dp[u][0] = max(dp[u][0], wt + dp[v][0]);
    }

    int mx1 = 0, mx2 = 0;
    for(auto nbr: g[u]) {
        int v = nbr.first, wt = nbr.second;
        if(dp[v][0]+wt >= mx1) {
            mx2 = mx1;
            mx1 = dp[v][0]+wt;
        }

        else if(dp[v][0]+wt > mx2) {
            mx2 = dp[v][0]+wt;
        }
    }

    dp[u][1] = mx1 + mx2;
    maxi = max({maxi,dp[u][0],dp[u][1]});
}

bool isPossible(vector<int> &mp) {
    int val = 0;
    for(int i=0; i<26; i++) {
        if(mp[i]>0) {
            if(val == 0) val = mp[i];
            else if(val != mp[i]) return false;    
        }
    }

    return true;
}

int f(int i,int n,string s,vector<int> &dp) {
    if(i == n) return 0;
    if(dp[i] != -1) return dp[i];

    int ans = 1e9;
    vector<int> mp(26,0);

    for(int j=i; j<n; j++) {
        mp[s[j]-97]++;
        if(isPossible(mp)) {
            ans = min(ans, 1 + f(j+1,n,s,dp));
        }

        else ans = min(ans, 1 + f(j,n,s,dp));
    }

    return dp[i] = ans;
}

void solution() {
    // int n,k; cin >> n >> k;
    // int sum = 0;
    // vector<pair<int,int>> g[n+1];
    // vector<vector<int>> dp(n+1,vector<int>(3,0));

    // for(int i=0; i<n-1; i++) {
    //     int u,v,w; cin >> u >> v >> w;
    //     g[u].push_back({v,w});
    //     g[v].push_back({u,w});
    //     sum += w;
    // }

    // if(k > 1) {
    //     cout << sum << "\n";
    //     return;
    // }

    // int maxi = 0;
    // dfs(1,-1,g,dp,maxi);
    // cout << maxi << "\n";

    // int n; cin >> n;
    // double avg = 0;
    // set<int> st;
    // for(int i=0; i<n; i++) {
    //     int x; cin >> x;
    //     st.insert(x);
    //     avg += (x + 0.0);
    // }

    // avg = avg/(n + 0.0);
    // cout << avg << "\n";
    // int avg2 = (int)ceil(avg);
    // if(st.find(avg2) != st.end()) cout << "True";
    // else cout << "False";

    string s; cin >> s;
    vector<int> dp(s.length(),-1);
    cout << f(0,s.length(),s,dp) << "\n";
}
 
int32_t main() {
    fast_io;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    int t; cin >> t;
    while(t--) solution();
}
