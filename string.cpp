#include<bits/stdc++.h>
using namespace std;
class HTable{
    private:
    vector<list<string>> table;
    int hashfn(const string& word){
        int hash=0;
        int i=0;
        int n=word.size();
        for(char c:word){
            hash+=int(c)*pow(10,n-i-1);
            i++;
        }
        return hash%table.size();
    }

    public:
    HTable(int size){
        table.resize(size);
    }

    void insert(const string& word){
        int index=hashfn(word);
        table[index].push_back(word);
    }

    bool search(const string& word){
        int index=hashfn(word);
        for(const string& w:table[index]){
            if(w==word) return true;
        }
        return false;
    }

    void display(){
        for(int i=0;i<table.size();i++){
            for(const string& word:table[i]){
                cout<<word<<"->";
            }
            cout<<"NULL"<<endl;
        }
    }
};

int main(){
    HTable hash(10);
    cout<<"Enter 20 words spelled correctly:"<<endl;
    for(int i=0;i<20;i++){
        string word;
        cin>>word;
        hash.insert(word);
    }
    int ch;
    string check;
    while(true){
        cout<<"1.Check spelling"<<endl;
        cout<<"2.Display"<<endl;
        cout<<"3.Exit"<<endl;
        cout<<"Enter your choice:"; cin>>ch;
        switch(ch){
            case 1:
            cout<<"Enter word to check:"; cin>>check;
            if(hash.search(check)){
                cout<<"correct spelled"<<endl;
            }
            else cout<<"incorrect"<<endl;
            break;

            case 2:
            hash.display();
            break;

            case 3:
            cout<<"Exiting!"<<endl;
            break;

            default:
            cout<<"Invalid choice! Try again.."<<endl;
        }
    }
}