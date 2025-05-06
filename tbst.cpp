#include<bits/stdc++.h>
using namespace std;
struct Node{
    int data;
    Node* left,*right;
    bool lthread,rthread;
};

Node* create(int data){
    Node* temp=new Node;
    temp->data=data;
    temp->left=temp->right=NULL;
    temp->lthread=temp->rthread=true;
    return temp;
}

Node* insert(Node* root, int key){
    Node* temp= root;
    Node* parent=NULL;
    while(temp!=NULL){
        if(key==temp->data){
            cout<<"NO duplicates";
            return root;
        }
        parent=temp;
        if(key<temp->data){
            if(!temp->lthread) temp=temp->left;
            else break;
        }

        else{
            if(!temp->rthread) temp=temp->right;
            else break;
        }
    }
    Node* newN=create(key);
    if(parent==NULL) root=newN;
    else if(parent->data>key){
        newN->left=parent->left;
        newN->right=parent;
        parent->left=newN;
        parent->lthread=false;
    }
    else{
        newN->right=parent->right;
        newN->left=parent;
        parent->right=newN;
        parent->rthread=false;
    }
    return root;
}

Node* left(Node* node){
    if(node==NULL) return NULL;
    while(!node->lthread){
        node=node->left;
    }
    return node;
}

void inorder(Node* root){
    Node* temp=left(root);
    while(temp!=NULL){
        cout<<temp->data<<" ";
        if(temp->rthread){
            temp=temp->right;
        }
        else{
            temp=left(temp->right);
        }
    }
}

int main(){
    int n,val;
    Node* root=NULL;
    cout<<"Enter number of node: ";
    cin>>n;
    cout<<endl;
    cout<<"Enter values: ";
    for(int i=0;i<n;i++){
        cin>>val;
        root=insert(root,val);
    }
    cout<<endl;
    cout<<"Inorder traversal: ";
    inorder(root);
    cout<<endl;
    return 0;
}