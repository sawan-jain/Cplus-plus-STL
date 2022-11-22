#include<iostream>
#include<string>
using namespace std;

template<typename T>
class Node {
public :
    string key;
    T value;
    Node* next;

    Node(string key,T value) {
        this->key = key;
        this->value = value;
        next = NULL;
    }

    ~Node() {
        if(next!=NULL) {
            delete next;
        }
    }
};

template<typename T>
class Hashtable {
    Node<T>** table;                       
    int cs;
    int ts;

    int HashFn(string k) {
        int idx = 0;
        int power = 1;
        for(auto ch:k) {
            idx= (idx + ch*power)%ts;
            power = (power*29)%ts;
        }

        return idx;
    }

    void rehash() {
        cs = 0;
        ts = 2*ts + 1;

        Node<T>** old_table = table;
        table = new Node<T>*[ts];

        for(int i=0; i<ts; i++) {
            table[i]=NULL;
        }
        for(int i=0; i<ts/2; i++) {
            Node<T>* temp = old_table[i];

            while(temp!=NULL) {
                string key = temp->key;
                T value = temp->value;
                insert(key,value);
                temp=temp->next;
            }

            if(old_table[i]!=NULL) {
                delete old_table[i];
            }
        }

        delete [] old_table;
    }

public :
    Hashtable(int default_size=7) {    // default_size taken as prime number to avoid collisions
        cs=0;
        ts = default_size;
        table = new Node<T>*[ts];      

        for(int i=0; i<ts; i++) {
            table[i]=NULL;            // to remove garbage values from the table elemnts
        }
    }

    void insert(string k,T data) {
        int idx = HashFn(k);
        Node<T>* n = new Node<T>(k,data);
        

        n->next = table[idx];
        table[idx] = n;
        cs++;

        float load_factor = cs/float(ts);
        if(load_factor>0.7) {
            rehash();
        }
    }

    bool isPresent(string key) {
        for(int i=0; i<ts; i++) {
            Node<T>* temp = table[i];

            while(temp!=NULL) {
                if(temp->key == key) {
                    return true;
                }
                temp = temp->next;
            }
        }
        return false;
    }

    T* search(string key) {  // T* so that we can return null if key is not present
        if(isPresent(key)) {
            int idx = HashFn(key);
            Node<T>* temp = table[idx];

            while(temp!=NULL) {
                if(temp->key == key){
                    return &temp->value;
                }

                temp=temp->next;
            }

            return NULL;
        }
        else return NULL;
    }

    void erase(string key) {
        int idx = HashFn(key);
        Node<T>* temp1 = table[idx];
        while(temp1!=NULL) {
            if(temp1->key == key) {
                Node<T>* prev = temp1->next;

            }
        }
        
        /*if(temp1->next==NULL) {
            temp2->next=NULL;
        }
        else {
            temp2->next = temp1->next;
            temp1->next = NULL;
        }
        

        cs--;
        delete temp1;*/

    }

    T& operator[](string key) {
        T* valueFound = search(key);
        if(valueFound==NULL) {
           T object;
           insert(key,object);
           valueFound = search(key);
        }

        return *valueFound;
    }

    void print() {
        for(int i=0; i<ts; i++) {
            Node<T>* temp = table[i];
            cout<<"Bucket "<<i<<"-> ";
            while(temp!=NULL) {
                cout<<temp->key<<" ";
                temp=temp->next;
            }
            cout<<endl;
        }
    }
};

