#include<bits/stdc++.h>
using namespace std;
#define ll long long

// preprocessing work for string hashing to find hash value of substring in O(1) time
// both these arrays take O(N) time in building

int prefixSumString(string s, int n, vector<int> &h, int A, int B) {
    if(n == 0) {
        h[0] = s[0];
        return h[0];
    }

    return h[n-1] = (prefixSumString(s,n-1,h,A,B)*A+ s[n-1])%B;    
}

int prefixSumPreprocessing(vector<int> &rho, int n, int A, int B) {
    if(n == 0) {
        rho[0] = 1;
        return 1;
    }

    return rho[n-1] = (prefixSumPreprocessing(rho,n-1,A,B)*A)%B ;
}

int hashValueSubstring(vector<int>h, vector<int> rho, int s, int e, int B) {
    if(s == 0) return h[e];

    return (h[e] - h[s-1]*rho[e-s+1])%B;
}

int main() {
    int n;
    cin>>n;
    string s;
    cin>>s;
    vector<int> h(s.length(),0);
    int A = 29, B = 31;
    prefixSumString(s,n,h,A,B); 
    for(int x : h) cout<<x<<" ";
    vector<int> rho(n,0);
    prefixSumPreprocessing(rho,n,A,B);
    return 0;
}