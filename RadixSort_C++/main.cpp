#include <iostream>
#include <fstream>
using namespace std;

class Node{
    
public:
    Node *next;
    string data;
    Node(string newdata){
        next=NULL;
        data=newdata;
    }
    ~Node(){
        delete next;
    }
};

class linkedStack{
    Node *top;
    int size;
public:
    linkedStack(){
        top=NULL;
        size=0;
    }
    
    void push(Node *newNode){
        newNode->next=top;
        top=newNode;
        size++;
    }
    
    string pop(){
        if(size!=0){
            size--;
            
            string returnData;
            Node *currentTop=top;
            top=top->next;
            currentTop->next=NULL;
            returnData= currentTop->data;
            delete currentTop;
            return returnData;
        }
        return NULL;
    }
    void print(){
        Node *p=top;
        while(p!=NULL){
            
            cout<<p->data<<endl;
            p=p->next;
        }
    }
    
};
int main(int argc, const char * argv[]) {
    
    ifstream infile;
    ofstream outfile;
    int maxData;
    if(argc<2){
        cout<<"invalid arguments for input";
        return 0;
    }
    
    infile.open(argv[1]);
    outfile.open(argv[2]);
    linkedStack stack;
    string input;
    infile>>input;
    maxData=atoi(input.c_str());
    Node *newNode=new Node(input);
    stack.push(newNode);
    while(infile>>input){
        int currNum=atoi(input.c_str());
        if(currNum>maxData){
            maxData=currNum;
        }
        Node *newNode=new Node(input);
        stack.push(newNode);
    }
    stack.print();
    cout<<"The maximum data is "<<maxData;
    
    return 0;
}
