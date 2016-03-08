import java.io.*;
import java.util.Scanner;

public class bucketSort {

	private static int [] hashTable;
	
	public static void main(String[] args)  {
		
		int x, index;
		
		//program quits if both files aren't passed in as arguments
		if(args.length<2){
			System.out.println("Invalid Arguments");
			return;
		}
		
		// Find max data from the file
		
		Scanner input1;
		try {
			input1 = new Scanner(new BufferedReader(new FileReader(args[0])));
			
		//dynamically allocate the hash table	
			hashTable=new int[findMax(input1)+1];
			
		//close the input file
			input1.close();
		
		//open input file for 2nd time
			
			Scanner input2;
		
			input2=new Scanner(new BufferedReader(new FileReader(args[0])));
			
		//while the input file is not empty read data, make that data the index
		//and increment the element at that index by 1
			while(input2.hasNext()){
				x=input2.nextInt();
				index=x;
				hashTable[index]++;
			}
			
			input2.close();

		
			FileWriter output;
		
			output = new FileWriter(args[1]);
			printTable(output);
			
		}catch(FileNotFoundException e){
			System.out.println("File not found");
		}
		catch (IOException e) {
			System.out.println("Input/output exception");
		}
		catch(Exception e){
			System.out.println("Exception occured");
		}
		
		
		
		
	}
	
	private static void printTable(Writer output){
		try{
			for(int i=0; i<hashTable.length; i++){
				if(hashTable[i]>0){
					for(int j=0; j<hashTable[i];j++){
						String str= Integer.toString(i);
					
							output.write(str);
							output.write("\r\n");
					
					
							System.out.println(i);
					}
				}
			
			}
	
			output.close();
		} catch (Exception e) {
			System.out.println("An exception occured");
		}
	}
	
	private static int findMax(Scanner input){
		int max=input.nextInt();
		while(input.hasNext()){
			int currentInput=input.nextInt();
			if(currentInput>max){
				max=currentInput;
			}
		}
		return max;
	}

}
