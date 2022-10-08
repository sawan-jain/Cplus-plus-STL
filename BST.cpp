#include<iostream>
#include<vector>
using namespace std;

class Node {

public :
    int data;
    Node*left;
    Node*right;

    Node(int d) {
        data=d;
        left=right=NULL;
    }
};

Node* buildBST(Node* root, int key) {
    if(root==NULL) {
        return new Node(key);
    }

    if(key<root->data) {
        root->left = buildBST(root->left,key);
    }
    else {
        root->right = buildBST(root->right,key);
    }
    return root;
}

void printInorder(Node* root) {
    if(root==NULL) {
        return;
    }

    printInorder(root->left);
    cout<<root->data<<",";
    printInorder(root->right);

}

bool search(Node* root, int key) {
    if(root==NULL) {
        return false;
    }
    if(key==root->data) return true;

    if(key<root->data) {
       return search(root->left,key);
    }

    return search(root->right,key);
}

Node* findMin(Node* root) {
    while(root->left!=NULL) {
        root=root->left;
    }
    return root;
}

Node* deletion(Node* root,int key) {

    if(root==NULL) {
        return NULL;
    }

    else if(key<root->data) {
        root->left = deletion(root->left,key);
    }
    
    else if(key>root->data) {
        root->right = deletion(root->right,key);
    }

    else {

        if(root->left==NULL and root->right==NULL) {
            delete root;
            root=NULL;
        }

        else if(root->left==NULL) {
            Node* temp = root;
            delete temp;
            root=root->right;
        }

        else if(root->right==NULL) {
            Node* temp = root;
            delete temp;
            root=root->left;
        }

        else {
            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deletion(root->right,temp->data);
        }

    }

    return root;
}

Node* removal(Node* root) {
    if(root->left==NULL and root->right==NULL) {
        return root;
    }

    else if(root->left==NULL) {
        root->right=removal(root->right);
        Node* temp = root;
        delete temp;
    }

    else if(root->right==NULL){
        root->left = removal(root->left);
        Node* temp = root;
        delete temp;
    }
    
    else {
        root->left = removal(root->left);
        root->right = removal(root->right);
    }

}

Node* mirrorBST(Node* root) {
    if(root==NULL) {
        return NULL;
    }
    
    Node*temp = root->right;
    root->right = root->left;
    root->left = temp;

    mirrorBST(root->left);
    mirrorBST(root->right);

    return root;

}

bool isBST(Node * root){

    if(root->left==NULL and root->right==NULL) {
        return true;
    }

    if(root->data >(root->left)->data){
        return isBST(root->left);
    }
    else return false;
    
    if(root->data <(root->right)->data){
        return isBST(root->right);
    }
    else return false;

}

Node* deleteNode(Node* root, int k) {
    if(root==NULL) {
        return NULL;
    }

    else if(root->data>k) {
        deleteNode(root->left,k);
    }

    else if(root->data<k) {
        deleteNode(root->right);
    }

    else {
        // no child
        if(root->left==NULL and root->right==NULL) {
            delete root;
            root=NULL;
        }

        // 1 children
        else if(root->left==NULL) {
            Node* temp =root;
            delete temp;
            root=root->right;
        }

        else if(root->right==NULL) {
            Node* temp=root;
            delete temp;
            root = root->left;
        }

        // 2 children
        else {
            Node* temp = findMin(root);
            root->data = temp->data;
            root->left = deleteNode(root->left,temp->data);
            
        }
    }

    return root;
}


void printRoot2Leaf(Node* root,vector<int> &path) {
    if(root==NULL) {
        return;
    }

    if(root->left==NULL and root->right==NULL) {
        path.push_back(root->data);
        for(int node:path) {
            cout<<node<<"->";
        }
        cout<<endl;
    }

    // rec case
    path.push_back(root->data);
    printRoot2Leaf(root->left,path);
    printRoot2Leaf(root->right,path);

    // backtracking
    path.pop_back();

}
int main() {
    Node * root = NULL;
    int arr[]={8,3,10,1,6,14,4,7,13};

    for(int x:arr) {
        root = buildBST(root,x);
    }

    printInorder(root);
    cout<<endl;
    cout<<isBST(root);
    //removal(root);
    //deletion(root,d);

    //printInorder(root);
    
    //cout<<search(root,1);
    return 0;
}