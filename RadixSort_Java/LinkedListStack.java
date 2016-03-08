import java.io.IOException;
import java.io.Writer;

public class LinkedListStack {
	private Node top;
	public LinkedListStack(){
		top=null;
	}
	public void push(Node newNode){
		newNode.next=top;
		top=newNode;
	}
	public Node pop(){
		if(isEmpty())return null;
		else{
			Node deleteNode=top;
			top=top.next;
			deleteNode.next=null;
			return deleteNode;
		}
	}
	
	public boolean isEmpty(){
		return top==null;
	}
	
	public void printStack(Writer output){
		Node p;
		p=top;
	
		while(p.next!=null){
			try {
				output.write("-->("+p.data+", "+p.next.data+")");
				p=p.next;
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		if(p.next==null){
            try {
				output.write("-->("+p.data+", "+"-1"+")");
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
        }

		
	}
}
