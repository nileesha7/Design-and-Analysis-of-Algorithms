import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		if(args.length<2){
			System.out.println("Invalid Arguments");
			return;
		}
		try{
			Scanner input;
			FileWriter output;
		
		
			input=new Scanner(new BufferedReader(new FileReader(args[0])));
			output=new FileWriter(args[1]);
			
			LinkedListStack stack= new LinkedListStack();
			int data, maxData;
			maxData=input.nextInt();
			Node newNode=new Node(Integer.toString(maxData));
			stack.push(newNode);
			while(input.hasNext()){
				data=input.nextInt();
				if(data>maxData){
					maxData=data;
				}
				newNode = new Node(Integer.toString(data));
				stack.push(newNode);
				
			}
			output.write("The Stack: ");
			stack.printStack(output);
			output.write("\n");
			RadixSort radixSortInstance = new RadixSort(Integer.toString(maxData).length(), output, stack);
			output.close();
			
			
		}catch(Exception e){
			e.getMessage();
		}
		
	}
		
		

}
