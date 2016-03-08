
#include <iostream>
#include <fstream>
using namespace std;

class graphNode{
public:
    int nodeID;
    graphNode* nextNode;
    
    graphNode(int id){
        nodeID=id;
        nextNode=NULL;
    }
    
    ~graphNode(){
        delete nextNode;
    }
    
    void insertNode(graphNode *dummy, graphNode * newNode){
        newNode->nextNode=dummy->nextNode;
        dummy->nextNode=newNode;
    }
    bool isEmpty(graphNode *dummy){
        return dummy->nextNode==NULL;
    }
    
    graphNode deleteNode(graphNode *dummy){
        graphNode *deleted = dummy->nextNode;
        dummy->nextNode=dummy->nextNode->nextNode;
        deleted->nextNode=NULL;
        return *deleted;
    }
};

class edgeNode{
public:
    int Ni, Nj, edgeCost;
    edgeNode* nextEdge;
    
    edgeNode(int ni, int nj, int cost){
        Ni=ni;
        Nj=nj;
        edgeCost=cost;
        nextEdge=NULL;
    }
    ~edgeNode(){
        delete nextEdge;
    }
   
    void printEdgeNode(){
        cout<<Ni<<" "<<Nj<<" "<<edgeCost<<endl;
    }
    
    void insertEdge(edgeNode* dummy, edgeNode* newNode){
        newNode->nextEdge=dummy->nextEdge;
        dummy->nextEdge=newNode;
        
    }
    
    edgeNode deleteEdge(edgeNode* dummy){
        edgeNode *deleteNode=dummy->nextEdge;
        dummy->nextEdge=deleteNode->nextEdge;
        deleteNode->nextEdge=NULL;
        return *deleteNode;
    }
};


class PrimMST{
public:
    int N, k;
    int totalCost;
    int * graphNodeIDArray;
    edgeNode *q;
    graphNode * newGraphNode;
    graphNode *g;
    edgeNode *dummy = new edgeNode(-9999,-9999,-9999);
    graphNode *aDummy = new graphNode(-9999);
    graphNode *bDummy = new graphNode(-9999);
    edgeNode *mstDummy = new edgeNode(-9999,-9999,-9999);
    
    PrimMST(int n, ifstream & infile, ofstream & outfile1, ofstream & outfile2){
        N=n;
        //Dynamically allocate 1D array
        graphNodeIDArray = new int[N];
        for(int i=0; i<N; i++){
            graphNodeIDArray[i]=0;
        }
        
        totalCost=0;
        int inputData;
        while(infile>>inputData){
            int ni=inputData;
            int nj;
            infile>>nj;
            int cost;
            infile>>cost;
            edgeNode * newEdgeNode= new edgeNode(ni, nj, cost) ;
     
            edgeNode *p=dummy;
            while(p->nextEdge!=NULL && newEdgeNode->edgeCost>p->nextEdge->edgeCost){
                p=p->nextEdge;
            }
            newEdgeNode->nextEdge=p->nextEdge;
            p->nextEdge=newEdgeNode;
            
            graphNodeIDArray[ni-1]++;
            graphNodeIDArray[nj-1]++;

        }
        
        //Printing graphNodeID array
        outfile2<<"Graph Node ID array:"<<endl;
        for(int i=0; i<N; i++){
            outfile2<<graphNodeIDArray[i]<<", ";
        }
        
         //printing edgeList
        outfile2<<endl<<endl<<"Printing edgeList:"<<endl;
        q=dummy->nextEdge;
        
        for(int i=0; q!=NULL && i<10; i++){
            outfile2<<q->Ni<<" "<<q->Nj<<" "<<q->edgeCost<<endl;
            q=q->nextEdge;
        }
         
        //find first non-zero node
        
        int i=0;
        while(graphNodeIDArray[i]==0){
            i++;
        }
        k=i;
        newGraphNode= new graphNode(k+1);
        aDummy->nextNode=newGraphNode;
        
        for(int i=k+1; i<N; i++){
            if(graphNodeIDArray[i]!=0){
                k=i;
                newGraphNode= new graphNode(k+1);
                newGraphNode->nextNode=bDummy->nextNode;
                bDummy->nextNode=newGraphNode;
            }
        }
        graphNode * b = bDummy->nextNode;
        while(b!=NULL){
            //cout<<b->nodeID<<" ";
            b=b->nextNode;
        }
        while(bDummy->nextNode!=NULL){
        //STEP 7:
        edgeNode *previousEdge=dummy;
        edgeNode *newEdge=dummy->nextEdge;
        bool found_ni, found_nj;
        int setA_id, setB_id = 0;
        while(true){
            found_ni=false;
            found_nj=false;
            
            graphNode * e= aDummy->nextNode;
            while(e!=NULL){
                if(e->nodeID==newEdge->Ni)
                    found_ni=true;
                if(e->nodeID==newEdge->Nj)
                    found_nj=true;
                if(found_ni && found_nj)
                    break;
                e=e->nextNode;
            }
            if(found_ni==true && found_nj == false){
                setA_id=newEdge->Ni;
                break;
            }
            if(found_ni==false && found_nj==true){
                setA_id=newEdge->Nj;
                break;
            }
            newEdge=newEdge->nextEdge;
            previousEdge=previousEdge->nextEdge;
        }
        
        //STEP 8:
        
        //8.1: Insert new edge infront of mst of G
            
            previousEdge->nextEdge=newEdge->nextEdge;
            newEdge->nextEdge=NULL;
            
            newEdge->nextEdge=mstDummy->nextEdge;
            mstDummy->nextEdge=newEdge;
            
            totalCost=totalCost+newEdge->edgeCost;
        
        //The swap
        
        if(newEdge->Ni==setA_id){
            setB_id=newEdge->Nj;
        }
        if(newEdge->Nj==setA_id){
            setB_id=newEdge->Ni;
        }
            
        graphNode *e=bDummy;
        while(e->nextNode->nodeID !=setB_id){
            e=e->nextNode;
        }
        graphNode * deleteNode =e->nextNode;
        e->nextNode=deleteNode->nextNode;
        deleteNode->nextNode=NULL;
        
        //insert
        deleteNode->nextNode=aDummy->nextNode;
        aDummy->nextNode=deleteNode;
        
        //Print set A
        outfile2<<endl<<"Set A:"<<endl;
        e=aDummy->nextNode;
        while(e!=NULL){
            outfile2<<e->nodeID<<", ";
            e=e->nextNode;
        }
        
        //Print set B
        outfile2<<endl<<"Set B:"<<endl;
        e=bDummy->nextNode;
        while(e!=NULL){
            outfile2<<e->nodeID<<", ";
            e=e->nextNode;
        }
            outfile2<<endl<<"MST of G:"<<endl;
            edgeNode *m =mstDummy->nextEdge;
            while(m!=NULL){
                outfile2<<"<"<<m->Ni<<", "<<m->Nj<<", "<<m->edgeCost<<">, ";
                m=m->nextEdge;
            }
            outfile2<<endl<<endl<<"****************************************";
        
    }
        outfile1<<"A MST of the input Graph:"<<endl<<endl;
        outfile1<<N<<endl;
        edgeNode *q = mstDummy->nextEdge;
        while(q!=NULL){
            outfile1<<q->Ni<<" "<<q->Nj<<" "<<q->edgeCost<<" "<<endl;
            q=q->nextEdge;
        }
        outfile1<<"Total Cost="<<totalCost;
    }
  
    
};
int main(int argc, const char * argv[]) {
    if(argc <3){
        cout<<"Invalid Arrguments!";
        return 0;
    }
    ifstream infile;
    infile.open(argv[1]);
    ofstream outfile2;
    outfile2.open(argv[3]);
    ofstream outfile1;
    outfile1.open(argv [2]);
    int input;
    infile>>input;
    PrimMST prim_mst_instance(input, infile, outfile1, outfile2);
    
    outfile1.close();
    outfile2.close();
    return 0;
}
