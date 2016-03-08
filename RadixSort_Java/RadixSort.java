import java.io.IOException;
import java.io.Writer;

public class RadixSort {
	int currentTable=0, previousTable ;
	int currentDigit=0;
	int currentQueue, temp;
	HashTable[]tableArray=new HashTable[2];
	
	
	RadixSort(int totalDigit, Writer outfile, LinkedListStack stack){
		tableArray[0]=new HashTable();
		tableArray[1]=new HashTable();
			int digit=0;
			int index = 0;
			int i=0;
			while(!stack.isEmpty()){
				i++;
				String data=stack.pop().data;
				//pop the stack and make a new node from data popped from the stack
				Node node=new Node(data);
				if(data.length()-1-currentDigit>=0){
					//get the current digit from the data in the node
					char charDigit= data.charAt(data.length()-1-currentDigit);
					digit=charDigit-'0';
					index=hashFunction(digit);
				}else{
				
					index=hashFunction(0);

				}
				tableArray[currentTable].table[index].addTail(node);
       
			}
		
		
			currentDigit++;
			currentTable=1;
			previousTable=0;
			currentQueue=0;
			while(currentDigit<totalDigit){
				
				tableArray[previousTable].printHashTable(outfile);
				while(currentQueue<10){
					
					while(!tableArray[previousTable].table[currentQueue].isEmpty()){
						
						Node newNode = tableArray[previousTable].table[currentQueue].deleteHead();
						String data=newNode.data;
						//get the current digit from the data in the node
						if(data.length()-1-currentDigit>=0){
							//get the current digit from the data in the node
							char charDigit= data.charAt(data.length()-1-currentDigit);
							digit=charDigit-'0';
							index=hashFunction(digit);
						}else{
							index=hashFunction(0);
						}
						tableArray[currentTable].table[index].addTail(newNode);
					}
					currentQueue++;
				
				}
			
				temp=currentTable;
				currentTable=previousTable;
				previousTable=temp;
				currentQueue=0;
				currentDigit++;
			}
			
			
			tableArray[previousTable].printHashTable(outfile);

			
	}
	
	private int hashFunction(int x){
		int index=x;
		return index;
	}
}
