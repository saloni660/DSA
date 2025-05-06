#include<bits/stdc++.h>
using namespace std;
class node{
    public:
    int data;
    node *left;
    node *right;

    node(){
        data=0;
        left=NULL;
        right=NULL;
    }
};

class tree : public node{
    node* root;
    public:
    tree() {
        root=NULL;
    }
    node* return_root(){
        return root;
    }
    int return_root_data(){
        return root->data;
    }
    void insert_it(int key);
    void preorder_rec(node* root);
    void inorder_rec(node* root);
    void postorder_rec(node* root);
    void preorder_it(node* root);
    void inorder_it(node* root);
    void postorder_it(node* root);
    void level();
    node* clone(node* root);
    node* mirror(node* root);
    int height(node* root);
    int no_node(node* root);
    node* build(int preorder[],int inorder[],int instart,int inend,int& pre);
    int index(int inorder[],int instart,int inend,int value);
};

void tree::insert_it(int key){
    if(root==NULL){
        root=new node;
        root->data=key;
        root->left=NULL;
        root->right=NULL;
        cout<<"inserted";
        return;
    }
    node* temp=root;
    while(true){
        if(temp->data==key){
            cout<<"no duplicates"<<endl;
            return;
        }
        else if(temp->data>key){
            if(temp->left==NULL){
                temp->left=new node;
                temp->left->data=key;
                break;
            }
            else temp=temp->left;
        }
        else{
            if(temp->right==NULL){
                temp->right=new node;
                temp->right->data=key;
                break;
            }
            else temp=temp->right;
        }
    }
    cout<<"insertes"<<endl;
}

void tree::preorder_rec(node* root){
    if(root==NULL) return;
    cout<<root->data<<" ";
    preorder_rec(root->left);
    preorder_rec(root->right);
}

void tree::inorder_rec(node* root){
    if(root==NULL) return;
    inorder_rec(root->left);
    cout<<root->data<<" ";
    inorder_rec(root->right);
}

void tree::postorder_rec(node* root){
    if(root==NULL) return;
    postorder_rec(root->left);
    postorder_rec(root->right);
    cout<<root->data<<" ";
}

void tree::preorder_it(node* root){
    stack<node*> s;
    node* temp=root;
    do
    {
        while(temp!=NULL){
            cout<<temp->data;
            s.push(temp);
            temp=temp->left;
        }
        temp=s.top();
        s.pop();
        temp=temp->right;
    } while (temp!=NULL ||s.size()!=0);
}

void tree::inorder_it(node* root){
    stack<node*> s;
    node* temp=root;
    do
    {
        while(temp!=NULL){
            s.push(temp);
            temp=temp->left;
        }
        temp=s.top();
        s.pop();
        cout<<temp->data<<" ";
        temp=temp->right;
    } while (temp!=NULL || s.size()!=0);
}

void tree::postorder_it(node* root){
    stack<node*> s1,s2;
    node* temp=NULL;
    s1.push(root);
    while(s1.size()!=0){
        temp=s1.top();
        s1.pop();
        s2.push(temp);
        if(temp->left!=NULL) s1.push(temp->left);
        if(temp->right!=NULL) s1.push(temp->right);
    }
    while(s2.size()!=0){
        temp=s2.top();
        s2.pop();
        cout<<temp->data<<" ";
    }
}

void tree::level(){
    queue<node*> q;
    q.push(root);
    while(q.size()!=0){
        node* temp=q.front();
        q.pop();
        cout<<temp->data<<" ";
        if(temp->left!=NULL) q.push(temp->left);
        if(temp->right!=NULL) q.push(temp->right);
    }
}

int tree::height(node* root){
    if(root==NULL) return 0;
    return 1+max(height(root->left),height(root->right));
}

int tree::no_node(node* root){
    if(root==NULL) return 0;
    return 1+no_node(root->left)+no_node(root->right);
}

node* tree::clone(node* root){
    if(root==NULL) return NULL;
    node* temp=new node;
    temp->data=root->data;
    temp->left=clone(root->left);
    temp->right=clone(root->right);
    return temp;
}

node* tree::mirror(node* root){
    if(root==NULL) return NULL;
    node* temp=new node;
    temp->data=root->data;
    temp->left=clone(root->right);
    temp->right=clone(root->left);
    return temp;
}

int tree::index(int inorder[],int instart,int inend,int value){
    for(int i=instart;i<=inend;i++){
        if(inorder[i]==value) return i;
    }
    return -1;
}
node* tree::build(int preorder[],int inorder[],int instart,int inend,int& pre){
    if(instart>inend){
        return nullptr;
    }
    int current=preorder[pre++];
    node* temp=new node;
    temp->data=current;
    if(instart==inend) return temp;

    int indexi=index(inorder,instart,inend,current);
    temp->left=build(preorder,inorder,instart,indexi-1,pre);
    temp->right=build(preorder,inorder,indexi+1,inend,pre);
    return temp;
}

int main(){
    tree t;
    int ch;
    do
    {
        cout<<"MENU";
        cout<<"ENter your choice:";
        cin>>ch;
        switch(ch){
            case 1:{
                int key;
                cout << "\t Enter the value to Insert :: ";
                cin >> key;
                t.insert_it(key);
            }
            break;
            case 2:{
                int traversal_choice = 0;
                cout << "\n\t 1. PreOrder \t 2. InOrder \t 3. PostOrder \t 4. LevelOrder";
                cout << "\n\t Enter Your Choice :: ";
                cin >> traversal_choice;
                switch (traversal_choice){
                    case 1:
                    cout << " -------------- PRE-ORDER TRAVERSAL ---------------- \n\t";
                    cout << " ITERATIVE :: ";
                    t.preorder_it(t.return_root());
                    cout << "\n\t RECURSIVE :: ";
                    t.preorder_rec(t.return_root());
                    cout << endl;
                    break;
                    case 2:
                    cout << " -------------- IN-ORDER TRAVERSAL ---------------- \n\t";
                    cout << " ITERATIVE :: ";
                    t.inorder_it(t.return_root());
                    cout << "\n\t RECURSIVE :: ";
                    t.inorder_rec(t.return_root());
                    cout << endl;
                    break;
                    case 3:
                    cout << " -------------- POST-ORDER TRAVERSAL ---------------- \n\t";
                    cout << " ITERATIVE :: ";
                    t.postorder_it(t.return_root());
                    cout << "\n\t RECURSIVE :: ";
                    t.postorder_rec(t.return_root());
                    cout << endl;
                    break;
                    case 4:
                    cout << " -------------- LEVEL-ORDER TRAVERSAL ---------------- \n\t";
                    t.level();
                    cout << endl;
                    break;
                    default:
                    cout << "\n No Such Choice!!";
                    break;
                }
            }
            break;

        }
    } while (ch!=10);
    
    
    
}



