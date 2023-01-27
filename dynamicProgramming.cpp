#include<bits/stdc++.h>
using namespace std;

const int m = 1e9+7;

int coinChange(int n,vector<int>denom,vector<int>&dp) {
    if(n == 0) return 0;
    if(dp[n]!=INT_MAX) return dp[n];

    for(int coins:denom) {
        if(n-coins>=0) {
            dp[n] = min(dp[n],coinChange(n-coins,denom,dp)+1);
        }
    }

    return dp[n];
}

int coinChangeWays(int n, vector<int> denom,vector<int> &dp) {
    if(n == 0) return 1;
    if(dp[n]!=0) return dp[n];
    
    for(int coin:denom) {
        if(n-coin>=0) {
            dp[n] += coinChangeWays(n-coin,denom,dp);
            dp[n] %= m;
        }
    }
    return dp[n];
}



int longest(vector<int> arr) {
    vector<int> dp(arr.size(),1);

    for(int i=1; i<arr.size(); i++) {
        for(int j=0; j<i; j++) {
            if(arr[j]<=arr[i]) dp[i] = max(dp[i],dp[j]+1);
        }
    }
    int m = dp[0];   
    for(int x : dp) {
        m = max(m,x);
    }
    return m;
}

int knapSack(vector<int> weight, vector<int> price,int W,int n,vector<vector<int>> &dp) {
    if(n == 0 || W == 0) return 0;
    if(dp[n][W] != 0) return dp[n][W];

    int inc = 0;
    if(W-weight[n-1]>=0) inc = knapSack(weight,price,W-weight[n-1],n-1,dp) + price[n-1];
    int exc = knapSack(weight,price,W,n-1,dp);

    return dp[n][W] = max(inc,exc);
}

int f(int i,int c,vector<int> A,unordered_map<int,bool> m,vector<vector<int>> &dp) {
    //base case
    if(i == 0) {
        if(A[0] == c) return 1;
        return 0;
    }

    if(dp[i][c] != -1) return dp[i][c];

    //rec case
    int exc = f(i-1,c,A,m,dp);
    int inc = 0;
    if(!m[i] && c-A[i] >=0) {
        inc += 1 + f(i-1,c-A[i],A,m,dp);
    }

    return dp[i][c] = max(inc,exc);
}

vector<int> maximumToys(int N,vector<int> A,int Q,vector<vector<int>> Queries){

    vector<int> ans;

    for(int i=0; i<Q; i++) {
        int c = Queries[i][0];
        int k = Queries[i][1];

        unordered_map<int,bool> m;
        for(int j=2; j<2+k; j++) {
            m[Queries[i][j] - 1] = true;
        }

        vector<vector<int>> dp(N,vector<int>(c+1,-1));
        int x = f(N-1,c,A,m,dp);
        ans.push_back(x);
    }
    return ans;
}

int main() {
    int n;
    cin>>n;
    vector<int> denom = {1,3,2};
    vector<int> dp(n+1,0);
    int c = coinChangeWays(n,denom,dp);
    cout<<(c+1)/2<<"\n";
    // vector<int> dp(n+1,INT_MAX);

    // cout<<coin(n,denom,dp)<<"\n";

    vector<int> arr = {50,4,10,8,30,100};
    // cout<<longest(arr)<<"\n";
    return 0;
}