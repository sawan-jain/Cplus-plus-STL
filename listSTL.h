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
class List{
    Node<T2>* head;
    Node<T2>* tail;

public: 
    List():head(NULL),tail(NULL){}

    Node<T2>* begin() {
        return head;
    }

    int length() {
        Node<T2>* t1=head;
        int count=0;
        while(t1!=NULL) {
            count++;
            t1=t1->next;
        }

        return count;
    }

    void push_front(T2 data) {
        if(head==NULL) {
            Node<T2>* n = new Node<T2>(data);
            head=tail=n;
        }
        else {
            Node<T2>* n = new Node<T2>(data);
            n->next=head;
            head=n;
        }
    }

    void push_back(T2 data) {
        if(tail==NULL) {
            Node<T2>* n = new Node<T2>(data);
            head=tail=n;
        }
        else {
            Node<T2>* n= new Node<T2>(data);
            tail->next=n;
            tail=n;
        }
    }

    void insert(T2 data,int pos) {
        if(pos==0) {
            push_front(data);
        }
        else {
            Node<T2>* temp = head;
            for(int i=1; i<pos; i++) {
                temp=temp->next;
            }
            Node<T2>* n =new Node<T2>(data);
            n->next=temp->next;
            temp->next=n;
        }
    }


    void deletion(int index) {
    
        if(index==0) {
            Node<T2>* temp=head;
            head=head->next;
            temp->next=NULL;
            delete temp;
        }

        else {
            Node<T2>* t1=head;
            Node<T2>* t2=head;
            for(int i=0; i<index-1; i++) {
                t1= t1->next;
            }
            for(int i=0; i<index; i++) {
                t2= t2->next;
            }
            t1->next=t2->next;
            t2->next=NULL;
            delete t2;
        }
    }

    void reverse() {
        Node<T2>* t1=head;              
        int count=0;
        while(t1!=NULL) {
            count++;
            t1=t1->next;
        }

        Node<T2>* n=head;
        Node<T2>* m=tail;
        for(int i=0; i<count; i++) {
            m->next = n;
            n = n->next;
        }
        n=n->next;
    }
};
