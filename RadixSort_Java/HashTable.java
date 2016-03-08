import java.io.IOException;
import java.io.Writer;

public class HashTable {

public LinkedListQueue [] table;
	LinkedListQueue list0=new LinkedListQueue();
	LinkedListQueue list1=new LinkedListQueue();
	LinkedListQueue list2=new LinkedListQueue();
	LinkedListQueue list3=new LinkedListQueue();
	LinkedListQueue list4=new LinkedListQueue();
	LinkedListQueue list5=new LinkedListQueue();
	LinkedListQueue list6=new LinkedListQueue();
	LinkedListQueue list7=new LinkedListQueue();
	LinkedListQueue list8=new LinkedListQueue();
	LinkedListQueue list9=new LinkedListQueue();
	
	
public HashTable(){
	table=new LinkedListQueue[10];
	table[0]=list0;
	table[1]=list1;
	table[2]=list2;
	table[3]=list3;
	table[4]=list4;
	table[5]=list5;
	table[6]=list6;
	table[7]=list7;
	table[8]=list8;
	table[9]=list9;

}
	
	public void printHashTable(Writer outfile){
		try {
			outfile.write("\n"+ "Hash Table: "+"\n");
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		for(int i=0; i<10; i++){
			try {
				outfile.write("Hash Table ["+i+"]");
				table[i].printQueue(outfile);
				
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	
	
}
