import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Main {
	public static void main(String [] args){
		Scanner input = null;
		Scanner input1=null;
		FileWriter output1 = null, output2 = null;
		int numOfNodes, sourceNode;
		Dijkstra dijkstraSSS;
		
		if (args.length<4){
			System.out.println("Invalid number of arguments");
			return;
		}
		
		try {
	
			input=new Scanner(new BufferedReader (new FileReader(args [0])));
			input1=new Scanner(new BufferedReader (new FileReader(args [1])));
			output1=new FileWriter(args[2]);
			output2=new FileWriter(args [3]);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		sourceNode=input1.nextInt();
		
		numOfNodes=input.nextInt();
		dijkstraSSS = new Dijkstra(numOfNodes, sourceNode);
		dijkstraSSS.dijkstra_SSS(input, output1, output2);
		
		try {
			output1.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			output2.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		input1.close();
		input.close();
		
		
	}
}
