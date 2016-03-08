
#include <iostream>
#include <fstream>
#include<math.h>
using namespace std;

class PointNode {
 
public:

    double distance;
    int x_coordinate, y_coordinate,  cluserLabel;
    PointNode *next;
    PointNode(int x, int y){
        x_coordinate=x;
        y_coordinate=y;
        distance=0.0;
        next=NULL;
    }
    
    ~PointNode(){
        delete next;
    }
    
    void printPointNode(){
        cout<<x_coordinate<<"  "<<y_coordinate<<" ";
    }
    
};

class LinkedList{

public:
    PointNode *dummy=NULL;
    PointNode *listHead=NULL;
    LinkedList(){
        dummy=new PointNode(-9999,-9999);
        listHead=dummy;
    }

    ~LinkedList(){
        PointNode *p;
        while(listHead!=NULL){
            p=listHead->next;
            delete listHead;
            listHead=p;
        }
    }
    
    
    void insert (PointNode *newNode){
        listHead->next=newNode;
        listHead=newNode;
        
    }
    
    void deleteList(){
        PointNode * deleteNode;
        deleteNode = dummy->next;
        dummy->next=dummy->next->next;
        delete deleteNode;
    }
    
    void printList(ofstream &outfile){
        PointNode *p=dummy->next;
        

        while (p!=NULL){
            cout<<p->x_coordinate<<" ";
            cout<<p->y_coordinate<<" ";
            cout<<p->cluserLabel<<" ";
            //cout<<p->distance;
            cout<<endl;
            
            outfile<<endl;
            outfile<<p->x_coordinate<<" ";
            outfile<<p->y_coordinate<<" ";
            outfile<<p->cluserLabel<<" ";
            //outfile<<p->distance;
            outfile<<endl;
            p=p->next;
        
        }
    }
    
   
    
};

class KMeans{
    
    struct xycoord{
        int x_coordinate=0, y_coordinate=0;
    };
    int k, numRow, numCol;
    LinkedList *listHead;
    
    int ** imageArray;
    xycoord *kCentroids;
public:
    KMeans(int input_k, int input_numRow, int input_numCol, ifstream &infile, ofstream &outfile,ofstream &outfile2){
        
       
        bool flag=0;
        LinkedList *pointList=new LinkedList;
        PointNode *p;
        int x_input, y_input;
        k=input_k;
        numRow=input_numRow;
        numCol=input_numCol;
        kCentroids=new xycoord[k];
        imageArray = new int *[numRow];
        
        //for loop initializing dynamic 2-D array
        for(int i=0; i<numRow; ++i){
            imageArray[i]=new int [numCol];
        }
        for(int i=0; i<numRow;i++){
            for(int j=0; j<numCol; j++){
                imageArray[i][j]=0;
            }
        }
        //populate the linked list reading the textfile
        while(infile>>x_input && infile>> y_input){
            PointNode *newNode = new PointNode(x_input, y_input);
            pointList->insert(newNode);
        }
     
        //place cluster labels in the linked list
        p=pointList->dummy->next;
        while(p!=NULL){
            for(int i=1; i<=k && p!=NULL; i++ ){

                p->cluserLabel=i;
                p=p->next;
            }
        }
        
        int trial =0;
        while(flag==0){
            outfile<<"TRIAL "<<++trial<<":";
            flag=1;
            //populate the image array
            PointNode *q=pointList->dummy->next;
            while(q!=NULL){//dummy is the last node
                imageArray[q->x_coordinate][q->y_coordinate]=q->cluserLabel;
                q=q->next;
            
            }
        

            printImageArray(imageArray,numRow, numCol, outfile);
        
            //Compute the centroids
        
            //1. Create a 1D array to keep track of the number of occurences
            // of each label
         
            int countArray[k];
            for(int i=0; i<k; i++){
                countArray[i]=0;
            }
     
        
            //traversing the list place the total of every label in the kcentroid array
         
            PointNode * x=pointList->dummy->next;
        
            while(x!=NULL){
                countArray[(x->cluserLabel)-1]++;
                kCentroids[(x->cluserLabel)-1].x_coordinate+=x->x_coordinate;
                kCentroids[(x->cluserLabel)-1].y_coordinate+=x->y_coordinate;
                x=x->next;

            }
        
        
            for(int i=0; i<k; i++){
                if(countArray[i]!=0){
                    kCentroids[i].x_coordinate=kCentroids[i].x_coordinate/countArray[i];
                    kCentroids[i].y_coordinate=kCentroids[i].y_coordinate/countArray[i];
                }
            }
      
            /*
             cout<<endl<<"Printing k-centroids:"<<endl;
             for(int i=0; i<k; i++){
                cout<<kCentroids[i].x_coordinate<<" "<<kCentroids[i].y_coordinate<<endl;
             }
             */
            //compute distance to node's own cluster center point
            p=pointList->dummy->next;
            while(p!=NULL){
                int x1=p->x_coordinate;
                int x2=kCentroids[(p->cluserLabel)-1].x_coordinate;
                int y1=p->y_coordinate;
                int y2=kCentroids[(p->cluserLabel)-1].y_coordinate;
                double distance=sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
                p->distance=distance;
                p=p->next;
            
            }
        
            p=pointList->dummy->next;
            while(p!=NULL){
                int minDistance=p->distance;
                int label = p->cluserLabel;
                for(int i=0; i<k; i++){
                    int x1=p->x_coordinate;
                    int x2=kCentroids[i].x_coordinate;
                    int y1=p->y_coordinate;
                    int y2=kCentroids[i].y_coordinate;
                    double distance=sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
                
                    if(distance<minDistance){
                        flag=0; //if there is a change flag=0
                        minDistance=distance;
                        label=i+1;
                    }
                
                }
                p->cluserLabel=label;
                p=p->next;
            }
        }
        cout<<"Printing linked list:"<<endl;
        outfile2<<"Printing linked list:"<<endl;
        outfile2<<endl;
        outfile2<<k<<endl<<endl;
        outfile2<<numRow<<" "<<numCol<<endl;

        pointList->printList(outfile2);
        
      
        
    }
    
    void printImageArray(int ** imageArray, int row, int col, ofstream &outfile){
        
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                if(imageArray[i][j]==0){
                    outfile<<" ";
                    cout<<" ";
                }
                else{
                    cout<<imageArray[i][j];
                    outfile<<imageArray[i][j];
                }
            }
            cout<<endl;
            outfile<<endl;
        }
    }
    
};

int main(int argc, const char * argv[]) {
    int k, numRow, numCol;
    
    if(argc<3){
        cout<<"Invalid number of arguments";
        return 0;
    }
    ifstream infile;
    infile.open(argv[1]);
    ofstream outfile;
    outfile.open(argv[2]);
    ofstream outfile2;
    outfile2.open(argv[3]);

    
    infile>>k;
    infile>>numRow;
    infile>>numCol;
    
    
    
    KMeans kMeansInstance(k, numRow, numCol, infile, outfile, outfile2);

    outfile.close();
    outfile2.close();
  
}
