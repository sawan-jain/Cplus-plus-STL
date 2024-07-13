// SEGMENT TREE ARE USED TO EFFICIENTLY PROCESS RANGE QUERIES LIKE SUM,MIN,MAX,AND,OR,XOR.
// TC--> O(N + QLOG(N))  N->TREE BUILD  LOG(N)->TIME TO PROCESS 1 QUERY
// SC--> O(N)   

#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod = 1e9 + 7;

class SegmentTree {
private:
    vector<int> tree;
    int n;

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node + 1, start, mid);
            build(arr, 2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    void update(int node, int start, int end, int idx, int value) {
        if (start == end) {
            tree[node] = value;
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(2 * node + 1, start, mid, idx, value);
            } else {
                update(2 * node + 2, mid + 1, end, idx, value);
            }
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return 0;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int leftSum = query(2 * node + 1, start, mid, l, r);
        int rightSum = query(2 * node + 2, mid + 1, end, l, r);
        return leftSum + rightSum;
    }

public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n); // Resize to accommodate a sufficiently large segment tree
        build(arr, 0, 0, n - 1);
    }

    void update(int idx, int value) {
        update(0, 0, n - 1, idx, value);
    }

    int query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }
};

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree segTree(arr);

    cout << "Sum of values in range [1, 3]: " << segTree.query(1, 3) << endl; // Output: 15
    segTree.update(1, 10); // Update value at index 1 to 10
    cout << "Updated sum of values in range [1, 3]: " << segTree.query(1, 3) << endl; // Output: 22

    return 0;
}


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
