// SEGMENT TREE ARE USED TO EFFICIENTLY PROCESS RANGE QUERIES LIKE SUM,MIN,MAX,AND,OR,XOR.
// TC--> O(N + QLOG(N))  N->TREE BUILD  LOG(N)->TIME TO PROCESS 1 QUERY
// SC--> O(N)   

#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod = 1e9 + 7;

// AN ARRAY WITH N VALUES CAN HAVE ATMOST 4N NODES IN ITS SEGMENT TREE 
vector<ll> v(100000);
vector<ll> segment(4*(100000));

// lazy array to keep track of changes
vector<ll> lazyUpdate(4*(200000),0);

void build(int ind,int low,int high) {
    //base case
    if(low == high) {
        segment[ind] = v[low];
        return;
    }

    //rec case
    int mid = (low+high)/2;
    build(2*ind+1,low,mid);
    build(2*ind+2,mid+1,high);
    segment[ind] = min(segment[2*ind+1],segment[2*ind+2]);   // change this statement according to problem
}

void update(int ind,int low,int high,int l,int r,int change) {
    if(low>high) return;

    // check if any update is pending at current node
    // if yes update the node value and propogate the value to its children
    if(lazyUpdate[ind]!=0) {
        segment[ind] += lazyUpdate[ind];

        // if node is not leaf node
        if(low != high) {
            lazyUpdate[2*ind + 1] += lazyUpdate[ind];
            lazyUpdate[2*ind+2] += lazyUpdate[ind];
        }
        lazyUpdate[ind] = 0;
    }

    // no overlap
    if(l>high || r<low) return;

    // complete overlap
    if(low>=l && high<=r) {
        segment[ind] += change;
        if(low != high) {
            lazyUpdate[2*ind + 1] += change;
            lazyUpdate[2*ind+2] += change;
        }
        return;
    }

    // partial overlap
    int mid = (low+high)/2;
    update(2*ind+1,low,mid,l,r,change);
    update(2*ind+2,mid+1,high,l,r,change);

    segment[ind] = min(segment[2*ind+1],segment[2*ind+2]); // change this statement according to problem
}

int query(int ind,int low,int high,int l,int r) {
    if(low>=l && high<=r) return segment[ind];
    if(high<l || low>r) return INT_MAX;   // change this statement according to problem

    int mid = (low+high)/2;
    int left = query(2*ind+1,low,mid,l,r);
    int right = query(2*ind+2,mid+1,high,l,r);

    return min(left,right);
}

int main() {
    
    int n,q;
    cin>>n>>q;    
    for(int i=0; i<n; i++) cin>>v[i];
    build(0,0,n-1);
    
    while(q--) {
        int k,a,b;
        cin>>k>>a>>b;
        if(k == 1) {
            update(0,0,n-1,a-1,a-1,b-v[a-1]);
        }

        else cout<<query(0,0,n-1,a-1,b-1)<<"\n";
    }
    
    return 0;
}
