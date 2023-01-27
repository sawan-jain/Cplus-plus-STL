#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod = 1e9 + 7;

vector<ll> v(100000);
vector<ll> segment(4*(100000));

// AN ARRAY WITH N VALUES CAN HAVE ATMOST 4N NODES IN ITS SEGMENT TREE 

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
    segment[ind] = min(segment[2*ind+1],segment[2*ind+2]);
}

int query(int ind,int low,int high,int l,int r) {
    if(low>=l && high<=r) return segment[ind];
    if(high<l || low>r) return INT_MAX;

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
        int a,b;
        cin>>a>>b;
        cout<<query(0,0,n-1,a-1,b-1)<<"\n";
    }    
    return 0;
}
