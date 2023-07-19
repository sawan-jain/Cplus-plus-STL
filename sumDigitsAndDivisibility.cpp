// Problem Statement: We have 3 positive integers A,B,K ,
// for each case output the number of numbers btw [A,B] which are divisible by K and 
// sum of their digits is also divisible by K 

#include<bits/stdc++.h>
#define int long long
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;

string n;
int a,b,k;
// int dp[10][2][k][k];

// sum_mod: to find the number mod k
// sum_mod_dig: to find sum of digits mod k
int f(int ind,bool tight,int sum_mod,int sum_mod_dig) {
    // base case
    if(ind == n.length()) {
        if(sum_mod == 0 && sum_mod_dig == 0) return 1;
        return 0;
    }

    //rec case
    int ub = (tight? n[ind]-'0' : 9);
    int ans = 0;
    for(int i=0; i<=ub; i++) {
        ans += f(ind+1,(tight && (i == ub)),
                (sum_mod*10 + i)%k, (sum_mod_dig+i)%k);
    }

    return ans;
}

void solution() {
    cin>>a>>b>>k;

    n = to_string(b);
    int b1 = f(0,true,0,0);

    n = to_string(a-1);
    int a1 = f(0,true,0,0);

    cout<<b1-a1<<"\n";
}

int32_t main() {
    fast_io;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    int t;
    cin>>t;
    while(t--) solution();
    return 0;
}

