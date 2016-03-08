
#include <iostream>
#include<fstream>
using namespace std;

class HeapSort{
    int *theArray; //is a pointer to the heap
public:
    HeapSort(int n);
    ~HeapSort();
    
    void buildHeap(ifstream& infile, ofstream& outfile, int size);
    void insertOneItem(int data, int size);
    bool isHeapFull(int size);
    void bubbleUp(int num);
    void deleteHeap(ofstream& outfile);
    void deleteRoot(ofstream& outfile);
    bool isHeapEmpty();
    void bubbleDown();
    int FindSmallestChildIndex(int leftChild, int rightChild);
    bool isLeaf(int leftchild, int rightchild);
    void printHeap(ofstream& outfile);
};


int main(int argc, const char * argv[]) {
    //The program exits if 0 or one textfiles are passed in as arguments
    if(argc<2){
        cout<<"Invalid Input";
        return 0;
    }
    ifstream infile;
    ofstream outfile;
    
    int num, numberOfElements;
    
    infile.open(argv[1]);
    outfile.open(argv[2]);
    //while loop reads input skipping over white spaces and counts the number of
    //data items
    while(infile>>num){
        numberOfElements++;
    }
    
    //the input file is closed and opened again to allow the file to be read from
    //beginning
    infile.close();
    infile.open(argv[1]);
    
    //numSort is an object of the HeapSort class
    //The constructor is called to build a new heap
    /*The argument passed is NumberOfElements + 1 to allow an extra space to store
    *the number of elements in the array
     */
    HeapSort numSort(numberOfElements+1);
    
    numSort.buildHeap(infile, outfile, numberOfElements+1);
    numSort.deleteHeap(outfile);
    return 0;
}


HeapSort::HeapSort(int size){
    //creates a heap called theArray
    theArray=new int[size];
    //There are initially 0 elements in the heap
    theArray[0]=0;
    
    
}
HeapSort::~HeapSort(){
    delete [] theArray;
}
void HeapSort::buildHeap(ifstream& infile, ofstream& outfile, int size){
    
    int data;
    outfile<<"Build Heap:"<<endl;
    
    while(infile>>data){
        
        insertOneItem(data,size); //The data item read from file is inserted to heap
                                  //using the method insertOnItem
        outfile<<"Inserting "<<data<<": ";
      
        printHeap(outfile);  // The heap is printed on the output file on each insertion
    }
    infile.close();
    
}

void HeapSort::insertOneItem(int num, int heapSize){
    
    if(!isHeapFull(heapSize))
        bubbleUp(num);
}

bool HeapSort::isHeapFull(int heapSize){
    if(heapSize==theArray[0])return true;
    return false;
}


void HeapSort::bubbleUp(int num){
    //parent and child are array indexes
    int parent, child, temp;
    //the array will be holding one more element increasing array size by 1
    theArray[0]++;
    
    child=theArray[0]; //the child index is the latest position of the array

    parent=child/2;
    
    theArray[child]=num;//the new data is stored in the latest index of the array
    
    //The while loop implements the bubble up process
    /*The loop continues while the child index is not the root and while the data in the
     * parent index is greater than the data in the child index
     */
    while(child!=1 && theArray[parent]>theArray[child]){
        
        //two data are swapped
        temp=theArray[child];
        theArray[child]=theArray[parent];
        theArray[parent]=temp;
        
        //Parent index becomes the child index and parent index changes
        child=parent;
        parent=parent/2;
    }
    
    
    
}

void HeapSort::printHeap(ofstream& outfile){
    
    //The loop continues until there is no more data in the heap and until the number
    //of elements in the heap is 10
    for(int i=1; i<=theArray[0]&&i<=10; i++){
        outfile<<theArray[i]<<" ";
    }
    outfile<<endl;
    
}

void HeapSort::deleteHeap(ofstream& outfile){
    outfile<<endl;
    outfile<<endl<<"Delete Heap"<<endl;
    //elements in the heap are deleted until the heap becomes empty
    while(theArray[0]!=0){
        deleteRoot(outfile);
        printHeap(outfile);
    }
    
}


void HeapSort::deleteRoot(ofstream& outfile){
    if(!isHeapEmpty()){
        //print the first element of the heap
        outfile<<"delete "<<theArray[1]<<": ";
        
        //The element in the rightmost position of the heap becomes the root
        theArray[1]=theArray[theArray[0]];
        
        //Since the lastmost position is no more needed the value is replaced with
        //the arbitary value -9999
        theArray[theArray[0]]=-9999;
        
        //the size of the heap decrements by 1
        theArray[0]--;
    
        //the heap is bubbled down
        bubbleDown();
    }
}
void HeapSort:: bubbleDown(){
    int parentIndex, leftChildIndex, rightChildIndex, temp,  smallestChildIndex;
    parentIndex=1;
    
    //The Parent Index has to Child Indices
    leftChildIndex=2*parentIndex;
    rightChildIndex=leftChildIndex+1;
    
    //checks the value of the two Child indices to determine the index with the smallest
    //value
    smallestChildIndex=FindSmallestChildIndex(leftChildIndex, rightChildIndex);
 
    /*The while loop continues while the value of the parent index is greater than the
     * value of the smallest child index, and while the parent is not a leaf
     */
    while(theArray[parentIndex]>theArray[smallestChildIndex]&& !(isLeaf(leftChildIndex,rightChildIndex))){
        //swap occurs
        temp=theArray[parentIndex];
        theArray[parentIndex]=theArray[smallestChildIndex];
        theArray[smallestChildIndex]=temp;
       
        //indexes are reseted
        parentIndex=smallestChildIndex;
        leftChildIndex=2*parentIndex;
        rightChildIndex=leftChildIndex+1;
        smallestChildIndex=FindSmallestChildIndex(leftChildIndex, rightChildIndex);
        
    }
   
    
}
bool HeapSort::isHeapEmpty(){
    if(theArray[0]==0) return true;
    return false;
}

int HeapSort::FindSmallestChildIndex(int leftchildIndex, int rightchildIndex){

    if (theArray[leftchildIndex]<theArray[rightchildIndex] || theArray[rightchildIndex]==-9999)return leftchildIndex;
    return rightchildIndex;
    
}

bool HeapSort:: isLeaf(int leftchildIndex, int rightchildIndex){
    if(leftchildIndex>theArray[0] && rightchildIndex>theArray[0])return true;
    
    return false;
}


