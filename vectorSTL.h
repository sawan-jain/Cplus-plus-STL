#include<iostream>
using namespace std;

template<typename T>
class Vector{
    T* arr;
    int ms;
    int cs;

public:
    Vector(int default_maxSize=1) {
        cs=0;
        ms=max_Size;
        arr = new T[ms];
    }

    void push_back(T data) {
        if(cs<ms) {
            arr[cs]=data;
            cs++;
        }
        else {
            cs = 1;
            T* old_arr = arr;
            arr = new T[ms*2];
            for(int i=0; i<ms; i++) {
                arr[i]=old_arr[i];
                cs++;
            }
            ms = ms*2;
            arr[cs] = data;
            delete [] old_arr;
        }
    }

    bool empty() {
        return cs==0;
    }
    
    T* begin() {
        T* ptr = & arr[0];
        return ptr;
    }

    T* end() {
        T* ptr = & arr[cs];
        return ptr;
    }

    void clear() {
        T* old_arr = arr;
        arr = new T[ms];
        delete [] old_arr;
    }

    T front() {
       return arr[0];
    }

    T last() {
        return arr[cs];
    }
    
    void pop_back() {
       if(cs>=0) {
           cs--;
       }
    }

    int size() {
        return cs;
    }

    int capacity() {
        return ms;
    }

    T element(int index) {
        if(index-1<=cs) {
            return arr[index];
        }
    }
};


