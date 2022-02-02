// QUEUE STL 
// implementing QUEUE data-structure using Linked Lists 

#include<iostream>
using namespace std;

template<typename T1>
class Node {
    T1 data;

public :
    Node<T1>* next;
    Node(T1 d):data(d),next(NULL) {}  
    
    T1 get_data() {   
        return data;
    }

};

template<typename T2>
class Queue{
    Node<T2>* head;
    Node<T2>* tail;

public :
    Queue():head(NULL),tail(NULL) {}

    Node<T2>* get_head() {
        return head;
    }

    bool empty() {
        return head==NULL;
    }

    void front() {                  // prints the first element of the queue
        if(head==NULL) {
            cout<<"queue empty"<<endl;
        }

        else {
            cout<<head->get_data()<<endl;
        }
    }

     void pop() {                    // deletes the first element of the queue
        if(head==NULL) {
            cout<<"queue empty"<<endl;
        }
        else {
            Node<T2>* temp=head;
            head=head->next;
            temp->next=NULL;

            // to prevent memory leak
            delete [] temp;          
        }
    }

    void push(int data) {               // pushes data at end of queue
        if(head==NULL) {
            Node<T2>* n = new Node<T2>(data);
            head=tail=n;
        }

        else {
            Node<T2>* n = new Node<T2>(data);
            tail->next=n;
            tail=n;
        }
    }

    int size() {
        Node<T2>* temp = head;
        int size=0;
        while(temp!=NULL) {
            size++;
            temp=temp->next;
        }

        return size;
    }

   

    
};