#include<bits/stdc++.h>
using namespace std;

const int SIZE=10;

class Node{
    public:
    int roll;
    int marks;
    Node *next;

    Node(int r,int m){
        roll=r;
        marks=m;
        next=NULL;
    }
};

// struct Node{
//     int data;
//     Node* left,*right;
// };

struct student{
    int roll;
    int marks;
    bool occupy;
    Node* chain;
    student(){
        roll=-1;
        marks=0;
        occupy=false;
        chain=NULL;
    }
};

student table[SIZE];

int hashfn(int key){
    return key%SIZE;
}

void insert(int roll,int marks){
    int index=hashfn(roll);
    if(!table[index].occupy){
        table[index].roll=roll;
        table[index].marks=marks;
        table[index].occupy=true;
    }
    else{
        int oindex=index;
        int i=(index+1)%SIZE;
        while(i!=oindex && table[i].occupy){
            i=(i+1)%SIZE;
        }
        if(table[i].occupy){
            cout<<"full"<<endl;
            return;
        }
        table[i].roll=roll;
        table[i].marks=marks;
        table[i].occupy=true;

        Node* newN=new Node(roll,marks);
        newN->next=table[oindex].chain;
        table[oindex].chain=newN;
    }
}

void display(){
    cout<<"Hash table:"<<endl;
    for(int i=0;i<SIZE;i++){
        if(table[i].occupy){
            cout<<"["<<table[i].roll<<","<<table[i].marks<<"]";
        }
        else{
            cout<<"empty";
        }
    
            
        Node* temp=table[i].chain;
        while(temp){
            cout<<"-> ["<<temp->roll<<","<<temp->marks<<"]";
            temp=temp->next;
        }    
    cout<<endl;
    }
}

void search(int roll){
    int index=hashfn(roll);
    if(table[index].occupy && table[index].roll==roll){
        cout<<"found"<<endl;
        return;
    }
    Node* temp=table[index].chain;
    while(temp){
        if(temp->roll==roll){
            cout<<"found"<<endl;
            return;
        }
        temp=temp->next;
    }
    cout<<"mot found"<<endl;
}

int main() {
    int choice;
    while (true) {
        cout << "\n===== Menu =====" << endl;
        cout << "1. Insert student" << endl;
        cout << "2. Search student by roll number" << endl;
        cout << "3. Display hash table" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int roll, marks;
            cout << "Enter roll number: ";
            cin >> roll;
            cout << "Enter marks: ";
            cin >> marks;
            insert(roll, marks);
        }
        else if (choice == 2) {
            int roll;
            cout << "Enter roll number to search: ";
            cin >> roll;
            search(roll);
        }
        else if (choice == 3) {
            display();
        }
        else if (choice == 4) {
            cout << "Exiting program." << endl;
            break;
        }
        else {
            cout << "Invalid choice! Try again." << endl;
        }
    }

    return 0;
}
