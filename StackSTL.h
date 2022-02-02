#include<iostream>
using namespace std;

template<typename T1>
class Node {
    T1 data;
public :
    Node<T1>* next;
    Node(T1 d):data(d),next(NULL){} 

    T1 get_data() {
        return data;
    }
};

template<typename T2>
class Stack {
    Node<T2>* head;
    Node<T2>* tail;

public :
    Stack():head(NULL),tail(NULL){}

    void push(T2 data) {
        if(head==NULL) {
            Node<T2>* n= new Node<T2>(data);
            n->next=head;
            head=tail=n;
        }
        else {
            Node<T2>* n= new Node<T2>(data);
            n->next=head;
            head=n;
        }
    }

    void pop() {
        if(head==NULL) {
            cout<<"stack empty"<<endl;
        }
        Node<T2>* temp=head;
        head=head->next;
        temp->next=NULL;
        delete [] temp; 
    }

    void top() {
        if(head==NULL) {
            return;
        }
        cout<<head->get_data()<<endl;
    }
};