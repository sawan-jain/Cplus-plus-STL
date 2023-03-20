#include<bits/stdc++.h>
#define int long long
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;

class DSU {
    vector<int> size;
    vector<int> parent;
public:
    DSU(int n) {
        size.resize(n);
        parent.resize(n);

        for(int i=0; i<n; i++) size[i] = 1;
        for(int i=0; i<n; i++) parent[i] = i;
    }

    // return the ultimate parent or representative of the set 
    // works in O(log n) time instead use recusrion to find the representative of set
    // and store it directly in above nodes therefore ither values can be obtained in 
    // O(1) time.
    int find(int x) {
        // logn method
        // while(x != parent[x]) x = parent[x];
        // return x;  

        if(x == parent[x]) return x;
        return parent[x] = find(parent[x]);
    }

    // checks whether the 2 elements belong to the same set or not
    bool same(int a,int b) {
        return (find(a) == find(b));
    }

    // union fn to join the 2 sets according to size
    void unite(int a,int b) {
        a = find(a);  
        b = find(b);
    
        if(size[a] < size[b]) swap(a,b);
        size[a] += size[b];
        parent[b] = a;
    }
};

int32_t main() {
    fast_io;
    DSU ds(8);
    
    return 0;
}

