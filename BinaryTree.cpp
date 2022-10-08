#include<iostream>
#include<queue>
#include<stack>
using namespace std;


class Node {
    
public:
    int data;
    Node* left;
    Node* right;
    Node(int d) {
        data=d;
        left=right=NULL;
    }
};

Node* buildTree() {
    int d;
    cin>>d;

    if(d==-1) {
        return NULL;
    }

    Node* n = new Node(d);
    n->left=buildTree();
    n->right=buildTree();

    return n;
}


/*Node* levelOrderBuild() {

    int d;
    cin>>d;                // 1 2 4 -1 -1 5 7 -1 -1 -1 3 -1 6 -1 -1;
    int c1,c2;
    cin>>c1>>c2;

    if(c1!=-1) {
        current->left= new Node(c1);
        q.push(current->left);
    }

    if(c2!=-1) {
        current->right= new Node(c2);
        q.push(current->right);
    }

    return root;
}*/

void preOrderTraversal(Node* root) {     // order: root,left,right

    if(root==NULL) {
        return;
    }

    cout<<root->data<<" ";
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

void InOrderTraversal(Node* root) {     // order : left,root,right
    if(root==NULL) {
        return;
    }

    InOrderTraversal(root->left);
    cout<<root->data<<" ";
    InOrderTraversal(root->right);
}

void postOrderTraversal(Node* root) {  // order : left,right,root
    if(root==NULL) {
        return;
    }

    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    cout<<root->data<<" ";
}

void levelOrderPrint(Node* root) {
    queue<Node*> order;
    order.push(root);
    order.push(NULL);

    while(!order.empty()) {
        Node* temp = order.front();
        if(temp==NULL) {
            cout<<endl;
            order.pop();
            if(!order.empty()) {
                order.push(NULL);
            }
        }

        else {
            order.pop();
            cout<<temp->data<<" ";
            if(temp->left) {
                order.push(temp->left);
            }
            if(temp->right) {
                order.push(temp->right);
            }
        }
    }
    return;
}

int height(Node* root) {
    if(root==NULL) {
        return 0;
    }

    int h1 = height(root->left);
    int h2 = height(root->right);

    return max(h1,h2)+1;
}

int sumBT(Node* root) {
    if(root==NULL) {
        return 0;
    }

    int l = sumBT(root->left);
    int r = sumBT(root->right);

    return l+r+(root->data);
}

int treeDiameter(Node* root) {
    if(root==NULL) {
        return 0;
    }

    int d1 = height(root->left) + height(root->right);
    int d2= treeDiameter(root->left);
    int d3 = treeDiameter(root->right);

    return max(d1,max(d2,d3));
    
}


int evalTree(Node* root) {

    if(root==NULL) {
        return 0;
    }

    int l = evalTree(root->left);
    int r = evalTree(root->right);

    if(root->data=='+') return l+r;
    else if(root->data=='-') return l-r;
    else if(root->data=='*') return l*r;
    else  return l/r;
}

void root2Leaf(Node* root,vector<int> &path,int targetSum) {
    if(root==NULL) {
        return;
    }

    if(root->left==NULL and root->right==NULL) {
        int s=0;
        for(int node:path) s+=node;
        if(s==targetSum) {
            for(int x:path) cout<<x<<" ";
        }
        
        while(path.size()>0) {
            path.pop_back();
        }
        return;
    }

    path.push_back(root->data);
    root2Leaf(root->left,path,targetSum);
    root2Leaf(root->right,path,targetSum);
}

vector<vector<int>> pathSum(Node* root, int targetSum){
    vector<int> p1;
    vector<vector<int>> out;

    root2Leaf(root,p1,targetSum);
    out.push_back(p1);
    return out;
    
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

Node* mirrorTree(Node* root) {
    if(root==NULL) {
        return NULL;
    }
    
    Node*temp = root->right;
    root->right = root->left;
    root->left = temp;

    mirrorTree(root->left);
    mirrorTree(root->right);

    return root;

}

void Kthlevel(Node* root,int i,int k) {
    if(root==NULL) return;
    if(i==k) {
        cout<<root->data<<" ";
        return;
    }

    Kthlevel(root->left,i+1,k);
    Kthlevel(root->right,i+1,k);

}

int main() {
    Node* root = buildTree();
    /*preOrderTraversal(root);
    cout<<endl;
    InOrderTraversal(root);
    cout<<endl;
    postOrderTraversal(root);
    cout<<endl;
    levelOrderPrint(root);
    cout<<endl;
    //cout<<height(root);
    cout<<sumBT(root)<<endl;

    cout<<isBST(root)<<endl;

    mirrorTree(root);
    InOrderTraversal(root);
    cout<<endl;

    Kthlevel(root,0,3);*/

    InOrderTraversal(root);


    return 0; 
}

