#include<iostream>
using namespace std;

class List;

class Node {
    int data;

public :
    Node* next;Node* tail;

    Node(int d):data(d),next(NULL){}

    int get_data() {
        return data;
    }
    friend class List;
};

class List{
    Node* head;
    Node* tail;

public: 
    List():head(NULL),tail(NULL){}

    Node* begin() {
        return head;
    }

    int length() {
        Node* t1=head;
        int count=0;
        while(t1!=NULL) {
            count++;
            t1=t1->next;
        }

        return count;
    }

    void push_front(int data) {
        if(head==NULL) {
            Node* n = new Node(data);
            head=tail=n;
        }
        else {
            Node* n = new Node(data);
            n->next=head;
            head=n;
        }
    }

    void push_back(int data) {
        if(tail==NULL) {
            Node* n=new Node(data);
            head=tail=n;
        }
        else {
            Node* n= new Node(data);
            tail->next=n;
            tail=n;
        }
    }

    void insert(int data,int pos) {
        if(pos==0) {
            push_front(data);
        }
        else {
            Node* temp=head;
            for(int i=1; i<pos; i++) {
                temp=temp->next;
            }
            Node* n =new Node(data);
            n->next=temp->next;
            temp->next=n;
        }
    }


    void deletion(int index) {
    
        if(index==0) {
            Node* temp=head;
            head=head->next;
            temp->next=NULL;
            delete temp;
        }

        else {
            Node* t1=head;
            Node* t2=head;
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
        Node* t1=head;              
        int count=0;
        while(t1!=NULL) {
            count++;
            t1=t1->next;
        }

        Node* n=head;
        Node* m=tail;
        for(int i=0; i<count; i++) {
            m->next = n;
            n = n->next;
        }
        n=n->next;
    }


};
