#include<bits/stdc++.h>
#define int long long
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;

// basic helper function to start with digit dp
// this function just helps us to print all the numbers from [0....num]
// "tight" variable is used to put limit on the number , initially it is "True"

void f(int ind,bool tight,string num,string ans) {
    // base case
    if(ind == num.length()) {
        cout<<ans<<'\n';
        return;
    }

    // rec case
    int ub = (tight? num[ind]-'0' : 9); // ub: upper bound on digit
    for(int i=0; i<=ub; i++) {
        f(ind+1,(tight && (i == ub)),num,(ans+to_string(i)));
    }
}

int32_t main() {
    fast_io;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif

    int t;
    cin>>t;
    while(t--) {
        string num;
        cin >> num;
        f(0,true,num,"");
    }
    return 0;
}

