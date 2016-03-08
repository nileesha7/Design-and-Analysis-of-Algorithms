import java.io.IOException;
import java.io.Writer;

public class LinkedListQueue {
	Node head, tail, dummy;
	public LinkedListQueue(){
		dummy=new Node("DUMMY");
		head=dummy;
		tail=dummy;
	}
	public void addTail(Node newNode){
		if(isEmpty()){
			dummy.next=newNode;
			head=newNode;
			tail=newNode;
		}
		else{
			tail.next=newNode;
			tail=newNode;
		}
	}
	
	public Node deleteHead(){
		 if(isEmpty())return null;
	        
	        Node deleteNode=head;
	        //if the queue only has one element
	        if(dummy.next.next==null){
	            dummy.next=null;
	            head=dummy;
	            tail=dummy;	           
	            return deleteNode;
	        }
	        //if the queue has more than 1 elements
	        else{
	            dummy.next=head.next;
	            head=head.next;
	            deleteNode.next=null;
	           
	            return deleteNode;
	        }

	}
	
	public boolean isEmpty(){
		return dummy.next==null;
	}
	
	public void printQueue(Writer outfile){
		Node p=dummy;
		while(p.next!=null){
			try {
				outfile.write("--> ("+p.data+", "+p.next.data+")");
				p=p.next;
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		if(p.next==null){
            try {
				outfile.write("-->("+p.data+", "+"-1"+")");
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
        }
		try {
			outfile.write("\n");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	
}
