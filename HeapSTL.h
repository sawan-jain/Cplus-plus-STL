#include<iostream>
#include<vector>

using namespace std;

class Heap{
    vector<int> v;
    

    bool compare(int idx, int minIdx,vector<int> in) {
        if(type) {
            return in[idx]<in[minIdx];
        }

        else {
            return in[idx]>in[minIdx];
        }
    }
    void heapify(int i) {
        int left = 2*i;
        int right = 2*i +1 ;
        int minIdx = i;

        if(left<v.size() and compare(left,minIdx,v)) {
            minIdx = left;
        }

        if(right<v.size() and compare(right,minIdx,v)) {
            minIdx = right;
        }

        if(minIdx!=i) {
            swap(v[i],v[minIdx]);
            heapify(minIdx);
        }
    }
public:

    bool type;
    
    Heap(int default_size=10, bool type = true) {
        v.reserve(default_size+1);
        v.push_back(-1);
    }

    void push(int data) {
        v.push_back(data);

        int indx = v.size()-1;
        int parent = indx/2;
        if(type) {
            while(indx>1 and compare(indx,parent,v)) {     
                swap(v[indx],v[parent]);
                indx = parent;
                parent = parent/2;
            } 
        }

        else {
            while(indx>1 and compare(indx,parent,v)) {     
                swap(v[indx],v[parent]);
                indx = parent;
                parent = parent/2;
            } 
        }
        
    }

    int getMin() {                               // for min heap
        return v[1];
    }

    void pop() {
        swap(v[1],v[v.size()-1]);
        v.pop_back();
        heapify(1);
    }

    vector<int> returnHeap() {
        return v;
    }
    
};